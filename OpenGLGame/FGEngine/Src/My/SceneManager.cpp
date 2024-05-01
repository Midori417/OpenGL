/**
* @file SceneManager.cpp
*/
#include "SceneManager.h"
#include "Scene.h"

 namespace SceneManagment
{
	 // 静的変数の初期化
	 ScenePtr SceneManager::scene = nullptr;
	 ScenePtr SceneManager::nextScene = nullptr;

	 /**
	 * シーンマネージャーを更新
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
	 * 現在のシーンにスカイスフィアを取得
	 *
	 * @return シーンに設定されているスカイスフィアマテリアル
	 * @return nullptr 設定されいない
	 */
	 MaterialPtr SceneManager::CurrentSceneSkyMaterial()
	 {
		 return scene->skyMaterial;
	 }
 }

