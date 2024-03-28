/**
* @file ObjectManager.cpp
*/
#include "ObjectManager.h"
#include "Time.h"
#include <algorithm>


namespace FGEngine
{
	/**
	* �I�u�W�F�N�g�}�l�[�W���[��������
	*
	* @retval 0		����ɏ�����
	* @retval 0�ȊO ���������s
	*/
	int ObjectManager::Initialize()
	{
		// �Q�[���I�u�W�F�N�g�z��̗e�ʂ���\��
		gameObjects.reserve(1000);

		return 0;
	}

	/**
	* �I�u�W�F�N�g�}�l�[�W���[���X�V
	*/
	void ObjectManager::Update()
	{
	}

	void ObjectManager::UpdateGameObject()
	{
	}

	void ObjectManager::UpdateTransform()
	{
	}

	void ObjectManager::UpdateRenderer()
	{
	}

	void ObjectManager::UpdateRigidbody()
	{
	}

	/**
	* �Q�[���I�u�W�F�N�g�̍폜����
	*/
	void ObjectManager::DestoryGameObject()
	{
		// �I�u�W�F�N�g�z�񂪂���Ȃ牽�����Ȃ�
		if (gameObjects.empty())
		{
			return;
		}

		// �j���\��Z���ŃQ�[���I�u�W�F�N�g�𕪂���
		const auto iter = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) { return !p->IsDestroyed(); });

		// �j���\��̔j�󎞊Ԃ�0�ȏ�Ȃ�^�C�}�[�����炷
		// 0�ȉ��Ȃ�j����Ԃɂ���
		for (auto i = iter; i < gameObjects.end(); ++i)
		{
			if (i->get()->destroyTime > 0)
			{
				i->get()->destroyTime -= Time::deltaTime();
				if (i->get()->destroyTime <= 0)
				{
					i->get()->hideFlag = Object::HideFlag::Destory;
					isDestoryObject = true;
				}
			}
		}

		// �j����Ԃ̃I�u�W�F�N�g���Ȃ���Ή������Ȃ�
		if (!isDestoryObject)
		{
			return;
		}

		// �j����Ԃ̗L���ŃI�u�W�F�N�g�𕪂���
		auto destroyIter = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) { return p->GetHideFlag() == Object::HideFlag::Destory; });
		
		// �j����Ԃ̃Q�[���I�u�W�F�N�g��ʂ̔z��Ɉړ�
		GameObjectList destroyList(
			std::move_iterator(iter),
			std::move_iterator(gameObjects.end()));

		// �j��I�u�W�F�N�g���Ȃ��ɂ���
		isDestoryObject = false;
	}

	/**
	* �Q�[���I�u�W�F�N�g���쐬
	* 
	* @param name �I�u�W�F�N�g�̖��O
	* 
	* @return �쐬�����Q�[���I�u�W�F�N�g
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name)
	{
		auto obj = CreateObject<GameObject>(name);

		// Transform��ǉ�
		//obj->AddComponent<Transform>();

		// �Q�[���I�u�W�F�N�g�z��ɓo�^
		gameObjects.push_back(obj);

		// �쐬�����Q�[���I�u�W�F�N�g
		return obj;
	}

	/**
	* �Q�[���I�u�W�F�N�g���쐬
	* 
	* @param name		�I�u�W�F�N�g�̖��O
	* @param transform	�I�u�W�F�N�g��Transfrom
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name, const Transform& transform)
	{
		// �Q�[���I�u�W�F�N�g���쐬
		auto obj = CreateGameObject(name);

		// Tranform��ݒ�

		// �ʒu
		//obj->transform->position = transform.position;

		//// ��]
		//obj->transform->rotation = transform.rotation;

		//// �g��k��
		//obj->transform->scale = transform.scale;

		// �쐬�����Q�[���I�u�W�F�N�g
		return obj;
	}

	/**
	* �Q�[���I�u�W�F�N�g���쐬
	* 
	* @param name �I�u�W�F�N�g�̖��O
	* @param 
	*/
	GameObjectPtr ObjectManager::CreateGameObject(const std::string& name, const Vector3& position, const Quaternion& rotation)
	{
		// �Q�[���I�u�W�F�N�g���쐬
		auto obj = CreateGameObject(name);

		// �ʒu
		//obj->transform->position = position;

		//// ��]
		//obj->transform->rotation = rotation;

		// �쐬�����Q�[���I�u�W�F�N�g
		return obj;
	}
}