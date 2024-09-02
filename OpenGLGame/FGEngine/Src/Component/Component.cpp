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
	* �Q�[���I�u�W�F�N�g�𐶐�����
	*
	* @param name�@�I�u�W�F�N�g�̖��O
	*
	* @return ���������I�u�W�F�N�g
	*/
	GameObjectPtr Component::Instantate(const std::string& name)
	{
		auto obj = OwnerObject()->GetScene()->Create(CreateObject::Empty);
		obj->name = name;

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
	GameObjectPtr Component::Instantate(const std::string& name, const TransformPtr transform)
	{
		auto obj = Instantate(name);
		obj->GetTransform()->position = transform->position;
		obj->GetTransform()->rotation = transform->rotation;

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
	GameObjectPtr Component::Instantate(const std::string& name, const Vector3& position, const Quaternion& rotation)
	{
		auto obj = Instantate(name);
		obj->GetTransform()->position = position;
		obj->GetTransform()->rotation = rotation;

		return obj;
	}

	GameObjectPtr Component::Instantate(const std::string& name, const Vector3& position)
	{
		return Instantate(name, position, Quaternion::identity);
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
}