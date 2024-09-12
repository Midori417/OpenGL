/**
* @file Scene.cpp
*/
#include "FGEngine/Scene/Scene.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/Camera.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Component/MeshRenderer.h"
#include "FGEngine/MainSystem/PhysicsEngine.h"
#include "FGEngine/MainSystem/RenderingEngine.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Asset/Shader.h"
#include <algorithm>

namespace FGEngine
{
	/**
	* �Q�[���I�u�W�F�N�g���쐬
	*
	* @param name �I�u�W�F�N�g�̖��O
	*
	* @return �쐬�����Q�[���I�u�W�F�N�g
	*/
	GameObjectPtr Scene::CreateGameObject(const std::string& name)
	{
		auto obj = std::make_shared<GameObject>();

		// ���O��ݒ�
		obj->name = (name);

		obj->gameObject = obj;

		obj->ownerScene = this;

		// Transform��ǉ�
		obj->AddComponent<Transform>();

		// �Q�[���I�u�W�F�N�g�z��ɓo�^
		gameObjects.push_back(obj);

		// �쐬�����Q�[���I�u�W�F�N�g
		return obj;
	}

	/**
	* name�ɂ������I�u�W�F�N�g�𐶐�����
	*
	* @param name �����������I�u�W�F�N�g�̖��O
	* namespace CreateObject����I�𐄏�
	*
	* @return ���������I�u�W�F�N�g
	*/
	GameObjectPtr Scene::Create(const std::string& name)
	{
		if (name == CreateObject::Empty)
		{
			return CreateGameObject("GameObject");
		}
		else if (name == CreateObject::Camera)
		{
			GameObjectPtr p = CreateGameObject("Camera");
			CameraPtr camera = p->AddComponent<Camera>();

			// ���C���J���������݂��Ȃ��ꍇ�ݒ肷��
			SetMainCameraInfo(camera);

			return p;
		}
		else if (name == CreateObject::GameObject3D::Cube)
		{
			GameObjectPtr p = CreateGameObject("Cube");
			MeshRendererPtr mesh = p->AddComponent<MeshRenderer>();

			// ���b�V����ݒ肷��
			auto assetManger = AssetManager::GetInstance();
			mesh->mesh = assetManger->GetStaticMesh("Cube");
			mesh->shader = assetManger->GetShader(DefalutShader::Standard3D);
			mesh->shadowShader = assetManger->GetShader(DefalutShader::Shadow3D);

			return p;
		}
		else if (name == CreateObject::GameObject3D::Sphere)
		{
			GameObjectPtr p = CreateGameObject("Sphere");
			MeshRendererPtr mesh = p->AddComponent<MeshRenderer>();

			// ���b�V���𐶐�
			mesh->mesh = AssetManager::GetStaticMesh("Sphere");
			mesh->shader = AssetManager::GetShader(DefalutShader::Standard3D);
			mesh->shadowShader = AssetManager::GetShader(DefalutShader::Shadow3D);

			return p;
		}

		return nullptr;
	}

	/**
	* �Q�[���I�u�W�F�N�g���N���[������
	*
	* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
	*
	* @return �쐬�����Q�[���I�u�W�F�N�g
	*/
	GameObjectPtr Scene::CloneGameObject(const GameObjectPtr& gameObject)
	{
		GameObjectPtr p = GameObject::CloneGameObject(gameObject);

		// �V�[����ݒ肷��
		p->ownerScene = this;

		// �z��ɒǉ�
		gameObjects.push_back(p);

		return p;
	}

	/**
	* �Q�[���I�u�W�F�N�g���N���[������
	*
	* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
	* @param transform	�N���[������g�����X�t�H�[��
	*
	* @return �쐬�����Q�[���I�u�W�F�N�g
	*/
	GameObjectPtr Scene::CloneGameObject(const GameObjectPtr& gameObject, const TransformPtr& tranform)
	{
		GameObjectPtr p = GameObject::CloneGameObject(gameObject, tranform);

		// �V�[����ݒ肷��
		p->ownerScene = this;

		// �z��ɒǉ�
		gameObjects.push_back(p);

		return p;
	}

