/**
* @file GameEngine.h
*/
#ifndef FGENGINE_GAMEENGINE_H_INCLUDED
#define FGENGINE_GAMEENGINE_H_INCLUDED
#include "FGEngine/Singleton.h"

namespace FGEngine
{
	// 先行宣言
	class RenderEngine;
	class PhysicsEngine;
	class AudioEngine;
	class InputManager;
	class AssetManager;
	class SceneManager;
	class WindowManager;

	/**
	* ゲームエンジン
	*/
	class GameEngine : public Singleton<GameEngine>
	{
		friend Singleton<GameEngine>;
	private:

		/**
		* デフォルトコンストラクタ
		*/
		GameEngine() = default;


		// コピーと代入を禁止
		GameEngine(const GameEngine&) = delete;
		GameEngine operator=(const GameEngine&) = delete;

	public:

		/**
		* ゲームエンジン稼働
		* 
		* @retval 0		正常に稼働
		* @retval 0以外	エラー発生
		*/
		int Run();

	private:

		/**
		* ゲームエンジンを初期化
		* 
		* @retval 0		正常に初期化
		* @retval 0以外	エラー発生
		*/
		int Initialize();

		/**
		* ゲームエンジンの状態を更新
		* 
		* @retval 0		正常に更新
		* @retval 0以外	エラー発生
		*/
		int Update();

		/**
		* ゲームエンジンの状態を描画
		*/
		void Render();

		/**
		* ゲームを終了
		*/
		void Finalze();

	public:

		/**
		* エンジンを止める
		*/
		void PowerOff();

	private:

		// 描画エンジン
		std::shared_ptr<RenderEngine> renderEngine;

		// 物理エンジン
		std::shared_ptr<PhysicsEngine> physicsEngine;

		// サウンドエンジン
		std::shared_ptr<AudioEngine> audioEngine;

		// 入力マネージャー
		std::shared_ptr<InputManager> inputManager;

		// アセットマネージャー
		std::shared_ptr<AssetManager> assetManager;

		// シーンマネージャー
		std::shared_ptr<SceneManager> sceneManager;

		// ウィンドウマネージャー
		std::shared_ptr<WindowManager> windowManger;

		// trueならエンジンを止める
		bool isPowerOff = false;
	};
}

#endif // !FGENGINE_GAMEENGINE_H_INCLUDED
