/**
* @file SceneManager.cpp
*/
#include "SceneManager.h"

namespace FGEngine::SceneSystem
{
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

		// 最初のシーンが設定されていなければシーン配列の最初を入れる
		if (!nextScene)
		{
			nextScene = scenes.begin()->second;
		}

		return 0;
	}

	/**
	* シーンマネージャーの更新
	*/
	void SceneManager::Update(Engine& engine)
	{
		// シーンの切り替え
		if (nextScene)
		{
			if (scene)
			{
				scene->Finalize(engine);
			}
			nextScene->Initialize(engine);
			scene = std::move(nextScene);
		}

		// シーンの更新
		if (scene)
		{
			scene->Update(engine);
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

