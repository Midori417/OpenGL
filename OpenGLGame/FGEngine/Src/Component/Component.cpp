/**
* @file Component.cpp
*/
#include "FGEngine/Component/Component.h"
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
		auto obj = OwnerObject()->GetScene()->CreateGameObject(name);

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
		auto obj = OwnerObject()->GetScene()->CreateGameObject(name, transform);

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
		auto obj = OwnerObject()->GetScene()->CreateGameObject(name, position, rotation);

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