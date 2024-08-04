/**
* @file WindowManager.cpp
*/
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Package/Glad.h"
#include "FGEngine/Debug/Debug.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	/**
	* デストラクタ
	*/
	WindowManager::~WindowManager()
	{
		if (window)
		{
			glfwDestroyWindow(window);
		}
	}

	/**
	* ウィンドウマネージャーを初期化
	*
	* @retval true	初期化成功
	* @retval flase	初期化失敗
	*/
	int WindowManager::Initialze()
	{
		// デバッグコンテキストの作成
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		// ウィンドウをフルスクリーンに設定
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		// ウィンドウの作成
		window = glfwCreateWindow(1280, 720, "Window", nullptr, nullptr);

		if (!window)
		{
			// ウィンドウの作成失敗
			LOG_ERROR("ウィンドウの作成に失敗しました");
			return 1;
		}

		// OpenGLコンテキストの作成
		glfwMakeContextCurrent(window);

		// 初期化成功
		return 0;
	}

	/**
	* ウィンドウの描画開始
	*/
	void WindowManager::Begin()
	{
		if (!window)
		{
			LOG_WARNINGS("ウィンドウが初期化されていません");
			return;
		}

		// 描画ウィンドウを指定
		glfwMakeContextCurrent(window);

		// バックバッファをクリア
		glClearColor(0, 0, 0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/**
	* ウィンドウの描画終了
	*/
	void WindowManager::End()
	{
		if (!window)
		{
			LOG_WARNINGS("ウィンドウが初期化されていません");
			return;
		}

		// フロントバッファとバックバッファを入れ替え
		glfwSwapBuffers(window);

		// OSからの要求を処理する
		glfwPollEvents();

		// 描画先ウィンドウの設定を解除
		glfwMakeContextCurrent(nullptr);
	}

	/**
	* ウィンドウタイトルを取得
	*/
	std::string WindowManager::GetTitle() const
	{
		if (!window)
		{
			LOG_WARNINGS("ウィンドウが初期化されていません");
			return "";
		}

		return glfwGetWindowTitle(window);
	}

	/**
	* ウィンドウタイトルを変更
	*
	* @param title 変更するタイトル
	*/
	void WindowManager::SetTitle(const std::string& title)
	{
		if (!window)
		{
			LOG_WARNINGS("ウィンドウが初期化されていません");
			return;
		}

		glfwSetWindowTitle(window, title.c_str());
	}

	/**
	* ウィンドウのサイズを取得
	*/
	Vector2 WindowManager::GetSize() const
	{
		if (!window)
		{
			LOG_WARNINGS("ウィンドウが初期化されていません");
			return Vector2::zero;
		}

		int widht = 0;
		int height = 0;
		// ウィンドウサイズを取得
		glfwGetWindowSize(window, &widht, &height);
		Vector2 size = Vector2(static_cast<float>(widht), static_cast<float>(height));

		return size;
	}

	/**
	* ウィンドウオブジェクトを取得
	*/
	GLFWwindow& WindowManager::GetObject() const
	{
		if (!window)
		{
			LOG_WARNINGS("ウィンドウが初期化されていません");
		}
		return *window;
	}

	/**
	* ウィンドウが閉じているか取得
	*
	* @retval true	ウィンドウが閉じている
	* @retval false ウィンドウが開いている
	*/
	bool WindowManager::IsClose() const
	{
		if (!window)
		{
			return true;
		}
		return !glfwWindowShouldClose(window);
	}

	/**
	* ウィンドウを閉じる
	*/
	void WindowManager::Close()
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}