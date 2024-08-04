/**
* @file GameEngine.cpp
*/
#include "FGEngine/GameEngine/GameEngine.h"
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Debug/Debug.h"

#include "FGEngine/Package/Glad.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{

	/**
	* ゲームエンジン稼働
	*
	* @retval 0		正常に稼働
	* @retval 0以外	エラー発生
	*/
	int GameEngine::Run()
	{
		if (Initialize() != 0)
		{
			LOG_ERROR("ゲームエンジンの初期化失敗");
			return 1;
		}

		while (isPowerOff)
		{
			if (Update() != 0)
			{
				LOG_ERROR("ゲームエンジンの更新中にエラー発生");
				isPowerOff = true;
			}
			Render();
		}

		Finalze();

		return 0;
	}

	/**
	* ゲームエンジンを初期化
	*
	* @retval 0		正常に初期化
	* @retval 0以外	エラー発生
	*/
	int GameEngine::Initialize()
	{	
		// GLFWの初期化
		if (glfwInit() != GLFW_TRUE)
		{
			LOG_ERROR("GLFWの初期化に失敗");
			return 1;
		}

		// === エンジンとマネージャーを作成と取得 === //
		inputManager = InputManager::GetInstance();
		windowManger = WindowManager::GetInstance();

		// OpenGLの関数アドレスを取得するにはウィンドウが必要なのでで先にウィンドウマネージャーを初期化する
		if (windowManger->Initialze() != 0)
		{
			LOG_ERROR("ウィンドウマネージャーの初期化に失敗");
			return 1;
		}

		// OpenGL関数のアドレスを取得
		// OpenGLVersion 4.5
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			LOG_ERROR("OpenGLの関数アドレスの取得に失敗");
			glfwTerminate();
			return 1;	// アドレスの取得失敗
		}

		Debug::OpenGLSetDebugCall();

		// エンジンとマネージャーを初期化 === //
		if (inputManager->Initialize() != 0)
		{
			LOG_ERROR("入力マネージャーの初期化に失敗");
			glfwTerminate();
			return 1;
		}

		return 0;
	}
	int GameEngine::Update()
	{
		return 0;
	}
	void GameEngine::Render()
	{
	}
	void GameEngine::Finalze()
	{
	}

	/**
	* エンジンを止める
	*/
	void GameEngine::PowerOff()
	{
		isPowerOff = true;
	}
}