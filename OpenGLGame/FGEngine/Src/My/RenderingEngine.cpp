/**
* RenderingEngine.cpp
*/
#include "RenderingEngine.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "ResouceManager.h"
#include "ObjectManager.h"
#include "Shader.h"
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

		// FBO���쐬
		auto texShadow = Texture::Create("FBO(depth)", 2048, 2048, GL_DEPTH_COMPONENT32, GL_CLAMP_TO_EDGE);
		fboShadow = FrameBufferObject::Create(nullptr, texShadow);
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
	* �J�����ɋ߂����C�g��I���GPu�������[�ɃR�s�[����
	*/
	void RenderingEngine::UpdateShaderLight()
	{
		// �V�F�[�_�̎d����
		auto resouceManager = ResouceSystem::ResouceManager::GetInstance();
		std::vector<GLuint> programs;
		for (auto prog : *resouceManager->GetShaderList())
		{
			// ���C�g�p�̃V�F�[�_
			if (prog.second->isLight)
			{
				programs.push_back(prog.second->GetProgId());
			}
		}

		for (auto prog : programs)
		{
			// ������GPU�������ɃR�s�[
			glProgramUniform3fv(prog, locAmbientLight, 1, &ambientLight.x);

			// ���s�����p�����[�^��GPU�������ɃR�s�[
			const Vector3 color = directionLight.color * directionLight.intensity;
			glProgramUniform3fv(prog, locDirectionalLightColor, 1, &color.x);
			glProgramUniform3fv(prog, locDirectionalLightDericion, 1, &directionLight.direction.x);

		}

		// �R�s�[���郉�C�g���Ȃ���΃��C�g����0�ɐݒ�
		if (usedLights.empty())
		{
			for (auto prog : programs)
			{
				if (usedLights.empty())
				{
					glProgramUniform1i(prog, locLightCount, 0);
					return;
				}
			}
		}
		// �g�p�����C�g�̔z�񂩂�A���g�p�ɂȂ������C�g�����O����
		const auto itrUnsed = std::remove_if(usedLights.begin(), usedLights.end(),
			[&](int i) {return !lights[i].used; });
		usedLights.erase(itrUnsed, usedLights.end());

		// �d������ԍ�����������
		std::sort(usedLights.begin(), usedLights.end());
		const auto itrUnique = std::unique(usedLights.begin(), usedLights.end());
		usedLights.erase(itrUnique, usedLights.end());

		auto camera = ObjectSystem::ObjectManager::GetInstance()->GetMainCamera();

		// �J�����̐��ʃx�N�g�����v�Z
		const Vector3 front = camera->transform->Forward();

		// �J�������烉�C�g�܂ł̋������v�Z
		struct Distance
		{
			float distance;		// �J�������烉�C�g�̔��a�܂ł̋���
			const LightData* p;	// ���C�g�̃A�h���X
		};
		std::vector<Distance> distanceList;
		distanceList.reserve(lights.size());
		for (auto index : usedLights)
		{
			const auto& light = lights[index];
			const Vector3 v = light.position - camera->transform->position;
			// �J�����̌��ɂ��郉�C�g�����O
			if (Vector3::Dot(front, v) <= -light.radius)
			{
				continue;
			}
			const float d = v.Magnitude() - light.radius; // �J��������̃��C�g�܂ł̔��w�܂ł̋���
			distanceList.push_back({ d,&light });
		}
		// ��ʂɉe�����郉�C�g���Ȃ���΃��C�g����0�ɐݒ�
		if (distanceList.empty())
		{
			for (auto prog : programs)
			{
				glProgramUniform1i(prog, locLightCount, 0);
			}
			return;
		}

		// �J�����ɋ߂����C�g��D�悷��
		std::stable_sort(distanceList.begin(), distanceList.end(),
			[&](const auto& a, const auto& b) {return a.distance < b.distance; });

		// ���C�g�f�[�^��GPU�������ɃR�s�[����
		const int lightCount = static_cast<int>(std::min(distanceList.size(), maxShaderLightCount)); // �R�s�[���郉�C�g��
		std::vector<Vector4> colorAndFalloffAngle(lightCount);
		std::vector<Vector4> positionAndRadius(lightCount);
		std::vector<Vector4> directionAndConeAngle(lightCount);
		for (int i = 0; i < lightCount; ++i)
		{
			const LightData* p = distanceList[i].p;
			const Vector3 color = p->color * p->intesity;
			colorAndFalloffAngle[i] = Vector4{
				color.x,color.y,color.z, p->fallOffAngle
			};
			positionAndRadius[i] = Vector4{
				p->position.x, p->position.y, p->position.z, p->radius
			};
			directionAndConeAngle[i] = Vector4{
					p->direction.x,p->direction.y,p->direction.z,p->coneAngle
			};
		}

		for (auto prog : programs)
		{
			glProgramUniform4fv(prog, locLightColorAndFalloffAngle, lightCount, &colorAndFalloffAngle[0].x);
			glProgramUniform4fv(prog, locLightPositionAndRadius, lightCount, &positionAndRadius[0].x);
			glProgramUniform4fv(prog, locLightDirectionAndConeAngle, lightCount, &directionAndConeAngle[0].x);
			glProgramUniform1i(prog, locLightCount, lightCount);
		}
	}

	/**
	* �f�v�X�V���h�E�}�b�v�̍쐬
	*/
	void RenderingEngine::CreateShadowMap(std::vector<RendererPtr>::iterator begin, std::vector<RendererPtr>::iterator end)
	{
		// �`���t���[���o�b�t�@��ύX
		glBindFramebuffer(GL_FRAMEBUFFER, *fboShadow);

		// �r���[�|�[�g���t���[���o�b�t�@�̃T�C�Y�ɍ��킹��
		const auto& texShadow = fboShadow->GetDepthTexture();
		glViewport(0, 0, texShadow->GetWidth(), texShadow->GetHeight());

		glEnable(GL_DEPTH_TEST);	// �[�x�e�X�g��L����
		glDisable(GL_BLEND);		// �����������𖳌���

		// �[�x�o�b�t�@���N���A
		glClear(GL_DEPTH_BUFFER_BIT);

		// �e�̕`��p�����[�^
		const float shadowAreaSize = 100;	// �e�̕`��͈�(XY����)
		const float shadowNearZ = 1;		// �e�̕`��͈�(��Z����)
		const float shadowFarZ = 200;		// �e�̕`��͈�(��Z����)
		const float shadowCenterZ = (shadowNearZ + shadowFarZ) * 0.5f; // �`��͈͂̒��S
		const Vector3 target = Vector3{ 0, 0, -50 }; // �J�����̒����_
		const Vector3 eye = target - directionLight.direction * shadowCenterZ; // �J�����̈ʒu

		// �r���[�v���W�F�N�V�����s����v�Z
		const Matrix4x4 matShadowView = Matrix4x4::LookAt(eye, target, Vector3::up);
		const Matrix4x4 matShadowProj = Matrix4x4::Orthogonal(
			-shadowAreaSize / 2, shadowAreaSize / 2,
			-shadowAreaSize / 2, shadowAreaSize / 2,
			shadowNearZ, shadowFarZ);
		const Matrix4x4 matShadow = matShadowProj * matShadowView;

		// �V�F�[�_�̎d����
		auto resouceManager = ResouceSystem::ResouceManager::GetInstance();
		std::vector<GLuint> shadowPrograms;
		for (auto prog : *resouceManager->GetShaderList())
		{
			// ���C�g�p�̃V�F�[�_
			if (prog.second->isShadow)
			{
				shadowPrograms.push_back(prog.second->GetProgId());
			}
		}

		// �e���g�p����V�F�[�_���擾
		std::vector<GLuint> programs;
		for (auto prog : *resouceManager->GetShaderList())
		{
			if (prog.second->isUseLight)
			{
				programs.push_back(prog.second->GetProgId());
			}
		}


		// �r���[�v���W�F�N�V�����s���GPU�������ɃR�s�[
		for (auto prog : shadowPrograms)
		{
			glProgramUniformMatrix4fv(prog, locViewProjectionMatrix, 1, GL_FALSE, &matShadow[0].x);
		}

		// ���b�V����`��
		for (std::vector<RendererPtr>::iterator i = begin; i != end; ++i)
		{
			const auto& e = *i;
			e->Draw(DrawType::shadow);
		}

		// �[�x�e�N�X�`�������蓖�Ă�
		glBindTextureUnit(2, *texShadow);

		// �[�x�e�N�X�`�����W�ւ̕ϊ��s����쐬
		static const Matrix4x4 matTexture = Matrix4x4{
			Vector4{0.5f, 0.0f, 0.0f, 0.0f},
			Vector4{0.0f, 0.5f, 0.0f, 0.0f},
			Vector4{0.0f, 0.0f, 0.5f, 0.0f},
			Vector4{0.5f, 0.5f, 0.5f, 1.0f}
		};

		for (auto prog : programs)
		{
			// �V���h�E�e�N�X�`���s���GPU�������ɃR�s�[
			const Matrix4x4 matShadowTexture = matTexture * matShadowProj * matShadowView;
			glProgramUniformMatrix4fv(prog, locShadowTextureMatrix, 1, GL_FALSE, &matShadowTexture[0].x);

			// �@�������̐ݒ�
			const float texSize = shadowAreaSize / static_cast<float>(texShadow->GetWidth());
			glProgramUniform1f(prog, locShadowNormalOffset, texSize);
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

		glDepthMask(GL_FALSE);	// �[�x�o�b�t�@�ւ̏������݂��֎~

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

		// �f�v�X�V���h�E�}�b�v���쐬
		CreateShadowMap(rendererList.begin(), rendererList.end());

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

		// ���C�g�̍X�V
		UpdateShaderLight();

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