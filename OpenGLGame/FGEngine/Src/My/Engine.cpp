/**
* @file Engine.cpp
*/
#define _CRT_SECURE_NO_WARNINGS

#include "Engine.h"
#include "../../../Application/Src/Application.h"


#include "Package/ImGUI.h"

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
		const int result = Initialize();
		if (result) {
			return result;
		}


		// ループ
		while (!glfwWindowShouldClose(window))
		{
			// -------------------------
			// ImGuiフレームの更新
			// -------------------------

			ImGui_ImplGlfw_NewFrame();
			ImGui_ImplOpenGL3_NewFrame();
			ImGui::NewFrame();

			Update();

		}

		// -----------------
		// ImGuiの終了
		// -----------------

		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();

		// ------------------------
		// コンテキストの削除
		// ------------------------

		ImGui::DestroyContext();

		glfwTerminate();
		return 0;
	}



	/**
	* フレームバッファの大きさを取得する
	*
	* @return フレームバッファの縦の横のサイズ
	*/
	Vector2 EngineCore::GetFramebufferSize() const
	{
		int w = 0;
		int h = 0;
		glfwGetFramebufferSize(window, &w, &h);
		return Vector2{ static_cast<float>(w), static_cast<float>(h) };
	}

	/**
	* フレームバッファのアスペクト比を取得する
	*
	* @return フレームバッファのアスペクト比
	*/
	float EngineCore::GetAspectRatio() const
	{
		const Vector2 size = GetFramebufferSize();
		return size.x / size.y;
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

		// 描画ウィンドウの作成
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_HOVERED, GLFW_FALSE);
		window = glfwCreateWindow(1280, 720, title.c_str(), nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			return 1; // ウィンドウの作成失敗
		}


		// OpenGLコンテキストの作成
		glfwMakeContextCurrent(window);

		// OpenGL関数のアドレスを取得
		// OpenGLVersion 4.5
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
			glfwTerminate();
			return 1;	// アドレスの取得失敗
		}

		// メッセージコールバック設定
		glDebugMessageCallback(DebugCallback, nullptr);

		// ====================
		// 各機能を生成と取得
		// ====================
		
		// アプリケーション
		application = Application::GetInstance();

		// シーンマネージャー
		sceneManager = SceneSystem::SceneManager::GetInstance();


		// ---------------------------
		// ImGuiコンテキスト作成
		// ---------------------------

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();

		// ------------------------
		// ImGuiの初期化
		// ------------------------

		// GLFW
		ImGui_ImplGlfw_InitForOpenGL(window, true);

		// GLSLのバージョンを指定
		ImGui_ImplOpenGL3_Init("#version 450");


		// アプリケーションを初期化
		application->Initialize();

		// シーンマネージャーを初期化
		sceneManager->Initialize();

		return 0;
	}

	/**
	* ゲームエンジンの状態を更新する
	*/
	void EngineCore::Update()
	{
		sceneManager->Update();

		// 時間ライブラリを更新
		Time::Update();

		// 入力ライブラリを更新
		Input::Update(window);

		// アプリケーションを更新する
		application->Update();
	}

	/**
	* エンジンの終了
	*/
	void EngineCore::Fainalize()
	{
		// アプリケーションの終了
		application->Fainalize();
	}

}