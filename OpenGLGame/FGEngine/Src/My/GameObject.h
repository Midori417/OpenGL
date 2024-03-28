/**
* @file GameObject.h
*/
#pragma once
#include "Object.h"
#include "Component.h"
#include "Collider.h"
#include "MonoBehaviour.h"
#include "Transform.h"
#include "Renderer.h"
#include "Rigidbody.h"

namespace FGEngine
{
	/**
	* �Q�[���ɓo�ꂷ��l�X�ȃI�u�W�F�N�g�̊�{�N���X
	*/
	class GameObject : public Object
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		GameObject() = default;
		virtual ~GameObject() = default;

		// �R�s�[�Ƒ�����֎~
		GameObject(GameObject&) = delete;
		GameObject& operator=(GameObject&) = delete;

		// �Q�[���I�u�W�F�N�g�ɃR���|�[�l���g��ǉ�����
		template<class T>
		std::shared_ptr<T> AddComponent()
		{
			// �R���|�[�l���g�����N���X����Ȃ����nullptr��Ԃ�
			if constexpr (!std::is_base_of_v<Component, T>)
			{
				return nullptr;
			}

			// �R���|�[�l���g���쐬
			auto p = std::make_shared<T>;

			// Collider�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Collider, T>)
			{
				colliders.push_back(p);
			}

			// MonoBehaviour�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<MonoBehaviour, T>)
			{
				monoBehaviours.push_back(p);
				p->Awake();
			}

			// Transform�����N���X�̏ꍇ
			if constexpr (std::is_base_of_v<Transform, T>)
			{
				transform = p;
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

			p->SetName(ToString());
			// �R���|�[�l���g�z��ɓo�^
			components.push_back(p);
		}

		// �R���|�[�l���g����������
		template<class T>
		std::shared_ptr<T> GetComponent() const
		{
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

		// Transform���擾
		TransformPtr GetTransform() const
		{
			return transform;
		}

	public:

		std::string tag = "Untagged";		// �^�O
		bool isActive = true;				// �I�u�W�F�N�g���L�����ǂ���

	private:

		std::vector<ComponentPtr> components;			// �R���|�[�l���g�z��
		std::vector<ColliderPtr> colliders;				// �R���C�_�[�z��
		std::vector<MonoBehaviourPtr> monoBehaviours;	// 	�A�v���P�[�V�����R���|�[�l���g�z��
		TransformPtr transform;			// �g�����X�t�H�[���R���|�[�l���g�|�C���^�[
		RendererPtr renderer;			// �`��R���|�[�l���g�|�C���^�[
		RigidbodyPtr rigidbody;			// �����R���|�[�l���g�|�C���^�[

	};
	using GameObjectList = std::vector<GameObjectPtr>;
}