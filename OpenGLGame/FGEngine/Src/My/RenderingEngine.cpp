/**
* RenderingEngine.cpp
*/
#include "RenderingEngine.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "ResouceManager.h"
#include "ObjectManager.h"
#include "ShaderObject.h"
#include "MeshBuffer.h"
#include "ShaderLocationNum.h"
#include <algorithm>

namespace FGEngine::RenderingSystem
{
	/**
	* �O���t�B�b�N�G���W����������
	*
	* @retval 0		����������
	* @retval 0�ȊO	���������s
	*/
	int RenderingEngine::Initialize()
	{
		
		// �X�J�C�X�t�B�A��ݒ�
		skySphere = ResouceSystem::ResouceManager::GetInstance()->GetStaticMesh("skySphere");

		return 0;
	}

	/**
	* �����_�����O�G���W�����X�V
	*/
	void RenderingEngine::Update()
	{
	}

	/**
	* 3D�I�u�W�F�N�g�̕`��
	*
	* @param �����_�[�R���|�[�l���g�͈͂̐�[
	* @param �����_�[�R���|�[�l���g�͈͂̏I�[
	*/
	void RenderingEngine::Draw3DGameObject(std::vector<RendererPtr>::iterator begin, std::vector<RendererPtr>::iterator end)
	{
		for (auto i = begin; i != end; ++i)
		{
			const auto& e = *i;
			// �`��R���|�[�l���g���@�\��~���Ă����牽�����Ȃ�
			if (!e->enabled)
			{
				continue;
			}
			// �`��
			e->Draw(DrawType::normal);
		}
	}

	/**
	* �X�J�C�X�t�B�A��`��
	*/
	void RenderingEngine::DrawSkySphere()
	{
		// �V�[���}�l�[�W���[���擾
		auto sceneManger = SceneSystem::SceneManager::GetInstance();

		// ���\�[�X�}�l�[�W���[���擾
		auto resouceManager = ResouceSystem::ResouceManager::GetInstance();
		const GLuint progUnlit = resouceManager->GetShader("Unlit")->GetProgId();

		// �X�J�C�X�t�B�A���ݒ肳��Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
		if (!skySphere || !sceneManger->CurrentScene()->skyMaterial)
		{
			return;
		}

		// �A�����b�h�V�F�[�_�ŕ`��
		glUseProgram(progUnlit);
		glDepthMask(GL_FALSE);	// �[�x�o�b�t�@�ւ̏������݂��֎~
		glBindVertexArray(*skySphere->vao);

		// �X�J�C�X�t�B�A�̔��a��0.5m�Ɖ��肵�A�`��͈͂�95%�̑傫���Ɋg��
		static const float far = 1000;	// �`��͈͂̍ő�l
		static const float scale = far * 0.95f / 0.5f;
		static const Matrix4x4 transformMatrix = Matrix4x4{
			Vector4(scale, 0,		0,		0),
			Vector4(0,		scale,	0,		0),
			Vector4(0,		0,		scale,	0),
			Vector4(0,		0,		0,		1),
		};
		glProgramUniformMatrix4fv(progUnlit, locTransformMatrix, 1, GL_FALSE, &transformMatrix[0].x);

		// �F�̓}�e���A���J���[�Œ�������̂ŃI�u�W�F�N�g�J���[�͔��ɐݒ�
		static const Color color = Color::white;
		glProgramUniform4fv(progUnlit, locColor, 1, &color.r);

		// �X�J�C�X�t�B�A�̓J���������_�Ƃ��ĕ`��
		static const Vector3 skySphereCameraPosition = Vector3{ 0,0,0 };
		glProgramUniform3fv(progUnlit, 4, 1, &skySphereCameraPosition.x);

		// �X�J�C�X�t�B�A��`��
		const MaterialList materials(1, sceneManger->CurrentScene()->skyMaterial);
		Draw(progUnlit, *skySphere, materials);

		auto objectManager = ObjectSystem::ObjectManager::GetInstance();

		glProgramUniform3fv(progUnlit, 4, 1, &objectManager->GetMainCamera()->GetTransform()->position.x);	// �J�������W�����ɖ߂�
		glDepthMask(GL_TRUE);	// �[�x�o�b�t�@�ւ̏������݂�����

		glBindVertexArray(0);
		glUseProgram(0);

	}

	/**
	* �Q�[���I�u�W�F�N�g�̕`��
	* 
	* @param �����_�[�R���|�[�l���g�͈͂̐�[
	* @param �����_�[�R���|�[�l���g�͈͂̏I�[
	*/
	void RenderingEngine::DrawGameObject(std::vector<RendererPtr> rendererList)
	{
		// �Q�[���I�u�W�F�N�g�������_�[�L���[���ɕ��ׂ�
		std::stable_sort(rendererList.begin(), rendererList.end(),
			[](const RendererPtr& a, const RendererPtr& b) {
				return a->renderQueue < b->renderQueue; });

		// transparent�L���[�̐擪������
		const auto transparentBegin = std::lower_bound(
				rendererList.begin(), rendererList.end(), RenderQueue_transparent,
			[](const RendererPtr& e, int value) { return e->renderQueue < value; });

		// overlay�L���[�̐擪������
		const auto overlayBegin = std::lower_bound(
			transparentBegin, rendererList.end(), RenderQueue_overlay,
			[](const RendererPtr& e, int value) { return e->renderQueue < value; });


		// �`�����f�t�H���g�t���[���o�b�t�@�ɖ߂�
		auto fbSize = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, (GLsizei)fbSize.x, (GLsizei)fbSize.y);

		glEnable(GL_DEPTH_TEST);	// �[�x�e�X�g��L����
		glEnable(GL_CULL_FACE);		// ���ʃJ�����O��L����

		// ������������L����
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);

		// transparent�ȑO�̃L���[��`��
		Draw3DGameObject(rendererList.begin(), transparentBegin);

		// �X�J�C�X�t�B�A��`��
		DrawSkySphere();

		// transparent����overlay�܂ł̃L���[��`��
		glDepthMask(GL_FALSE); // �[�x�o�b�t�@�ւ̏������݂��֎~
		Draw3DGameObject(transparentBegin, overlayBegin);
		glDepthMask(GL_TRUE); // �[�x�o�b�t�@�ւ̏������݂�����

		// overlay�ȍ~�̃L���[��`��
		glDisable(GL_DEPTH_TEST);	// �[�x�e�X�g�𖳌���
		glDisable(GL_CULL_FACE);	// ���ʃJ�����O�𖳌���

	}
}