/**
* @file GameObject.h
*/
#ifndef FGENGINE_GAMEOBJECT_H_INCLUDED
#define FGENGINE_GAMEOBJECT_H_INCLUDED
#include "FGEngine/UsingNames/UsingGameObject.h"
#include "FGEngine/UsingNames/UsingComponent.h"
#include "FGEngine/UsingNames/UsingScene.h"
#include "FGEngine/Component/Component.h"
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Component/ImGuiLayout.h"
#include <string>

namespace FGEngine
{
	/**
	* �Q�[���I�u�W�F�N�g�̏��
	*/
	enum GameObjectState
	{
		// �ʏ�
		None,

		// �j������
		DestroyTime,

		// �j���\��
		Destroyed,
	};

	/**
	* �Q�[���I�u�W�F�N�g
	*/
	class GameObject 
	{
		friend Scene;
		friend class RenderingEngine;
		friend class PhysicsEngine;
	public:	// �R���X�g���N�^�E�f�X�g���N�^
		
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		GameObject() = default;

		/**
		* �f�t�H���g�f�X�g���N�^
		*/
		virtual ~GameObject() = default;
						
	public:	// �֎~����

		// �R�s�[���֎~
		GameObject(GameObject&) = delete;

		// ������֎~
		GameObject& operator=(GameObject&) = delete;

	public:

		/**
		* �Q�[���I�u�W�F�N�g�𐶐�
		*
		* @param name �Q�[���I�u�W�F�N�g�̖��O
		*/
		static GameObjectPtr Create(const std::string& name);

	public:	// �R���|�[�l���g�̑���

		/**
		* T�^�̃R���|�[�l���g���Q�[���I�u�W�F�N�g�ɒǉ�
		*/
		template<class T>
		std::shared_ptr<T> AddComponent()
		{
			// T���R���|�[�l���g�̊��N���X����Ȃ���Ή������Ȃ�
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}

			// �R���|�[�l���g���쐬
			auto p = std::make_shared<T>();

			// �R���|�[�l���g�̏��L�҂�ݒ�
			p->ownerObject = gameObject;

			// T���g�����X�t�H�[���̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				transform = p;
			}

			// T�������_���[�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Renderer, T>)
			{
				renderer = p;
			}

			// T�����W�b�h�{�f�B�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Rigidbody, T>)
			{
				rigidbody = p;
			}

			// T���J�����R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Camera, T>)
			{
				camera = p;
			}

			// T���A�j���[�^�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Animator, T>)
			{
				animator = p;
			}

			// T��imGUI�R���|�[�l���g�̊��N���X
			if constexpr (std::is_base_of_v<ImGuiLayout, T>)
			{
				imGuiLayout = p;
			}

			// T���R���C�_�[�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Collider, T>)
			{
				colliders.push_back(p);
			}

			// T���Q�[���C�x���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<GameEvent, T>)
			{
				gameEvents.push_back(p);
				// �����C�x���g���s
				gameEvents.back()->Awake();
			}

			// T���I�E�f�B�I�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<AudioSource, T>)
			{
				audioSources.push_back(p);
			}

