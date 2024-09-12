/**
* @file EngineCore.cpp
*/
#define _CRT_SECURE_NO_WARNINGS
#include "FGEngine/MainSystem/EngineCore.h"
#include "FGEngine/MainSystem/RenderingEngine.h"
#include "FGEngine/MainSystem/PhysicsEngine.h"
#include "FGEngine/MainSystem/SoundManager.h"
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Scene/SceneManager.h"
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Audio/EasyAudio.h"
#include "../../../Application/Src/Application.h"
#include "FGEngine/Other/Time.h"
#include "FGEngine/Package/ImGUI.h"
#include "FGEngine/Debug.h"
#include "FGEngine/Package/Glad.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <filesystem>

namespace FGEngine
{
	/**
	* OpenGLからのメッセージを処理するコールバック関数
	*
	* @param source		メッセージの発信者
	* @param type		メッセージの種類
	* @param id			メッセージを一位に選別する値
	* @param severiry	メッセージの重要度(高、中、小、最低)
	* @param length		メッセージの文字数、負数ならメッセージは0終端されている
	* @param message	メッセージ本体
	* @param userParam	コールバック設定時に指定したポインタ
	*/
	void APIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
	{
		std::string s;
		if (length < 0)
		{
			s = message;
		}
		else
		{
			s.assign(message, message + length);
		}
		s += '\n';
		LOG(s.c_str());
	}

	/**
	* ゲームエンジンを実行する
	*
	* @retval 0		正常に終了
	* @retval 0以外 エラーが発生した
	*/
	int EngineCore::Run()
	{
		// エンジンコアの初期化
		const int result = Initialize();
		if (result)
		{
			// エラー発生
			return result;
		}


		// ループ
		while (!windowManager->IsClose())
		{
			// ImGuiのフレームの更新
			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			// エンジンコアの更新
			Update();

			// imGuiを描画
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		// エンジンコアの終了
		Fainalize();

		return 0;
	}

	/**
	* ゲームエンジンを初期化する
	*
	* @retval 0		正常に終了
	* @ratval 0以外	エラーが発生
	*/
	int EngineCore::Initialize()
	{
		// GLFWの初期化
		if (glfwInit() != GLFW_TRUE)
		{
			return 1; // 初期化失敗
		}

		// ウィンドウマネージャーを作成と取得
		windowManager = WindowManager::GetInstance();

		// ウィンドウマネージャーの初期化
		windowManager->Initialize();

		// OpenGLコンテキストの作成
		glfwMakeContextCurrent(&windowManager->GetWindow());

		// OpenGL関数のアドレスを取得
		// OpenGLVersion 4.5
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			glfwTerminate();
			return 1;	// アドレスの取得失敗
		}

		// メッセージコールバック設定
		glDebugMessageCallback(DebugCallback, nullptr);

		// ====================
		// 各機能を生成と取得
		// ====================
		
		// レンダリングエンeジン
		renderingEngine = RenderingEngine::GetInstance();

		// 物理エンジン
		physicsEngine = PhysicsEngine::GetInstance();

		// サウンドマネージャー
		soundManager = SoundManager::GetInstance();

		// リソースマネージャー
		assetManager = AssetManager::GetInstance();

		// シーンマネージャー
		sceneManager = SceneManager::GetInstance();

		// インプットマネージャー
		inputManager = InputManager::GetInstance();

		// アプリケーション
		application = Application::GetInstance();

		// ImGuiコンテキストの作成
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// ====================
		// 各機能を初期化
		// ====================

		// ImGuiの初期化
		ImGui_ImplGlfw_InitForOpenGL(&windowManager->GetWindow(), true);	// GLFW
		ImGui_ImplOpenGL3_Init("#version 450");		// GLSLのバージョンを指定

		// アセットマネージャーを初期化
		assetManager->Initialize();

		// レンダリングエンジンーを初期化
		renderingEngine->Initialize();

		// アプリケーションを初期化
		application->Initialize();

		// シーンマネージャーを初期化
		sceneManager->Initialize();

		// インプットマネージャを初期化
		inputManager->Initialize(&windowManager->GetWindow());

		// サウンドマネージャーを初期化
		soundManager->Inititalize();

		return 0;
	}

	/**
	* ゲームエンジンの状態を更新する
	*/
	void EngineCore::Update()
	{
		// ウィンドウの描画開始
		windowManager->Begin();

		// 時間ライブラリを更新
		Time::Update();

		// 乱数の初期化
		Random::Initialize((unsigned int)time(NULL));

		// インプットマネージャを更新
		inputManager->Update();

		// シーンマネージャーを更新
		sceneManager->Update();

		// レンダリングエンジンを更新
		renderingEngine->Update();

		// サウンドマネージャーを更新
		soundManager->Update();

		// アプリケーションを更新する
		application->Update();

		// エディタ画面を描画
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// ウィンドウの描画終了
		windowManager->End();
	}

	/**
	* エンジンの終了
	*/
	void EngineCore::Fainalize()
	{
		// アプリケーションの終了
		application->Fainalize();

		// 音声ライブラリを終了
		soundManager->Fainalize();

		// アセットマネージャーの開放
		assetManager->Fainalize();

		// ImGuiの終了
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();

		// imGuiのコンテキストを削除
		ImGui::DestroyContext();

		// GLFWの終了
		glfwTerminate();
	}

}