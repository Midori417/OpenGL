/**
* @file Component.cpp
*/
#include "FGEngine/Component/Component.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Scene/Scene.h"
#include "FGEngine/Math/Quaternion.h"

namespace FGEngine
{
	/**
	* ���g�����L���Ă���I�u�W�F�N�g���擾
	*/
	GameObjectPtr Component::OwnerObject() const
	{
		auto ptr = ownerObject.lock();
		if (!ptr)
		{
			return nullptr;
		}
		return ptr;
	}

	/**
	* Transform���擾
	*/
	TransformPtr Component::GetTransform() const
	{
		GameObjectPtr obj = OwnerObject();
		if (!obj)
		{
			return nullptr;
		}

		return obj->GetTransform();
	}

	/**
	* Tag���擾
	*/
	std::string Component::GetTag() const
	{
		GameObjectPtr obj = OwnerObject();
		if (!obj)
		{
			return "";
		}

		return obj->tag;
	}

	/**
	* �j���\�肩�擾
	*
	* @return true �j���\��
	* @return false �j���\�肶��Ȃ�
	*/
	bool Component::IsDestroyed() const
	{
		return isDestroyed;
	}

#pragma region Instantate

	/**
	* type�ɂ������I�u�W�F�N�g�𐶐�����
	*
	* @param type �����������I�u�W�F�N�g�̃^�C�v
	* namespace CreateObject����I�𐄏�
	*
	* @return ���������I�u�W�F�N�g
	*/
	GameObjectPtr Component::Instantate(const std::string& type)
	{
		auto owner = OwnerObject();
		if (!owner)
		{
			return nullptr;
		}

		auto scene = owner->GetScene();
		if (!scene)
		{
			return nullptr;
		}

		auto obj = scene->Instantate(type);

		return obj;
	}

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
	GameObjectPtr Component::Instantate(const std::string& type, const Vector3& position, const Quaternion& rotation)
	{
		auto obj = Instantate(type);
		if (!obj)
		{
			return nullptr;
		}

		obj->GetTransform()->position = position;
		obj->GetTransform()->rotation = rotation;

		return obj;
	}

	/**
	* gameObject�̃N���[�����쐬
	*
	* @param gameObject �N���[�����Ƃ̃Q�[���I�u�W�F�N�g
	*
	* @return ���������Q�[���I�u�W�F�N�g
	*/
	GameObjectPtr Component::Instantate(const GameObjectPtr& gameObject)
	{
		// �N���[���������݂��Ȃ��ꍇ�͉������Ȃ�
		if (!gameObject)
		{
			return nullptr;
		}

		auto obj = OwnerObject();
		if (!obj)
		{
			return nullptr;
		}

		auto scene = obj->GetScene();
		if (!scene)
		{
			return nullptr;
		}

		return scene->Instantate(gameObject);
	}

	/**
	* gameObject�̃N���[�����쐬
	*
	* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
	* @param transform	�N���[������g�����X�t�H�[��
	*
	* @return �쐬�����Q�[���I�u�W�F�N�g
	*/
	GameObjectPtr Component::Instantate(const GameObjectPtr& gameObject, const TransformPtr& tranform)
	{
		// �N���[���������݂��Ȃ��ꍇ�͉������Ȃ�
		if (!gameObject)
		{
			return nullptr;
		}

		auto obj = OwnerObject();
		if (!obj)
		{
			return nullptr;
		}

		auto scene = obj->GetScene();
		if (!scene)
		{
			return nullptr;
		}

		return scene->Instantate(gameObject, tranform);
	}

	/**
	* gameObject�̃N���[�����쐬
	*
	* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
	* @param position	�N���[���������̈ʒu
	* @param rotation	�N���[���������̉�]
	*
	* @return �쐬�����Q�[���I�u�W�F�N�g
	*/
	GameObjectPtr Component::Instantate(const GameObjectPtr& gameObject, const Vector3& position, const Quaternion& rotation)
	{
		// �N���[���������݂��Ȃ��ꍇ�͉������Ȃ�
		if (!gameObject)
		{
			return nullptr;
		}

		auto owner = OwnerObject();
		if (!owner)
		{
			return nullptr;
		}

		auto scene = owner->GetScene();
		if (!scene)
		{
			return nullptr;
		}

		auto obj = scene->Instantate(gameObject);

		// �g�����X�t�H�[�����擾���Ĉʒu�Ɖ�]��ݒ�
		auto transform = obj->GetTransform();
		transform->position = position;
		transform->rotation = rotation;

		return obj;
	}

#pragma endregion

}