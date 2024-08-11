/**
* @file ObjectManager.h
*/
#ifndef FGENGINE_OBJECTMANAGER_H_INCLUDED
#define FGENGINE_OBJECTMANAGER_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "Object.h"
#include "GameObject.h"

namespace FGEngine::ObjectSystem
{
	/**
	* �I�u�W�F�N�g�Ǘ��N���X
	*/
	class ObjectManager : public Singleton<ObjectManager>
	{
	private:

		friend Singleton<ObjectManager>;
		friend MainSystem::EngineCore;

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

		/**
		* �Q�[���I�u�W�F�N�g�̕`�揈���̏���
		*/
		void RendererGameObject();

		/**
		* �Q�[���I�u�W�F�N�g��UI�`�揈��
		*/
		void UIRendererGameObject();

		/**
		* �Q�[���I�u�W�F�N�g�̏Փˏ����̏���
		*/
		void CollisionGameObject();

		/**
		* Transform���X�V
		*/
		void UpdateTransform();

		/**
		* MonoBehaviour���X�V
		*/
		void UpdateMonoBehaviour();

		/**
		* Rigidbody���X�V
		*/
		void UpdateRigidbody();

		/**
		* Animator���X�V
		*/
		void UpdateAnimator();

		/**
		* AudioSource���X�V
		*/
		void UpdateAudioSource();

		/**
		* �Q�[���I�u�W�F�N�g���擾
		*/
		GameObjectList& GetGameObjects()
		{
			return gameObjects;
		}


	public:

		/**
		* �Q�[���I�u�W�F�N�g���쐬
		*/
		GameObjectPtr CreateGameObject(const std::string& name);
		GameObjectPtr CreateGameObject(const std::string& name, const TransformPtr transform);
		GameObjectPtr CreateGameObject(const std::string& name, const Vector3& position, const Quaternion& rotation = Quaternion::identity);

		/**
		* ���C���J�������擾
		*/
		GameObjectPtr GetMainCamera() const
		{
			return mainCamera;
		}

		/**
		* ���C���J������ݒ�
		*/
		void SetMainCamera(GameObjectPtr camera)
		{
			mainCamera = camera;
		}

		/**
		* �S�ẴQ�[���I�u�W�F�N�g���폜
		*/
		void AllClearGameObject()
		{
			gameObjects.clear();
		}

	private:

		// �Q�[���I�u�W�F�N�g�z��
		std::vector<GameObjectPtr> gameObjects;

		// ���C���J�����I�u�W�F�N�g
		GameObjectPtr mainCamera;

		// �j��I�u�W�F�N�g�����݂��邩�ǂ���
		bool isDestoryObject = false;
	};
}

#endif // !OBJECTMANAGER_H_INCLUDED