			// �쐬�����R���|�[�l���g��ǉ�
			return p;
		}

		/**
		* T�^�̃R���|�[�l���g���擾
		*/
		template<class T>
		std::shared_ptr<T> GetComponent() const
		{
			// T���R���|�[�l���g�̊��N���X����Ȃ���Ή������Ȃ�
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}

			// T���g�����X�t�H�[���̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				return std::dynamic_pointer_cast<T>(transform);
			}

			// T�������_���[�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Renderer, T>)
			{
				return std::dynamic_pointer_cast<T>(renderer);
			}

			// T�����W�b�h�{�f�B�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Rigidbody, T>)
			{
				return std::dynamic_pointer_cast<T>(rigidbody);
			}

			// T���J�����R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Camera, T>)
			{
				return std::dynamic_pointer_cast<T>(camera);
			}

			// T���A�j���[�^�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Animator, T>)
			{
				return std::dynamic_pointer_cast<T>(animator);
			}

			// T��imGUI�R���|�[�l���g�̊��N���X
			if constexpr (std::is_base_of_v<ImGuiLayout, T>)
			{
				return std::dynamic_pointer_cast<T>(imGuiLayout);
			}

			// T���R���C�_�[�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Collider, T>)
			{
				for (auto& x : colliders)
				{
					auto p = std::dynamic_pointer_cast<T>(x);
					if (p)
					{
						return p;
					}
				}
			}

			// T���Q�[���C�x���g�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<GameEvent, T>)
			{
				for (auto& x : gameEvents)
				{
					auto p = std::dynamic_pointer_cast<T>(x);
					if (p)
					{
						return p;
					}
				}
			}

			// T���I�E�f�B�I�R���|�[�l���g�̊��N���X�̏ꍇ
			if constexpr (std::is_base_of_v<AudioSource, T>)
			{
				for (auto& x : audioSources)
				{
					auto p = std::dynamic_pointer_cast<T>(x);
					if (p)
					{
						return p;
					}
				}
			}

			// �R���|�[�l���g��������Ȃ�����
			return nullptr;
		}

		/**
		* T�^�̃R���|�[�l���g���폜���� 
		*/
		template<class T>
		void RemoveComponent() const
		{
			auto p = GetComponent<T>();

			// �擾�����R���|�[�l���g��j���\��ɂ���
			if (p)
			{
				p->isDestroyed = true;
			}
		}

	public:

		/**
		* �Q�[���I�u�W�F�N�g�̏�Ԃ��擾
		*/
		GameObjectState GetState() const;

		/**
		* �V�[�����擾
		*/
		Scene* GetScene() const;

		/**
		* �g�����X�t�H�[���R���|�[�l���g���擾
		*/
		TransformPtr GetTransform() const;

		/**
		* �Q�[���I�u�W�F�N�g��j������
		* 
		* @param destroyTime �j���܂ł̎���
		*/
		void Destroy(float destroyTime = 0);

	public:

		/**
		* �N���[�������Q�[���I�u�W�F�N�g���擾����
		* 
		* @param object �N���[�����Ƃ̃I�u�W�F�N�g
		* @oaram trasnform �N���[������g�����X�t�H�[��
		* 
		* @return �N���[�������Q�[���I�u�W�F�N�g
		*/
		static GameObjectPtr Clone(const GameObjectPtr& object, const TransformPtr& transform = nullptr);

	private:

		/**
		* ��Ԃ��j���҂��Ȃ�j�����Ԃ��X�V
		*/
		void UpdateDestroyTime();

		/**
		* �폜�\��̃R���|�[�l���g���폜
		*/
		void DestroyComponent();

	public:

		// �I�u�W�F�N�g�̖��O
		std::string name = "GameObject";

		// �I�u�W�F�N�g���L�����ǂ���
		bool isActive = true;

		// �^�O
		std::string tag = "None";

	private:

		// ���g���Ǘ�����|�C���^�[
		std::weak_ptr<GameObject> gameObject;

		// ���g���Ǘ�����V�[��
		Scene* ownerScene;

		// ���
		GameObjectState state = GameObjectState::None;

		// �j���܂ł̎���
		float destroyTime = 0;

	private:	// �R���|�[�l���g�ϐ�

		// �g�����X�t�H�[���R���|�[�l���g�|�C���^�[
		TransformPtr transform;

		// �`��R���|�[�l���g�|�C���^�[
		RendererPtr renderer;	

		// �����R���|�[�l���g�|�C���^�[
		RigidbodyPtr rigidbody;

		// �A�j���[�^�R���|�[�l���g�|�C���^�[
		AnimatorPtr animator;

		// �J�����R���|�[�l���g�|�C���^�[
		CameraPtr camera;

		// UI���C�A�E�g�R���|�[�l���g�|�C���^�[
		ImGuiLayoutPtr imGuiLayout;

		// �R���C�_�[�z��
		std::vector<ColliderPtr> colliders;

		// 	�Q�[���C�x���g�z��
		std::vector<GameEventPtr> gameEvents;

		// AudioSource�R���|�[�l���g�z��
		std::vector<AudioSourcePtr> audioSources;
	};
}
#endif // !FGENGINE_GAMOBJECYT_H_INCLUDED
