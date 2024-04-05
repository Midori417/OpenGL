/**
* @file ObjectManager.cpp
*/
#include "ObjectManager.h"
#include "Time.h"
#include <algorithm>


namespace FGEngine::ObjectSystem
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
				i->get()->destroyTime -= Time::DeltaTime();
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
		auto iter2 = std::stable_partition(
			gameObjects.begin(), gameObjects.end(),
			[](const GameObjectPtr p) { return p->GetHideFlag() == Object::HideFlag::Destory; });
		
		// �j����Ԃ̃Q�[���I�u�W�F�N�g��ʂ̔z��Ɉړ�
		GameObjectList destroyList(
			std::move_iterator(iter2),
			std::move_iterator(gameObjects.end()));

		// �z�񂩂�ړ��ς݂̃Q�[���I�u�W�F�N�g���폜
		gameObjects.erase(iter2, gameObjects.end());

		for (auto& e : destroyList)
		{
			// ���g�̂��Q�[���I�u�W�F�N�g�j��
			e->gameObject = nullptr;

			// �j����Ԃ̃Q�[���I�u�W�F�N�g��OnDestory�����s
			for (auto x : e->monoBehaviours)
			{
				x->OnDestory();
			}
		}

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
		obj->AddComponent<Transform>();
		obj->AddComponent<Renderer>();

		obj->gameObject = obj;

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
		obj->GetTransform()->position = transform.position;

		// ��]
		obj->GetTransform()->rotation = transform.rotation;

		// �g��k��
		obj->GetTransform()->scale = transform.scale;

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
		obj->GetTransform()->position = position;

		// ��]
		obj->GetTransform()->rotation = rotation;

		// �쐬�����Q�[���I�u�W�F�N�g
		return obj;
	}
}