/**
* @file SceneManager.h
*/
#ifndef SCENEMANAGER_H_INCLUDED
#define SCENEMANAGER_H_INCLUDED
#include <memory>

// 先行宣言
class Engine;
struct Material;
using MaterialPtr = std::shared_ptr<Material>;

namespace SceneManagment
{
	// 先行宣言2
	class Scene;
	using ScenePtr = std::shared_ptr<Scene>;

	/**
	* シーンを管理するクラス
	*/
	class SceneManager
	{
		friend Engine;
	private:

		// コンストラクタ・デストラクタ
		SceneManager() = default;
		~SceneManager() = default;


		/**
		* シーンマネージャーを更新
		*/
		static void Update(Engine& engine);

		/**
		* 現在のシーンを取得
		*/
		static ScenePtr CurrentScene()
		{
			return scene;
		}

		/**
		* 現在のシーンにスカイスフィアを取得
		*
		* @return シーンに設定されているスカイスフィアマテリアル
		* @return nullptr 設定されいない
		*/
		static MaterialPtr CurrentSceneSkyMaterial();

	public:

		// 次のシーンを設定する
		template<typename T>
		static void SetNextScene()
		{
			nextScene = std::make_shared<T>();
		}

	private:

		static ScenePtr scene;		// 実行中のシーン
		static ScenePtr nextScene;	// 次のシーン

	};
}

#endif // !SCENEMANAGER_H_INCLUDED