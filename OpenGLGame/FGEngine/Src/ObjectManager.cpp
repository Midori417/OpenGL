/**
* @file ObjectManager.cpp
*/
#include "FGEngine/ObjectManager.h"
#include "FGEngine/Rendering/RenderingEngine.h"
#include "FGEngine/Physics/PhysicsEngine.h"
#include "FGEngine/Physics/WorldCollider.h"
#include "FGEngine/Asset/ResouceManager.h"
#include "FGEngine/Asset/Shader.h"
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Time.h"
#include <algorithm>

namespace FGEngine::ObjectSystem
{
	/**
	* �I�u�W�F�N�g�}�l�[�W���[��������
	*
	* @retval 0		����ɏ�����
	* @retval 0�ȊO ���������s
	*/
	int ObjectManager::Initialize()
	{
		// �Q�[���I�u�W�F�N�g�z��̗e�ʂ���\��
		gameObjects.reserve(1000);


		return 0;
	}

	/**
	* �I�u�W�F�N�g�}�l�[�W���[���X�V
	*/
	void ObjectManager::Update()
	{
		// �Q�[���I�u�W�F�N�g�z�񂪋�̂��߉������Ȃ�
		if (gameObjects.empty())
		{
			return;
		}

		// �Q�[���I�u�W�F�N�g�̃C�x���g����
		UpdateMonoBehaviour();

		// �I�u�W�F�N�g���W����
		UpdateTransform();

		// �Փˏ���
		CollisionGameObject();

		// ��������
		UpdateRigidbody();

		// �A�j���[�^����
		UpdateAnimator();

		// �I�u�W�F�N�g�̔j�󏈗�
		DestoryGameObject();

		// UI�̕`�揈��
		UIRendererGameObject();

		// �I�u�W�F�N�g�̕`�揈��
		RendererGameObject();

	}

	/**
	* �Q�[���I�u�W�F�N�g��`��
	*/
	void ObjectManager::RendererGameObject()
	{
		// �V�F�[�_�̎d����
		auto resouceManager = ResouceSystem::ResouceManager::GetInstance();
		std::vector<ShaderPtr> programs;
		programs.push_back(resouceManager->GetShader(DefalutShader::Standard3D));
		programs.push_back(resouceManager->GetShader(DefalutShader::Skeletal3D));
		programs.push_back(resouceManager->GetShader(DefalutShader::Unlit));
		programs.push_back(resouceManager->GetShader(DefalutShader::Particle));

		// �J�����̃p�����[�^��ݒ�
		for (auto prog : programs)
		{
			if (mainCamera)
			{
				// �A�X�y�N�g��Ǝ���p��ݒ�
				float fovScale = mainCamera->camera->GetFovScale();
				float aspectRatio = mainCamera->camera->aspect;
				prog->SetFloat4("aspectRatioAndScaleFov", 1 / aspectRatio, fovScale,
					mainCamera->camera->near, mainCamera->camera->far);

				// �J�����̈ʒu�Ɖ�]�ƃX�P�[���̊i�[��
				Vector3 pos;
				Vector3 scale;
				Matrix3x3 rot;

				// �J�����̍��W�ϊ��s��𕪉�
				Matrix4x4::Decompose(mainCamera->transform->GetWorldTransformMatrix(), pos, scale, rot);

				// �N�H�[�^�j�I���Ɉ�x�ϊ�
				Quaternion q = Quaternion::RotationMatrixToQuaternion(rot);
				// �J�����͋t��]�ɂ��邽�ߋt���ɂ���
				rot = Quaternion::QuaternionToRotationMatrix(Quaternion(q.x, q.y, q.z, -q.w));

				// GPU�ɏ���`����
				prog->SetVector3("cameraPosition", pos);
				prog->SetMatrix3x3("cameraRotationMatrix", rot);
			}
		}

		// �`��R���|�[�l���g�̗L���Ŏd��������
		std::vector<RendererPtr> rendererList;
		rendererList.reserve(gameObjects.size());
		for (auto x : gameObjects)
		{
			if (x->renderer)
			{
				rendererList.push_back(x->renderer);
			}
		}

		// �����_�����O�G���W���ɕ`�悵�Ă��炤
		RenderingSystem::RenderingEngine::GetInstance()->DrawGameObject(rendererList);
	}

	/**
	* �Q�[���I�u�W�F�N�g��UI�`�揈��
	*/
	void ObjectManager::UIRendererGameObject()
	{
		// UI�`��R���|�[�l���g�̗L���Ŏd������
		std::vector<UI::ImGuiLayoutPtr> imguiList;
		imguiList.reserve(gameObjects.size());

		for (auto x : gameObjects)
		{
			if (x->imGuiLayout)
			{
				imguiList.push_back(x->imGuiLayout);
			}
		}

		// UI���Ȃ����ߏ������I���
		if (imguiList.empty())
		{
			return;
		}

		for (auto x : imguiList)
		{
			if (x && x->enabled)
			{
				x->UIUpdate();
			}
		}
	}

