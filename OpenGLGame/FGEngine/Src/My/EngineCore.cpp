/**
* @file EngineCore.cpp
*/
#define _CRT_SECURE_NO_WARNINGS
#include "EngineCore.h"
#include "RenderingEngine.h"
#include "PhysicsEngine.h"
#include "WindowManager.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResouceManager.h"
#include "EasyAudio/EasyAudio.h"
#include "../../../Application/Src/Application.h"
#include "Time.h"
#include "Package/ImGUI.h"
#include <fstream>
#include <filesystem>

namespace FGEngine::MainSystem
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
		windowManager = WindowSystem::WindowManager::GetInstance();

		// ウィンドウを作成
		windowManager->CreateWindow("Window");

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
		
		// レンダリングエンジン
		renderingEngine = RenderingSystem::RenderingEngine::GetInstance();

		// 物理エンジン
		physicsEngine = PhysicsSystem::PhysicsEngine::GetInstance();

		// リソースマネージャー
		resouceManager = ResouceSystem::ResouceManager::GetInstance();

		// シーンマネージャー
		sceneManager = SceneSystem::SceneManager::GetInstance();

		// インプットマネージャー
		inputManager = InputSystem::InputManager::GetInstance();

		// オブジェクトマネージャー
		objectManager = ObjectSystem::ObjectManager::GetInstance();

		// アプリケーション
		application = Application::GetInstance();

		// ImGuiコンテキストの作成
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// ====================
		// 各機能を初期化
		// ====================

		// ImGuiの初期化
		ImGui_ImplGlfw_InitForOpenGL(&windowManager->GetWindow(0), true);	// GLFW
		ImGui_ImplOpenGL3_Init("#version 450");		// GLSLのバージョンを指定

		// リソースマネージャーを初期化
		resouceManager->Initialize();

		// レンダリングエンジンーを初期化
		renderingEngine->Initialize();

		// オブジェクトマネージャーを初期化
		objectManager->Initialize();

		// アプリケーションを初期化
		application->Initialize();

		// シーンマネージャーを初期化
		sceneManager->Initialize();

		// インプットマネージャを初期化
		inputManager->Initialize();

		// 音声ライブラリを初期化
		if (!EasyAudio::Initialize()) 
		{
			return 1;
		}

		return 0;
	}

	/**
	* ゲームエンジンの状態を更新する
	*/
	void EngineCore::Update()
	{
		// ウィンドウの描画開始
		windowManager->Begin();

		// 乱数の初期化
		Random::Initialize((unsigned int)time(NULL));

		// 時間ライブラリを更新
		Time::Update();

		// インプットマネージャを更新
		inputManager->Update(&windowManager->GetWindow());

		// シーンマネージャーを更新
		sceneManager->Update();

		// オブジェクトマネージャを更新
		objectManager->Update();

		// レンダリングエンジンを更新
		renderingEngine->Update();

		// 音声ライブラリを更新
		EasyAudio::Update();

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
		EasyAudio::Finalize();

		// ImGuiの終了
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();

		// imGuiのコンテキストを削除
		ImGui::DestroyContext();

		// GLFWの終了
		glfwTerminate();
	}

}