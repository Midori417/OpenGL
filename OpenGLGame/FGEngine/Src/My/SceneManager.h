/**
* @file SceneManager.h
*/
#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
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
			friend class EngineCore;

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


		public:

			// 次のシーンを設定する
			template<typename T>
			static void SetNextScene()
			{
				nextScene = std::make_shared<T>();
			}

		private:

			ScenePtr scene;				// 実行中のシーン
			static ScenePtr nextScene;	// 次のシーン
			static std::unordered_map<std::string, ScenePtr> scenes;	// シーン管理配列

		};
	}
}

#endif // !SCENEMANAGER_H_INCLUDED