/**
* @file SceneManager.h
*/
#ifndef FGENEING_SCENEMANAGER_H_INCLUDED
#define FGENEING_SCENEMANAGER_H_INCLUDED
#include "Singleton.h"
#include "Scene.h"
#include <unordered_map>

namespace FGEngine
{
	struct Material;
	using MaterialPtr = std::shared_ptr<Material>;

	namespace SceneSystem
	{
		/**
		* シーンを管理するクラス
		*/
		class SceneManager : public Singleton<SceneManager>
		{
		private:
			
			friend Singleton<SceneManager>;
			friend MainSystem::EngineCore;

			// コンストラクタ
			SceneManager() = default;

			/**
			* シーンマネージャーの初期化
			*
			* @retval 0		初期化成功
			* @retval 0以外	初期化失敗
			*/
			int Initialize();

			/**
			* シーンマネージャーの更新
			*/
			void Update();

		public:

			/**
			* シーンを登録する
			*
			* @parma name 登録するシーンの名前
			*/
			template<typename T>
			static void AddScene(const std::string& name)
			{
				auto scenePtr = std::make_shared<T>();
				scenes.emplace(name, scenePtr);
			}

			/**
			* シーンをロードする
			*
			* @param name ロードするシーンの名前
			*/
			static void LoadScene(const std::string& name);

			/**
			* 現在のシーンを取得
			*/
			ScenePtr CurrentScene() const
			{
				return scene;
			}

			// 次のシーンを設定する
			template<typename T>
			static void SetNextScene()
			{
				nextScene = std::make_shared<T>();
			}

		private:

			// 実行中のシーン
			ScenePtr scene;

			// 次のシーン
			static ScenePtr nextScene;	

			// シーン管理配列
			static std::unordered_map<std::string, ScenePtr> scenes;

		};
	}
}

#endif // !SCENEMANAGER_H_INCLUDED