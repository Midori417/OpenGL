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
		* ���g�����L���Ă���I�u�W�F�N�g���擾
		*/
		GameObjectPtr OwnerObject() const;

		/**
		* �g�����X�t�H�[�����擾
		*/
		TransformPtr GetTransform() const;

		/**
		* Tag���擾
		*/
		std::string GetTag() const;

		/**
		* T�^�̃R���|�[�l���g���擾
		*/
		template<typename T>
		std::shared_ptr<T> GetComponent() const;

		/**
		* �j���\�肩�擾
		*
		* @return true �j���\��
		* @return false �j���\�肶��Ȃ�
		*/
		bool IsDestroyed() const;

	public:	// �I�u�W�F�N�g�̐���

		/**
		* type�ɂ������I�u�W�F�N�g�𐶐�����
		*
		* @param type �����������I�u�W�F�N�g�̃^�C�v
		* namespace CreateObject����I�𐄏�
		*
		* @return ���������I�u�W�F�N�g
		*/
		GameObjectPtr Instantate(const std::string& type);

		/**
		* type�ɂ������I�u�W�F�N�g�𐶐�����
		*
		* @param type �����������I�u�W�F�N�g�̃^�C�v
		* namespace CreateObject����I�𐄏�
		* @param position �ʒu
		* @param rotation ��]
		*
		* @return ���������I�u�W�F�N�g
		*/
		GameObjectPtr Instantate(const std::string& type, const Vector3& position, const Quaternion& rotation);

		/**
		* gameObject�̃N���[�����쐬
		* 
		* @param gameObject �N���[�����Ƃ̃Q�[���I�u�W�F�N�g
		* 
		* @return ���������Q�[���I�u�W�F�N�g
		*/
		GameObjectPtr Instantate(const GameObjectPtr& gameObject);

		/**
		* gameObject�̃N���[�����쐬
		*
		* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
		* @param transform	�N���[������g�����X�t�H�[��
		*
		* @return �쐬�����Q�[���I�u�W�F�N�g
		*/
		GameObjectPtr Instantate(const GameObjectPtr& gameObject, const TransformPtr& tranform);

		/**
		* gameObject�̃N���[�����쐬
		*
		* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
		* @param position	�N���[���������̈ʒu
		* @param rotation	�N���[���������̉�]
		*
		* @return �쐬�����Q�[���I�u�W�F�N�g
		*/
		GameObjectPtr Instantate(const GameObjectPtr& gameObject, const Vector3& position, const Quaternion& rotation);

	protected:

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