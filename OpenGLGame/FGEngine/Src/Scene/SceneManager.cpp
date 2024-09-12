/**
* @file SceneManager.cpp
*/
#include "FGEngine/Scene/SceneManager.h"

namespace FGEngine
{
	// 静的変数の初期化
	ScenePtr SceneManager::nextScene;
	std::unordered_map<std::string, ScenePtr> SceneManager::scenes;

	/**
	* シーンマネージャーの初期化
	*
	* @retval 0		初期化成功
	* @retval 0以外	初期化失敗
	*/
	int SceneManager::Initialize()
	{
		// シーンが一つもないためエラー発生
		if (scenes.empty())
		{
			return 1;
		}


		// 初期化成功
		return 0;
	}

	/**
	* シーンマネージャーの更新
	*/
	void SceneManager::Update()
	{
		// シーンの切り替え
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
	* シーンをロードする
	*
	* @param name ロードするシーンの名前
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

