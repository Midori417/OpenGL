/**
* @file Component.h
*/
#pragma once
#include "Object.h"
#include <memory>

namespace FGEngine
{
	// ��s�錾
	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
	class Component;
	using ComponentPtr = std::shared_ptr<Component>;
	class Transform;

	/**
	* �R���|�[�l���g�̊��N���X
	*/
	class Component : public Object
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Component() = default;
		virtual ~Component() = default;

		/**
		* �R���|�[�l���g�����L���Ă���I�u�W�F�N�g���擾
		*/
		GameObjectPtr OwnerObject() const
		{
			auto ptr = ownerObject.lock();
			if (!ptr)
			{
				return nullptr;
			}
			return ptr;
		}

		/**
		* �g�����X�t�H�[�����擾
		*/
		TransformPtr GetTransform() const
		{
			auto ptr = transform.lock();
			if (!ptr)
			{
				return nullptr;
			}
			return ptr;
		}

		/**
		* T�^�̃R���|�[�l���g���擾
		*/
		template<typename T>
		std::shared_ptr<T> GetComponent() const;

		/**
		* �e��T�^�̃R���|�[�l���g���擾
		*/
		template<typename T>
		std::shared_ptr<T> GetComponentInChildren() const;

		/**
		* �q��T�^�̃R���|�[�l���g���擾
		*/
		template<typename T>
		std::shared_ptr<T> GetComponentInParent() const;

		/**
		* Tag���擾
		*/
		std::string GetTag() const;

	private:

		std::weak_ptr<GameObject> ownerObject;		// �R���|�[�l���g�̏��L�I�u�W�F�N�g
		std::weak_ptr<Transform> transform;			// ���L�I�u�W�F�N�g��Transform
	};
}