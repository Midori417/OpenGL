/**
* @file SceneManager.cpp
*/
#include "FGEngine/Scene/SceneManager.h"

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
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


		// ����������
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
				scene->AllClearGameObject();
				scene.reset();
			}
			nextScene->Awake();
			nextScene->Initialize();
			scene = std::move(nextScene);
		}

		if (scene)
		{
			scene->Update();
			scene->Render();
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