	/**
	* �Q�[���I�u�W�F�N�g�̏Փˏ����̏���
	*/
	void ObjectManager::CollisionGameObject()
	{
		// ���[���h���W�n�̏Փ˔�����쐬
		std::vector<PhysicsSystem::WorldColliderList> colliders;
		colliders.reserve(gameObjects.size());
		for (const auto& e : gameObjects)
		{
			if (e->colliders.empty())
			{
				continue; // �R���C�_�[�������Ă��Ȃ������牽�����Ȃ�
			}

			if (e->rigidbody)
			{
				e->rigidbody->isGrounded = false;
			}

			// �Փ˔�����쐬
			PhysicsSystem::WorldColliderList list(e->colliders.size());
			for (int i = 0; i < e->colliders.size(); ++i)
			{
				// �I���W�i���̃R���C�_�[���R�s�[
				list[i].origin = e->colliders[i];

				//�R���C�_�[�̍��W�����[���h���W�ɕϊ�
				list[i].world = e->colliders[i]->GetTransformedCollider(e->transform->GetWorldTransformMatrix());
			}
			colliders.push_back(list);
		}

		// �Փˏ����̓R���W�����̂����Q�[���I�u�W�F�N�g����ȏ�
		if (colliders.size() >= 2)
		{
			// �Q�[���I�u�W�F�N�g�P�ʂ̏Փ˔���
			for (auto a = colliders.begin(); a != colliders.end() - 1; ++a)
			{
				const GameObjectPtr goA = a->at(0).origin->OwnerObject();
				if (goA->GetHideFlag() == Object::HideFlag::Destory)
				{
					continue;	// �폜�ς݂Ȃ̂Ŕ�΂�
				}
				for (auto b = a + 1; b != colliders.end(); ++b)
				{
					const GameObjectPtr goB = b->at(0).origin->OwnerObject();
					if (goB->GetHideFlag() == Object::HideFlag::Destory)
					{
						continue;	// �폜�ς݂Ȃ̂Ŕ�΂�
					}
					// �R���C�_�[�P�ʂ̏Փ˔���
					PhysicsSystem::PhysicsEngine::GetInstance()->HandleWorldColliderCollision(&*a, &*b);
				}
			}
		}

	}

	/**
	* Transform���X�V
	*/
	void ObjectManager::UpdateTransform()
	{

		// ���[�J�����W�ϊ��s����X�V
		for (int i = 0; i < gameObjects.size(); ++i)
		{
			GameObjectPtr e = gameObjects[i];
			if (e->transform != nullptr)
			{
				e->transform->LocalTransformUpdate();
			}
		}

		// ���[���h���W�ϊ��s����v�Z
		std::vector<Matrix4x4> worldTransforms(gameObjects.size());
		std::vector<Matrix3x3> worldNormals(gameObjects.size());
		for (int i = 0; i < gameObjects.size(); ++i)
		{
			TransformPtr e = gameObjects[i]->transform;
			if (e != nullptr)
			{
				Matrix4x4 m = e->GetLocalTransformMatrix();
				Matrix3x3 n = e->GetNormalMatrix();
				for (e = e->GetParent(); e; e = e->GetParent())
				{
					m = e->GetLocalTransformMatrix() * m;
					n = e->GetNormalMatrix() * n;
				}
				worldTransforms[i] = m;
				worldNormals[i] = n;
			}
		}

		// ���[���h���W�ϊ��s����Q�[���I�u�W�F�N�g�ɐݒ�
		for (int i = 0; i < gameObjects.size(); ++i)
		{
			gameObjects[i]->transform->worldTransformMatrix = worldTransforms[i];
			gameObjects[i]->transform->normalMatrix = worldNormals[i];
		}

	}

	/**
	* MonoBehaviour�̍X�V
	*/
	void ObjectManager::UpdateMonoBehaviour()
	{
		// �X�^�[�g����
		for (auto x : gameObjects)
		{
			// �����Ă��Ȃ���Ή������Ȃ�
			if (x->monoBehaviours.empty())
			{
				continue;
			}
			for (auto mono : x->monoBehaviours)
			{
				if (!mono->isStart && mono->enabled)
				{
					mono->Start();
					mono->isStart = true;
				}
			}
		}

		// �X�V����
		for (auto x : gameObjects)
		{
			// �����Ă��Ȃ���Ή������Ȃ�
			if (x->monoBehaviours.empty())
			{
				continue;
			}
			for (auto mono : x->monoBehaviours)
			{
				if (mono->enabled && mono->isStart)
				{
					mono->Update();
				}
			}
		}

		// �X�V����2
		for (auto x : gameObjects)
		{
			// �����Ă��Ȃ���Ή������Ȃ�
			if (x->monoBehaviours.empty())
			{
				continue;
			}
			for (auto mono : x->monoBehaviours)
			{
				if (mono->enabled && mono->isStart)
				{
					mono->LateUpdate();
				}
			}
		}
	}

