/**
* @file SceneManager.h
*/
#ifndef FGENGINE_SCENEMANAGER_H_INCLUDED
#define FGENGINE_SCENEMANAGER_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include "Scene.h"
#include <unordered_map>

namespace FGEngine
{
	/**
	* シーンを管理するクラス
	*/
	class SceneManager : public Singleton<SceneManager>
	{
		friend Singleton<SceneManager>;
		friend class EngineCore;
	private:

		/**
		* デフォルトコンストラクタ
		*/
		SceneManager() = default;

	private:

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
			// 名前を検索する
			auto tmp = scenes.find(name);
			if (tmp != scenes.end())
			{
				// 既に存在している
				return;
			}

			// シーンを作成
			ScenePtr p = std::make_shared<T>();
			p->name = name;

			// 最初のシーンが設定されていなければ設定する
			if (!nextScene)
			{
				nextScene = p;
			}
			
			// シーン配列に追加
			scenes.emplace(name, p);
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

	private:

		// 実行中のシーン
		ScenePtr scene;

		// 次のシーン
		static ScenePtr nextScene;

		// シーン管理配列
		static std::unordered_map<std::string, ScenePtr> scenes;

	};
}

#endif // !SCENEMANAGER_H_INCLUDED