/**
* RenderingEngine.cpp
*/
#include "FGEngine/MainSystem/RenderingEngine.h"
#include "FGEngine/BufferAndVAO/MeshBuffer.h"
#include "FGEngine/BufferAndVAO/GltfFileBuffer.h"
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Scene/SceneManager.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Asset/Shader.h"
#include "FGEngine/Asset/Texture.h"
#include "FGEngine/Math/Math.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Renderer.h"
#include "FGEngine/Component/Camera.h"
#include <algorithm>

namespace FGEngine
{
	/**
	* �O���t�B�b�N�G���W����������
	*
	* @retval 0		����������
	* @retval 0�ȊO	���������s
	*/
	int RenderingEngine::Initialize()
	{
		auto resManager = AssetManager::GetInstance();

		// �X�J�C�X�t�B�A��ݒ�
		skySphere = resManager->GetStaticMesh("skySphere");

		// glTF�t�@�C���o�b�t�@���擾
		glTFfileBuffer = resManager->GetGltfFileBuffer();

		// FBO���쐬
		auto texShadow = Texture::Create("FBO(depth)", 4096, 4096, GL_DEPTH_COMPONENT32, GL_CLAMP_TO_EDGE);
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
	* �J�����ɋ߂����C�g��I���GPU�������[�ɃR�s�[����
	*/
	void RenderingEngine::UpdateShaderLight(const CameraPtr& camera)
	{
		// �V�F�[�_�̎d����
		auto resouceManager = AssetManager::GetInstance();
		std::vector<ShaderPtr> programs;
		programs.push_back(resouceManager->GetShader(DefalutShader::Standard3D));
		programs.push_back(resouceManager->GetShader(DefalutShader::Skeletal3D));

		for (auto prog : programs)
		{
			// ������GPU�������ɃR�s�[
			prog->SetVector3("ambientLight", ambientLight);

			// ���s�����p�����[�^��GPU�������ɃR�s�[
			const Vector3 color = directionLight.color * directionLight.intensity;
			prog->SetVector3("directionLight.color", color);
			prog->SetVector3("directionLight.direction", directionLight.direction);

		}

		// �R�s�[���郉�C�g���Ȃ���΃��C�g����0�ɐݒ�
		if (usedLights.empty())
		{
			for (auto prog : programs)
			{
				prog->SetInt("lightCount", 0);
				return;
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


		// �J�����̐��ʃx�N�g�����v�Z
		const Vector3 front = camera->GetTransform()->Forward();

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
			const Vector3 v = light.position - camera->GetTransform()->position;
			// �J�����̌��ɂ��郉�C�g�����O
			if (Vector3::Dot(front, v) <= -light.radius)
			{
				continue;
			}
			const float d = Vector3::Magnitude(v) - light.radius; // �J��������̃��C�g�܂ł̔��w�܂ł̋���
			distanceList.push_back({ d,&light });
		}
		// ��ʂɉe�����郉�C�g���Ȃ���΃��C�g����0�ɐݒ�
		if (distanceList.empty())
		{
			for (auto prog : programs)
			{
				prog->SetInt("lightCount", 0);
			}
			return;
		}

		// �J�����ɋ߂����C�g��D�悷��
		std::stable_sort(distanceList.begin(), distanceList.end(),
			[&](const auto& a, const auto& b) {return a.distance < b.distance; });

		// ���C�g�f�[�^��GPU�������ɃR�s�[����
		constexpr size_t maxShaderLightCount = 16;
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
			//glProgramUniform4fv(prog, locLightColorAndFalloffAngle, lightCount, &colorAndFalloffAngle[0].x);
			//glProgramUniform4fv(prog, locLightPositionAndRadius, lightCount, &positionAndRadius[0].x);
			//glProgramUniform4fv(prog, locLightDirectionAndConeAngle, lightCount, &directionAndConeAngle[0].x);
			prog->SetInt("lightCount", lightCount);
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

		// �[�x�o�b�t�@���N���A
		glClear(GL_DEPTH_BUFFER_BIT);

		// �e�̕`��p�����[�^
		const float shadowAreaSize = 450;	// �e�̕`��͈�(XY����)
		const float shadowNearZ = 1;		// �e�̕`��͈�(��Z����)
		const float shadowFarZ = 400;		// �e�̕`��͈�(��Z����)
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
		auto resouceManager = AssetManager::GetInstance();
		std::vector<ShaderPtr> shadowPrograms;

		shadowPrograms.push_back(resouceManager->GetShader(DefalutShader::Shadow3D));
		shadowPrograms.push_back(resouceManager->GetShader(DefalutShader::ShadowSkeletal3D));

		// �e���g�p����V�F�[�_���擾
		std::vector<ShaderPtr> programs;
		programs.push_back(resouceManager->GetShader(DefalutShader::Standard3D));
		programs.push_back(resouceManager->GetShader(DefalutShader::Skeletal3D));

		// �r���[�v���W�F�N�V�����s���GPU�������ɃR�s�[
		for (auto prog : shadowPrograms)
		{
			prog->SetMatrix4x4("viewProjectionMatrix", matShadow);
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
			prog->SetMatrix4x4("shadowTextureMatrix", matShadowTexture);

			// �@�������̐ݒ�
			const float texSize = shadowAreaSize / static_cast<float>(texShadow->GetWidth());
			prog->SetFloat("shadowNormalOffset", texSize);
		}
	}

	/**
	* �X�J�C�X�t�B�A��`��
	*/
	void RenderingEngine::DrawSkySphere(const CameraPtr& camera)
	{
		// �V�[���}�l�[�W���[���擾
		auto sceneManger = SceneManager::GetInstance();

		// ���\�[�X�}�l�[�W���[���擾
		auto resouceManager = AssetManager::GetInstance();
		const auto progUnlit = resouceManager->GetShader("Unlit");

		// �X�J�C�X�t�B�A���ݒ肳��Ă��Ȃ��ꍇ�͕`�悵�Ȃ�
		if (!skySphere || !sceneManger->CurrentScene()->skyBoxMaterial)
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
		progUnlit->SetMatrix4x4("transformMatrix", transformMatrix);

		// �F�̓}�e���A���J���[�Œ�������̂ŃI�u�W�F�N�g�J���[�͔��ɐݒ�
		progUnlit->SetColor("color", Color::white);

		// �X�J�C�X�t�B�A�̓J���������_�Ƃ��ĕ`��
		progUnlit->SetVector3("cameraPosition", Vector3::zero);

		// �X�J�C�X�t�B�A��`��
		const MaterialList materials(1, sceneManger->CurrentScene()->skyBoxMaterial);
		Draw(progUnlit, *skySphere, materials);

		// �J�������W�����ɖ߂�
		progUnlit->SetVector3("cameraPosition", camera->GetTransform()->position);
		glDepthMask(GL_TRUE);	// �[�x�o�b�t�@�ւ̏������݂�����
	}

	/**
	* �Q�[���I�u�W�F�N�g�̕`��
	*
	* @param �����_�[�R���|�[�l���g�͈͂̐�[
	* @param �����_�[�R���|�[�l���g�͈͂̏I�[
	*/
	void RenderingEngine::DrawGameObject(std::vector<RendererPtr> rendererList, const CameraPtr& camera)
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

		glEnable(GL_DEPTH_TEST);	// �[�x�e�X�g��L����
		glEnable(GL_CULL_FACE);		// ���ʃJ�����O��L����

		// ������������L����
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glBlendEquation(GL_FUNC_ADD);

		// ���C�g�̍X�V
		UpdateShaderLight(camera);

		// �f�v�X�V���h�E�}�b�v���쐬
		CreateShadowMap(rendererList.begin(), rendererList.end());

		// �`�����f�t�H���g�t���[���o�b�t�@�ɖ߂�
		auto fbSize = WindowManager::GetInstance()->GetWindowSize();
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, (GLsizei)fbSize.x, (GLsizei)fbSize.y);

		// �A�j���[�V�����o�b�t�@���N���A
		glTFfileBuffer->ClearAnimationBuffer();

		// �`��̑O����
		for (auto& x : rendererList)
		{
			if (x->enabled)
			{
				x->PreDraw();
			}
		}

		// �A�j���[�V�����o�b�t�@��GPU�������ɃR�s�[����
		glTFfileBuffer->UploadAnimationBuffer();

		// transparent�ȑO�̃L���[��`��
		Draw3DGameObject(rendererList.begin(), transparentBegin);

		// �X�J�C�X�t�B�A��`��
		DrawSkySphere(camera);

		// transparent����overlay�܂ł̃L���[��`��
		glDepthMask(GL_FALSE); // �[�x�o�b�t�@�ւ̏������݂��֎~
		Draw3DGameObject(transparentBegin, overlayBegin);
		glDepthMask(GL_TRUE); // �[�x�o�b�t�@�ւ̏������݂�����

		// overlay�ȍ~�̃L���[��`��
		glDisable(GL_DEPTH_TEST);	// �[�x�e�X�g�𖳌���
		glDisable(GL_CULL_FACE);	// ���ʃJ�����O�𖳌���

	}
}