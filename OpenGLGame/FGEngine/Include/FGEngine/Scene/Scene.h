/**
* @file Scene.h
*/
#ifndef FGENGINE_SCENE_H_INCLUDED
#define FGENGINE_SCENE_H_INCLUDED
#include "FGEngine/UsingNames/UsingScene.h"
#include "FGEngine/UsingNames/UsingAsset.h"
#include "FGEngine/UsingNames/UsingGameObject.h"
#include "FGEngine/UsingNames/UsingComponent.h"
#include "FGEngine/UsingNames/UsingMath.h"
#include <string>

namespace FGEngine
{
	namespace CreateObject
	{
		// �������ĂȂ��Q�[���I�u�W�F�N�g
		inline const std::string Empty = "Empty";

		// �J����
		inline const std::string Camera = "Camera";

		// 3D�I�u�W�F�N�g
		namespace GameObject3D
		{
			// �l�p�`
			inline const std::string Cube = "Cube";

			// ����
			inline const std::string Sphere = "Sphere";
		}
		// ���[�U�[�C���^�[�t�F�[�X
		namespace UI
		{
			// �摜
			inline const std::string Image = "Image";

			// �{�^��
			inline const std::string Button = "Button";
		}
	}

	/**
	* �V�[���̊��N���X
	*/
	class Scene
	{
		friend class SceneManager;
	public:	// �R���X�g���N�^�E�f�X�g���N�^

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Scene() = default;

		/**
		* �f�t�H���g�f�X�g���N�^
		*/
		virtual ~Scene() = default;

	private: // �I�u�W�F�N�g�̐����E�j��

		/**
		* �Q�[���I�u�W�F�N�g���쐬
		* 
		* @param name �I�u�W�F�N�g�̖��O
		* 
		* @return �쐬�����Q�[���I�u�W�F�N�g
		*/
		GameObjectPtr CreateGameObject(const std::string& name);

	public:	

		/**
		* name�ɂ������I�u�W�F�N�g�𐶐�����
		* 
		* @param name �����������I�u�W�F�N�g�̖��O
		* namespace CreateObject����I�𐄏�
		* 
		* @return ���������I�u�W�F�N�g
		*/
		GameObjectPtr Create(const std::string& name);

		/**
		* �Q�[���I�u�W�F�N�g���N���[������
		* 
		* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
		* 
		* @return �쐬�����Q�[���I�u�W�F�N�g
		*/
		GameObjectPtr CloneGameObject(const GameObjectPtr& gameObject);

		/**
		* �Q�[���I�u�W�F�N�g���N���[������
		*
		* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
		* @param transform	�N���[������g�����X�t�H�[��
		*
		* @return �쐬�����Q�[���I�u�W�F�N�g
		*/
		GameObjectPtr CloneGameObject(const GameObjectPtr& gameObject, const TransformPtr& tranform);

		/**
		* �Q�[���I�u�W�F�N�g���N���[������
		*
		* @param gameObject �N���[�����̃Q�[���I�u�W�F�N�g
		* @param position	�N���[���������̈ʒu
		* @param rotation	�N���[���������̉�]
		*
		* @return �쐬�����Q�[���I�u�W�F�N�g
		*/
		GameObjectPtr CloneGameObject(const GameObjectPtr& gameObject, const Vector3& position, const Quaternion& rotation);

		/**
		* �S�ẴQ�[���I�u�W�F�N�g���폜����
		*/
		void AllClearGameObject();

	public:

		/**
		* �J�����R���|�[�l���g���擾
		*/
		CameraPtr GetMainCameraInfo() const;

		/**
		* ���C���J������ݒ�
		* 
		* @param camera �ݒ肷��J����
		*/
		void SetMainCameraInfo(const CameraPtr& camera);

	protected:

		/**
		* �V�[���̏�����
		*
		* @param engine �G���W��
		*
		* @retval true	����������
		* @retval false	���������s
		*/
		virtual bool Initialize()
		{
			return true;
		}

	private:	// �V�[���̃C�x���g

		/**
		* �������̏���
		*/
		void Awake();

		/**
		* ���t���[�����̏���
		*/
		void Update();

		/**
		* ���t���[���`�悷��
		*/
		void Render();

		/**
		* �I�����̏���
		*/
		void Fainalize();

	private:	// �Q�[���I�u�W�F�N�g�̏���

		/**
		* �Q�[���C�x���g�̍X�V
		*/
		void UpdateGameEvent();

		/**
		* Animator���X�V
		*/
		void UpdateAnimator();

		/**
		* AudioSource���X�V
		*/
		void UpdateAudioSource();

		/**
		* �g�����X�t�H�[�����X�V
		*/
		void UpdateTransform();

		/**
		* ���W�b�h�{�f�B���X�V
		*/
		void UpdateRigidbody();

		/**
		* �Q�[���I�u�W�F�N�g�̏Փˏ����̏���
		*/
		void CollisionGameObject();

		/**
		* �Q�[���I�u�W�F�N�g�̕`�揈���̏���
		*/
		void RendererGameObject();

		/**
		* �Q�[���I�u�W�F�N�g��UI�`�揈��
		*/
		void UIRendererGameObject();

		/**
		* �Q�[���I�u�W�F�N�g�̔j������
		*/
		void DestoryGameObject();

	public:

		// �V�[���̖��O
		std::string name = "�f�t�H���g�V�[��";

		// �X�J�C�{�b�N�X�p�̃}�e���A��
		MaterialPtr skyBoxMaterial;

	private:	// �Q�[���I�u�W�F�N�g

		// ���C���J�����R���|�[�l���g
		CameraPtr mainCamera;
		
		// �Q�[���I�u�W�F�N�g�z��
		GameObjectList gameObjects;
	};
}
#endif // !SCENEH_INCLUDED