	/**
	* �Q�[���I�u�W�F�N�g���N���[������
	*
	* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
	* @param position	�N���[���������̈ʒu
	* @param rotation	�N���[���������̉�]
	*
	* @return �쐬�����Q�[���I�u�W�F�N�g
	*/
	GameObjectPtr Scene::CloneGameObject(const GameObjectPtr& gameObject, const Vector3& position, const Quaternion& rotation)
	{
		GameObjectPtr p = CloneGameObject(gameObject);

		// �ʒu�Ɖ�]��ݒ�
		TransformPtr transform = p->GetTransform();
		transform->position = position;
		transform->rotation = rotation;

		// �z��ɒǉ�
		gameObjects.push_back(p);

		return p;
	}

	/**
	* �S�ẴQ�[���I�u�W�F�N�g���폜����
	*/
	void Scene::AllClearGameObject()
	{
		gameObjects.clear();
	}

	/**
	* �J�����R���|�[�l���g���擾
	*/
	CameraPtr Scene::GetMainCameraInfo() const
	{
		return mainCamera;
	}

	/**
	* ���C���J������ݒ�
	*
	* @param camera �ݒ肷��J����
	*/
	void Scene::SetMainCameraInfo(const CameraPtr& camera)
	{
		mainCamera = camera;
	}

	/**
	* �������̏���
	*/
	void Scene::Awake()
	{
		// �Q�[���I�u�W�F�N�g�z���\��
		gameObjects.reserve(1000);
	}

	/**
	* ���t���[�����̏���
	*/
	void Scene::Update()
	{
		if (!gameObjects.empty())
		{
			UpdateGameEvent();
			UpdateAudioSource();
			UpdateRigidbody();
			UpdateTransform();
			CollisionGameObject();
			// �Փˌ�̍��W�ɍX�V���������������x�Ăяo��
			UpdateTransform();
			UpdateAnimator();

			DestoryGameObject();
		}
	}

	/**
	* ���t���[���`�悷��
	*/
	void Scene::Render()
	{
		RendererGameObject();
		UIRendererGameObject();
	}

	/**
	* �I�����̏���
	*/
	void Scene::Fainalize()
	{
		AllClearGameObject();
	}


	/**
	* �Q�[���C�x���g�̍X�V
	*/
	void Scene::UpdateGameEvent()
	{
		// Start�C�x���g
		for (auto& x : gameObjects)
		{
			if (x->isActive)
			{
				// �C�x���g���Ȃ���Ή����X�L�b�v����
				if (x->gameEvents.empty())
				{
					continue;
				}

				for (auto& e : x->gameEvents)
				{
					// ��x�����֐������s
					if (e->isActive && !e->isStart)
					{
						e->Start();
						e->isStart = true;
					}
				}
			}
		}

		// Update�C�x���g
		for (auto& x : gameObjects)
		{
			if (x->isActive)
			{
				// �C�x���g���Ȃ���Ή����X�L�b�v����
				if (x->gameEvents.empty())
				{
					continue;
				}

				for (auto& e : x->gameEvents)
				{
					if (e->isActive && e->isStart)
					{
						e->Update();
					}
				}
			}
		}

		// LateUpdate�C�x���g
		for (auto& x : gameObjects)
		{
			if (x->isActive)
			{
				// �C�x���g���Ȃ���Ή����X�L�b�v����
				if (x->gameEvents.empty())
				{
					continue;
				}

				for (auto& e : x->gameEvents)
				{
					if (e->isActive && e->isStart)
					{
						e->LateUpdate();
					}
				}
			}
		}
	}

