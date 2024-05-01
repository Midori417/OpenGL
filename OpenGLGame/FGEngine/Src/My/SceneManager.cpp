/**
* @file SceneManager.cpp
*/
#include "SceneManager.h"
#include "Scene.h"

 namespace SceneManagment
{
	 // �ÓI�ϐ��̏�����
	 ScenePtr SceneManager::scene = nullptr;
	 ScenePtr SceneManager::nextScene = nullptr;

	 /**
	 * �V�[���}�l�[�W���[���X�V
	 */
	 void SceneManager::Update(Engine& engine)
	 {

		 // �V�[���̐؂�ւ�
		 if (nextScene) 
		 {
			 if (scene)
			 {
				 scene->Finalize(engine);
			 }
			 nextScene->Initialize(engine);
			 scene = std::move(nextScene);
		 }

		 // �V�[���̍X�V
		 if (scene) 
		 {
			 scene->Update(engine);
		 }
	 }

	 /**
	 * ���݂̃V�[���ɃX�J�C�X�t�B�A���擾
	 *
	 * @return �V�[���ɐݒ肳��Ă���X�J�C�X�t�B�A�}�e���A��
	 * @return nullptr �ݒ肳�ꂢ�Ȃ�
	 */
	 MaterialPtr SceneManager::CurrentSceneSkyMaterial()
	 {
		 return scene->skyMaterial;
	 }
 }

