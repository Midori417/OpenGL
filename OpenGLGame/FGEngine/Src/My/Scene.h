/**
* @file Scene.h
*/
#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include <memory>
#include <string>

// ��s�錾
class Engine;
struct Material;
using MaterialPtr = std::shared_ptr<Material>;

namespace SceneManagment
{
	/**
	* �V�[���̊��N���X
	*/
	class Scene
	{
		friend class SceneManager;
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Scene() = default;
		virtual ~Scene() = default;

		/**
		* �X�J�C�X�t�B�A�}�e���A��ݒ�
		* 
		* @param skyMaterial �ݒ肷��}�e���A��
		*/
		void SetSkeyMaterial(MaterialPtr skyMaterial)
		{
			this->skyMaterial = skyMaterial;
		}

	private:

		/**
		* �V�[���̏�����
		* 
		* @param engine �G���W��
		* 
		* @retval true	����������
		* @retval false	���������s
		*/
		virtual bool Initialize(Engine& engine) 
		{
			return true;
		}

		/**
		* �V�[���̍X�V
		* 
		* @param engine �G���W��
		*/
		virtual void Update(Engine& engine) {}

		/**
		* �V�[���̏I��
		* 
		* @param engine �G���W��
		*/
		virtual void Finalize(Engine& engine) {}


	public:

		std::string name = "sampleScene";
		MaterialPtr skyMaterial;	// �X�J�C�X�t�B�A�p�̃}�e���A��

	};
	using ScenePtr = std::shared_ptr<Scene>;
}
#endif // !SCENEH_INCLUDED
