/**
* @file WindowManager.cpp
*/
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Package/Glad.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// 静的変数の初期化
	GLFWwindow* WindowManager::window = nullptr;
	Color WindowManager::bufferColor = Color::black;

	/**
	* ウィンドウマネージャーを初期化
	*
	* @retval true	正常に初期化
	* @retval false	初期化失敗
	*/
	bool WindowManager::Initialize()
	{
		// デバッグコンテキストの作成
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		// ウィンドウをフルスクリーンに設定
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		// 描画ウィンドウの作成
		window = glfwCreateWindow(1280, 720, "Window", nullptr, nullptr);
		if (!window)
		{
			return false;
		}

		return true;
	}

	/**
	* ウィンドウの描画を開始
	*/
	void WindowManager::Begin()
	{
		if (!window)
		{
			return;
		}

		// 描画先のウィンドウを設定
		glfwMakeContextCurrent(window);

		// バックバッファをクリア
		glClearColor(bufferColor.r, bufferColor.g, bufferColor.b, bufferColor.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/**
	* ウィンドウの描画を終了
	*/
	void WindowManager::End()
	{
		// フロントバッファとバックバッファを入れ替え
		glfwSwapBuffers(window);

		// OSからの要求を処理する
		glfwPollEvents();

		// ウィンドウが閉じれられたら
		// ウィンドウとウィンドウオブジェクトを削除する
		if (IsClose())
		{
			WindowClose();
		}

		// 描画先ウィンドウの設定を解除
		glfwMakeContextCurrent(nullptr);
	}

	/**
	* ウィンドウタイトルを取得
	*/
	std::string WindowManager::GetTitle()
	{
		if (!window)
		{
			return "";
		}

		return glfwGetWindowTitle(window);
	}

	/**
	* ウィンドウタイトルを設定
	*
	* @param title 設定するウィンドウタイトル
	*/
	void WindowManager::SetTitle(const std::string& title)
	{
		if (!window)
		{
			return;
		}

		glfwSetWindowTitle(window, title.c_str());
	}

	/**
	* ウィンドウが閉じているか取得
	*
	* @retval true	閉じている
	* @retval false	閉じていない
	*/
	bool WindowManager::IsClose()
	{
		if (!window)
		{
			return true;
		}
		return glfwWindowShouldClose(window);
	}

	/**
	* ウィンドウを終了
	*/
	void WindowManager::WindowClose()
	{
		if (!window)
		{
			return;
		}
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}


	/**
	* ウィンドウオブジェクトを取得
	*/
	GLFWwindow& WindowManager::GetWindow()
	{
		return *window;
	}

	/**
	* ウィンドウのサイズをVector2で取得
	*/
	Vector2 WindowManager::GetWindowSize()
	{
		// フレームバッファの大きさを取得
		int w, h;
		glfwGetFramebufferSize(window, &w, &h);

		return Vector2{ static_cast<float>(w), static_cast<float>(h) };
	}

	/**
	* バッファクリアのカラーを設定
	*/
	void WindowManager::SeteBufferClearColor(const Color& color)
	{
		bufferColor = color;
	}
}