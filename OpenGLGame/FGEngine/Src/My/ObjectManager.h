/**
* @file ObjectManager.h
*/
#ifndef OBJECTMANAGER_H_INCLUDED
#define OBJECTMANAGER_H_INCLUDED
#include "Singleton.h"
#include "Object.h"
#include "GameObject.h"

namespace FGEngine
{
	/**
	* �I�u�W�F�N�g�Ǘ��N���X
	*/
	class ObjectManager : public Singleton<ObjectManager>
	{
	private:

		friend Singleton<ObjectManager>;

		// �R���X�g���N�^
		ObjectManager() = default;

		/**
		* �I�u�W�F�N�g�}�l�[�W���[��������
		*
		* @retval 0		����ɏ�����
		* @retval 0�ȊO ���������s
		*/
		int Initialize();

		/**
		* �I�u�W�F�N�g�}�l�[�W���[���X�V
		*/
		void Update();

		/**
		* �Q�[���I�u�W�F�N�g�̍폜����
		*/
		void DestoryGameObject();

	public:

		/**
		* �I�u�W�F�N�g���쐬
		*/
		template<typename T>
		std::shared_ptr<T> CreateObject(const std::string& name)
		{
			auto obj = std::make_shared<T>();
			obj->SetName(name);
			return obj;
		}

		/**
		* �Q�[���I�u�W�F�N�g���쐬
		*/
		GameObjectPtr CreateGameObject(const std::string& name);
		GameObjectPtr CreateGameObject(const std::string& name, const Transform& transform);
		GameObjectPtr CreateGameObject(const std::string& name, const Vector3& position, const Quaternion& rotation);

		/**
		* �Q�[���I�u�W�F�N�g���擾
		*/
		GameObjectList& GetGameObjects()
		{
			return gameObjects;
		}

		/**
		* �S�ẴQ�[���I�u�W�F�N�g���폜
		*/
		void AllClearGameObject()
		{
			gameObjects.clear();
		}

	private:

		std::vector<GameObjectPtr> gameObjects;	// �Q�[���I�u�W�F�N�g�z��
	};
}

#endif // !OBJECTMANAGER_H_INCLUDED