/**
* @file SceneManager.cpp
*/
#include "SceneManager.h"

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