	/**
	* Rigidbody���X�V
	*/
	void ObjectManager::UpdateRigidbody()
	{
		for (auto x : gameObjects)
		{
			if (x->rigidbody)
			{
				x->rigidbody->GravityUpdate();
			}
		}
	}

	/**
	* �A�j���[�^�[���X�V
	*/
	void ObjectManager::UpdateAnimator()
	{
		for (auto x : gameObjects)
		{
			if (x->animator)
			{
				x->animator->Update();
			}
		}
	}

	/**
	* AudioSource���X�V
	*/
	void ObjectManager::UpdateAudioSource()
	{
		for (auto x : gameObjects)
		{
			// �����Ă��Ȃ���Ή������Ȃ�
			if (x->audioSources.empty())
			{
				continue;
			}
			for (auto audio : x->audioSources)
			{
				audio->Set3DSoundPos();
			}
		}
	}

	/**
	* �Q�[���I�u�W�F�N�g�̍폜����
	*/
	void ObjectManager::DestoryGameObject()
	{
		// �I�u�W�F�N�g�z�񂪂���Ȃ牽�����Ȃ�
		if (gameObjects.empty())
		{
			return;
		}

		// �j���\��Z���ŃQ�[���I�u�W�F�N�g�𕪂���
		const auto iter = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) { return !p->IsDestroyed(); });

		// �j���\��̔j�󎞊Ԃ�0�ȏ�Ȃ�^�C�}�[�����炷
		// 0�ȉ��Ȃ�j����Ԃɂ���
		for (auto i = iter; i < gameObjects.end(); ++i)
		{
			if (i->get()->destroyTime > 0)
			{
				i->get()->destroyTime -= Time::DeltaTime();
				if (i->get()->destroyTime <= 0)
				{
					i->get()->hideFlag = Object::HideFlag::Destory;
					isDestoryObject = true;
				}
			}
		}

		// �j����Ԃ̗L���ŃI�u�W�F�N�g�𕪂���
		auto iter2 = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) { return p->GetHideFlag() != Object::HideFlag::Destory; });

		// �j����Ԃ̃Q�[���I�u�W�F�N�g��ʂ̔z��Ɉړ�
		GameObjectList destroyList(
			std::move_iterator(iter2),
			std::move_iterator(gameObjects.end()));

		// �z�񂩂�ړ��ς݂̃Q�[���I�u�W�F�N�g���폜
		gameObjects.erase(iter2, gameObjects.end());

		for (auto& e : destroyList)
		{
			// ���g�̂��Q�[���I�u�W�F�N�g�j��
			e->gameObject = nullptr;

			// �j����Ԃ̃Q�[���I�u�W�F�N�g��OnDestory�����s
			for (auto x : e->monoBehaviours)
			{
				x->OnDestory();
			}
		}

		// �j��I�u�W�F�N�g���Ȃ��ɂ���
		isDestoryObject = false;
	}

	/**
	* �Q�[���I�u�W�F�N�g���쐬
	*
	* @param name �I�u�W�F�N�g�̖��O
	*
	* @return �쐬�����Q�[���I�u�W�F�N�g
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name)
	{
		auto obj = std::make_shared<GameObject>();

		// ���O��ݒ�
		obj->SetName(name);

		obj->gameObject = obj;

		// Transform��ǉ�
		obj->AddComponent<Transform>();

		// �Q�[���I�u�W�F�N�g�z��ɓo�^
		gameObjects.push_back(obj);

		// �쐬�����Q�[���I�u�W�F�N�g
		return obj;
	}

	/**
	* �Q�[���I�u�W�F�N�g���쐬
	*
	* @param name		�I�u�W�F�N�g�̖��O
	* @param transform	�I�u�W�F�N�g��Transfrom
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name, const TransformPtr transform)
	{
		// �Q�[���I�u�W�F�N�g���쐬
		auto obj = CreateGameObject(name);

		// Tranform��ݒ�

		// �ʒu
		obj->GetTransform()->position = transform->position;

		// ��]
		obj->GetTransform()->rotation = transform->rotation;

		// �g��k��
		obj->GetTransform()->scale = transform->scale;

		// �쐬�����Q�[���I�u�W�F�N�g
		return obj;
	}

	/**
	* �Q�[���I�u�W�F�N�g���쐬
	*
	* @param name �I�u�W�F�N�g�̖��O
	* @param
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name, const Vector3& position, const Quaternion& rotation)
	{
		// �Q�[���I�u�W�F�N�g���쐬
		auto obj = CreateGameObject(name);

		// �ʒu
		obj->GetTransform()->position = position;

		// ��]
		obj->GetTransform()->rotation = rotation;

		// �쐬�����Q�[���I�u�W�F�N�g
		return obj;
	}

}