/**
* @file SceneManager.cpp
*/
#include "FGEngine/Scene/SceneManager.h"
#include "FGEngine/ObjectManager.h"

namespace FGEngine::SceneSystem
{
	ScenePtr SceneManager::nextScene;
	std::unordered_map<std::string, ScenePtr> SceneManager::scenes;

	/**
	* �V�[���}�l�[�W���[�̏�����
	*
	* @retval 0		����������
	* @retval 0�ȊO	���������s
	*/
	int SceneManager::Initialize()
	{
		// �V�[��������Ȃ����߃G���[����
		if (scenes.empty())
		{
			return 1;
		}

		// �ŏ��̃V�[�����ݒ肳��Ă��Ȃ���΃V�[���z��̍ŏ�������
		if (!nextScene)
		{
			nextScene = scenes.begin()->second;
		}

		return 0;
	}

	/**
	* �V�[���}�l�[�W���[�̍X�V
	*/
	void SceneManager::Update()
	{
		// �V�[���̐؂�ւ�
		if (nextScene)
		{
			if (scene)
			{
				scene->Finalize();
				scene.reset();
				// �I�u�W�F�N�g��S�폜
				ObjectSystem::ObjectManager::GetInstance()->AllClearGameObject();
			}
			nextScene->Initialize();
			scene = std::move(nextScene);
		}

		// �V�[���̍X�V
		if (scene)
		{
			scene->Update();
		}
	}

	/**
	* �V�[�������[�h����
	*
	* @param name ���[�h����V�[���̖��O
	*/
	void SceneManager::LoadScene(const std::string& name)
	{
		auto scenePtr = scenes.find(name);
		if (scenePtr != scenes.end())
		{
			nextScene = scenePtr->second;
		}
	}
}

