/**
* @file Object.cpp
*/
#include "Object.h"
#include "GameObject.h"
#include "ObjectManager.h"

namespace FGEngine
{
	/**
	* �I�u�W�F�N�g�̖��O���擾����
	*/
	std::string Object::ToString() const
	{
		return name;
	}

	/**
	* �I�u�W�F�N�g�̖��O��ݒ肷��
	*
	* @param value �ݒ肷�閼�O
	*/
	void Object::SetName(const std::string& value)
	{
		name = value;
	}

	/**
	* �I�u�W�F�N�g�̏�Ԃ��擾
	*/
	Object::HideFlag Object::GetHideFlag() const
	{
		return hideFlag;
	}

	/**
	* �Q�[���I�u�W�F�N�g�𐶐�����
	* 
	* @param name�@�I�u�W�F�N�g�̖��O
	* 
	* @return ���������I�u�W�F�N�g
	*/
	GameObjectPtr Object::Instantate(const std::string& name)
	{
		auto obj = ObjectSystem::ObjectManager::GetInstance()->CreateGameObject(name);

		return obj;
	}

	/**
	* �Q�[���I�u�W�F�N�g�𐶐�����
	*
	* @param name		�I�u�W�F�N�g�̖��O
	* @param transform	�I�u�W�F�N�g��Transform
	*
	* @return ���������I�u�W�F�N�g
	*/
	GameObjectPtr Object::Instantate(const std::string& name, const Transform& transform)
	{
		auto obj = ObjectSystem::ObjectManager::GetInstance()->CreateGameObject(name, transform);

		return obj;
	}

	/**
	* �Q�[���I�u�W�F�N�g�𐶐�����
	*
	* @param name		�I�u�W�F�N�g�̖��O
	* @param position	��������ʒu
	* @param rotation	���������Ƃ��̉�]�x
	*
	* @return ���������I�u�W�F�N�g
	*/
	GameObjectPtr Object::Instantate(const std::string& name, const Vector3& position, const Quaternion& rotation)
	{
		auto obj = ObjectSystem::ObjectManager::GetInstance()->CreateGameObject(name, position, rotation);

		return obj;
	}

	/**
	* �I�u�W�F�N�g�̏�Ԃ�j��\��ɂ���
	*
	* @param obj �j���\��ɂ���I�u�W�F�N�g
	* @parma t	�j�󂳂�鎞��
	*/
	void Object::Destory(ObjectPtr obj, float t)
	{
		// ���łɔj���\��
		if (obj->isDestroyed)
		{
			return;
		}

		// �j���\��ɂ���
		obj->isDestroyed = true;

		if (t > 0)
		{
			// �j�����Ԃ�ݒ�
			obj->destroyTime = t;
		}
		else
		{
			obj->hideFlag = HideFlag::Destory;
		}
	}

}