/**
* @file SceneManager.h
*/
#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include <memory>

// ��s�錾
class Engine;
struct Material;
using MaterialPtr = std::shared_ptr<Material>;

namespace SceneManagment
{
	// ��s�錾2
	class Scene;
	using ScenePtr = std::shared_ptr<Scene>;

	/**
	* �V�[�����Ǘ�����N���X
	*/
	class SceneManager
	{
		friend Engine;
	private:

		// �R���X�g���N�^�E�f�X�g���N�^
		SceneManager() = default;
		~SceneManager() = default;


		/**
		* �V�[���}�l�[�W���[���X�V
		*/
		static void Update(Engine& engine);

		/**
		* ���݂̃V�[�����擾
		*/
		static ScenePtr CurrentScene()
		{
			return scene;
		}

		/**
		* ���݂̃V�[���ɃX�J�C�X�t�B�A���擾
		*
		* @return �V�[���ɐݒ肳��Ă���X�J�C�X�t�B�A�}�e���A��
		* @return nullptr �ݒ肳�ꂢ�Ȃ�
		*/
		static MaterialPtr CurrentSceneSkyMaterial();

	public:

		// ���̃V�[����ݒ肷��
		template<typename T>
		static void SetNextScene()
		{
			nextScene = std::make_shared<T>();
		}

	private:

		static ScenePtr scene;		// ���s���̃V�[��
		static ScenePtr nextScene;	// ���̃V�[��

	};
}

#endif // !SCENEMANAGER_H_INCLUDED