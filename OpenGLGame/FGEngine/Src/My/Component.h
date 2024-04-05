/**
* @file Component.h
*/
#ifndef FGENGINE_COMPONENT_H_INCLUDED
#define FGENGINE_COMPONENT_H_INCLUDED
#include "Object.h"

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
		friend GameObject;

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

		// �R���|�[�l���g�̏��L�I�u�W�F�N�g
		std::weak_ptr<GameObject> ownerObject;

		// ���L�I�u�W�F�N�g��Transform
		std::weak_ptr<Transform> transform;
	};
}
#endif // !FGENGINE_COMPONENT_H_INCLUDED