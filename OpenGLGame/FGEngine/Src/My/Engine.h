/**
* @file Engine.h
*/
#ifndef ENGINE_H_INCLUDED
#define ENGINE_H_INCLUDED
#include "Singleton.h"
#include "VecMath.h"
#include "Package/Glad.h"

#include <GLFW/glfw3.h>
#include <string>
#include <utility>
#include <functional>
#include <unordered_map>

// 先行宣言
class Application;
using ApplicationPtr = std::shared_ptr<Application>;

namespace FGEngine
{
	namespace SceneSystem
	{
		class SceneManager;
		using SceneManagerPtr = std::shared_ptr<SceneManager>;
	}

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

		// フレームバッファの大きさを取得する
		Vector2 GetFramebufferSize() const;

		// フレームバッファのアスペクト比を取得する
		float GetAspectRatio() const;

	private:

		// ゲームエンジンを初期化
		int Initialize();

		// ゲームエンジンを更新
		void Update();

		// エンジンの終了
		void Fainalize();

	private:

		// ウィンドウ
		GLFWwindow* window = nullptr;	// ウィンドウオブジェクト
		const std::string title = "OpenGLGame";	// ウィンドウタイトル

		// アプリケーションポインター
		ApplicationPtr application;

		// シーンマネージャーポインター
		SceneSystem::SceneManagerPtr sceneManager;
	};
}
#endif // !ENGINE_H_INCLUDED