	/**
	* Animator���X�V
	*/
	void Scene::UpdateAnimator()
	{
		for (auto& x : gameObjects)
		{
			auto e = x->animator;
			if (e)
			{
				e->Update();
			}
		}
	}

	/**
	* AudioSource���X�V
	*/
	void Scene::UpdateAudioSource()
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
	* �g�����X�t�H�[�����X�V
	*/
	void Scene::UpdateTransform()
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
	* ���W�b�h�{�f�B���X�V
	*/
	void Scene::UpdateRigidbody()
	{
		for (auto& x : gameObjects)
		{
			if (x->isActive)
			{
				auto e = x->rigidbody;
				if (e)
				{
					e->GravityUpdate();
				}
			}
		}
	}

	/**
	* �Q�[���I�u�W�F�N�g�̏Փˏ����̏���
	*/
	void Scene::CollisionGameObject()
	{
		// ���[���h���W�n�̏Փ˔�����쐬
		std::vector<WorldColliderList> colliders;
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
			WorldColliderList list(e->colliders.size());
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
				if (goA->GetState() == GameObjectState::Destroyed)
				{
					continue;	// �폜�ς݂Ȃ̂Ŕ�΂�
				}
				for (auto b = a + 1; b != colliders.end(); ++b)
				{
					const GameObjectPtr goB = b->at(0).origin->OwnerObject();
					if (goB->GetState() == GameObjectState::Destroyed)
					{
						continue;	// �폜�ς݂Ȃ̂Ŕ�΂�
					}
					// �R���C�_�[�P�ʂ̏Փ˔���
					PhysicsEngine::GetInstance()->HandleWorldColliderCollision(&*a, &*b);
				}
			}
		}
	}

	/**
	* �Q�[���I�u�W�F�N�g�̕`�揈���̏���
	*/
	void Scene::RendererGameObject()
	{
		// �V�F�[�_�̎d����
		auto resouceManager = AssetManager::GetInstance();
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
				float fovScale = mainCamera->GetFovScale();
				float aspectRatio = mainCamera->aspect;
				prog->SetFloat4("aspectRatioAndScaleFov", 1 / aspectRatio, fovScale, mainCamera->near, mainCamera->far);

				// �J�����̈ʒu�Ɖ�]�ƃX�P�[���̊i�[��
				Vector3 pos;
				Vector3 scale;
				Matrix3x3 rot;

				// �J�����̍��W�ϊ��s��𕪉�
				Matrix4x4::Decompose(mainCamera->GetTransform()->GetWorldTransformMatrix(), pos, scale, rot);

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
		RenderingEngine::GetInstance()->DrawGameObject(rendererList, mainCamera);
	}

	/**
	* �Q�[���I�u�W�F�N�g��UI�`�揈��
	*/
	void Scene::UIRendererGameObject()
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
	* �Q�[���I�u�W�F�N�g�̔j������
	*/
	void Scene::DestoryGameObject()
	{
		// �j���\��̃R���|�[�l���g���폜
		for (auto& x : gameObjects)
		{
			x->DestroyComponent();
		}

		// �j����Ԃ̍X�V
		for (auto& x : gameObjects)
		{
			x->UpdateDestroyTime();
		}

		// �j���\��ŃQ�[���I�u�W�F�N�g�𕪂���
		const auto iter = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) {
				return p->GetState() != GameObjectState::Destroyed;
			});

		// �j���̃Q�[���I�u�W�F�N�g
		GameObjectList destroyList(
			std::move_iterator(iter),
			std::move_iterator(gameObjects.end()));

		// �z�񂩂�ړ��ς݂̃Q�[���I�u�W�F�N�g���폜
		gameObjects.erase(iter, gameObjects.end());

		// �폜�C�x���g
		for (auto& x : destroyList)
		{
			if (x->gameEvents.empty())
			{
				continue;
			}
			for (auto& event : x->gameEvents)
			{
				event->OnDestroy();
			}
		}
	}
}