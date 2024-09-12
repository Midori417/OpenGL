/**
* @file Component.h
*/
#ifndef FGENGINE_COMPONENT_H_INCLUDED
#define FGENGINE_COMPONENT_H_INCLUDED
#include "FGEngine/UsingNames/UsingGameObject.h"
#include "FGEngine/UsingNames/UsingComponent.h"
#include "FGEngine/UsingNames/UsingMath.h"
#include "FGEngine/UsingNames/UsingScene.h"
#include <string>

namespace FGEngine
{
	/**
	* �R���|�[�l���g�̊��N���X
	*/
	class Component
	{
		friend GameObject;
	protected:	// ���̃N���X�͎��̉����Ȃ�

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Component() = default;

		/**
		* �f�t�H���g�f�X�g���N�^
		*/
		virtual ~Component() = default;

	public:

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
		TransformPtr GetTransform() const;

		/**
		* T�^�̃R���|�[�l���g���擾
		*/
		template<typename T>
		std::shared_ptr<T> GetComponent() const;

		/**
		* Tag���擾
		*/
		std::string GetTag() const;

		/**
		* �Q�[���I�u�W�F�N�g�𐶐�����
		*/
		GameObjectPtr Instantate(const std::string& name);
		GameObjectPtr Instantate(const std::string& name, const TransformPtr transform);
		GameObjectPtr Instantate(const std::string& name, const Vector3& position, const Quaternion& rotation);
		GameObjectPtr Instantate(const std::string& name, const Vector3& position);

		/**
		* �j���\�肩�擾
		*
		* @return true �j���\��
		* @return false �j���\�肶��Ȃ�
		*/
		bool IsDestroyed() const;

		/**
		* �R���|�[�l���g�̃N���[�����쐬����
		*/
		virtual ComponentPtr Clone() const = 0;

	private:

		// �R���|�[�l���g�̏��L�I�u�W�F�N�g
		std::weak_ptr<GameObject> ownerObject;

		// true�Ȃ�j��\��
		bool isDestroyed = false;
	};
}
#endif // !FGENGINE_COMPONENT_H_INCLUDED