/**
* @file GameObject.h
*/
#ifndef FGENGINE_GAMEOBJECT_H_INCLUDED
#define FGENGINE_GAMEOBJECT_H_INCLUDED
#include "Object.h"
#include "Component.h"
#include "Collider.h"
#include "MonoBehaviour.h"
#include "Transform.h"
#include "Renderer.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Camera.h"
#include "ImGuiLayout.h"

namespace FGEngine
{
	/**
	* �Q�[���ɓo�ꂷ��l�X�ȃI�u�W�F�N�g�̊�{�N���X
	*/
	class GameObject : public Object
	{
	public:
		
		friend ObjectSystem::ObjectManager;
		friend RenderingSystem::RenderingEngine;
		friend PhysicsSystem::PhysicsEngine;
		friend Collider;

		// �R���X�g���N�^�E�f�X�g���N�^
		GameObject() = default;
		virtual ~GameObject() = default;

		// �R�s�[�Ƒ�����֎~
		GameObject(GameObject&) = delete;
		GameObject& operator=(GameObject&) = delete;

		/**
		* T�^�̃R���|�[�l���g���Q�[���I�u�W�F�N�g�ɒǉ�
		*/
		template<class T>
		std::shared_ptr<T> AddComponent()
		{
			// �R���|�[�l���g�����N���X����Ȃ����nullptr��Ԃ�
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}

			// �R���|�[�l���g���쐬
			auto p = std::make_shared<T>();

			// �e�I�u�W�F�N�g��ݒ�
			p->ownerObject = gameObject;

			// ���O��ݒ�
			p->SetName(ToString());

			// Transform�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				transform = p;
			}

			// Collider�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Collider, T>)
			{
				colliders.push_back(p);
			}

			// MonoBehaviour�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<MonoBehaviour, T>)
			{
				monoBehaviours.push_back(p);
				// �������������s
				monoBehaviours.back()->Awake();
			}


			// Renderer�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Renderer, T>)
			{
				renderer = p;
			}

			// Rigidbody�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Rigidbody, T>)
			{
				rigidbody = p;
			}
			// Camera�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Camera, T>)
			{
				camera = p;
			}
			// Animator�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Animator, T>)
			{
				animator = p;
			}

			// ImGuiLayout�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<UI::ImGuiLayout, T>)
			{
				imGuiLayout = p;
			}

			// �R���|�[�l���g�z��ɓo�^
			components.push_back(p);

			return p;
		}

		/**
		* T�^�̃R���|�[�l���g���擾
		*/
		template<class T>
		std::shared_ptr<T> GetComponent() const
		{
			// �R���|�[�l���g�����N���X����Ȃ����nullptr��Ԃ�
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}
			// Transform�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				return transform;
			}
			// Renderer�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Renderer, T>)
			{
				return renderer;
			}

			// Rigidbody�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Rigidbody, T>)
			{
				return rigidbody;
			}
			// Camera�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Camera, T>)
			{
				return camera;
			}
			// Animator�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Animator, T>)
			{
				return animator;
			}

			// ImGuiLayout�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<UI::ImGuiLayout, T>)
			{
				return imGuiLayout;
			}


			for (auto& e : components)
			{
				// T�^�ɃA�b�v�L���X�g���Ă���ꍇ�擾����
				auto p = std::dynamic_pointer_cast<T>(e);
				if (p)
				{
					// ���������R���|�[�l���g
					return p;
				}
			}
			// �����Ȃ�����
			return nullptr;
		}

		/**
		* T�^�̃R���|�[�l���g���폜���� 
		*/
		template<class T>
		void RemoveComponent() const
		{
			// �R���|�[�l���g�����N���X����Ȃ����nullptr��Ԃ�
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}


			// �R���|�[�l���g���擾
			auto com = GetComponent<T>();

			// �j���\��ɂ���
			Destory(com);
		}

		/**
		* �g�����X�t�H�[���R���|�[�l���g���擾
		*/
		TransformPtr GetTransform() const
		{
			return transform;
		}

	private:

		/**
		* �폜�\��̃R���|�[�l���g���폜
		*/
		void DestroyComponent();

	public:

		// �I�u�W�F�N�g���L�����ǂ���
		bool isActive = true;

		// �^�O
		std::string tag = "Untagged";


	private:

		// ���g���Ǘ�����|�C���^�[
		GameObjectPtr gameObject;

		// �R���|�[�l���g�z��
		std::vector<ComponentPtr> components;

		// �R���C�_�[�z��
		std::vector<ColliderPtr> colliders;

		// 	���m�r�w�C�r�A�z��
		std::vector<MonoBehaviourPtr> monoBehaviours;

		// �g�����X�t�H�[���R���|�[�l���g�|�C���^�[
		TransformPtr transform;

		// �`��R���|�[�l���g�|�C���^�[
		RendererPtr renderer;	

		// �����R���|�[�l���g�|�C���^�[
		RigidbodyPtr rigidbody;

		// �J�����R���|�[�l���g�|�C���^�[
		CameraPtr camera;

		// �A�j���[�^�R���|�[�l���g�|�C���^�[
		AnimatorPtr animator;

		// UI���C�A�E�g�R���|�[�l���g�|�C���^�[
		UI::ImGuiLayoutPtr imGuiLayout;

	};
	using GameObjectList = std::vector<GameObjectPtr>;
}
#endif // !FGENGINE_GAMOBJECYT_H_INCLUDED
