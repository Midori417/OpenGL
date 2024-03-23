/**
* @file Object.cpp
*/
#include "Object.h"
#include "GameObject.h"
#include "Transform.h"

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
	* @param name		�I�u�W�F�N�g�̖��O
	* @param transform	�I�u�W�F�N�g��Transform
	*
	* @return ���������I�u�W�F�N�g
	*/
	GameObjectPtr Object::Instantate(const std::string& name, const TransformPtr& transform)
	{
		return nullptr;
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
		return nullptr;
	}

	/**
	* �I�u�W�F�N�g�̏�Ԃ�j��\��ɂ���
	*
	* @param obj �j���\��ɂ���I�u�W�F�N�g
	* @parma t	�j�󂳂�鎞��
	*/
	void Object::Destory(Object* obj, float t)
	{
		// ���łɔj���\��
		if (obj->isDestoryed)
		{
			return;
		}

		// �j���\��ɂ���
		obj->isDestoryed = true;
		// �j�����Ԃ�ݒ�
		obj->destoryTime = t;
	}

}