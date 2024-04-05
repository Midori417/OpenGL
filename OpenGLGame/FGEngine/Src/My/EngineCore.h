/**
* @file EngineCore.h
*/
#ifndef FGENGINE_ENGINECORE_H_INCLUDED
#define FGENGINE_ENGINECORE_H_INCLUDED
#include "Singleton.h"
#include "SystemFrd.h"
#include "Package/Glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <utility>
#include <functional>
#include <unordered_map>

// 先行宣言
class Application;
using ApplicationPtr = std::shared_ptr<Application>;

namespace FGEngine::MainSystem
{
	/**
	* ゲームエンジン
	*/
	class EngineCore : public Singleton<EngineCore>
	{
	private:

		friend Singleton<EngineCore>;

		// コンストラクタ
		EngineCore() = default;

	public:

		~EngineCore() = default;

		// ゲームエンジンを実行
		int Run();

	private:

		/**
		* ゲームエンジンを初期化
		* 
		* @retval 0		正常に終了
		* @ratval 0以外	エラーが発生
		*/
		int Initialize();

		/**
		* ゲームエンジンを更新
		*/
		void Update();

		/**
		* エンジンを終了
		*/
		void Fainalize();

	private:

		// アプリケーションポインター
		ApplicationPtr application;

		// ウィンドウマネージャーポインター
		std::shared_ptr<WindowSystem::WindowManager> windowManager;

		// シーンマネージャーポインター
		std::shared_ptr<SceneSystem::SceneManager> sceneManager;

		// インプットマネージャポインター
		std::shared_ptr<InputSystem::InputManager> inputManager;
	};
}
#endif // !ENGINE_H_INCLUDED
