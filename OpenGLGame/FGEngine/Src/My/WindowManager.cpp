/**
* @file WindowManager.cpp
*/
#include "WindowManager.h"

namespace FGEngine::WindowSystem
{
	/**
	* ウィンドウを作成
	*
	* @param windowTitle ウィンドウタイトル
	*
	* @retval	作成したウィンドウオブジェクト
	*			nullptr 作成に失敗
	*/
	void WindowManager::CreateWindow(const std::string& windowTitle)
	{
		// デバッグコンテキストの作成
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

		// ウィンドウをフルスクリーンに設定
		//glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		// 描画ウィンドウの作成
		auto window = glfwCreateWindow(1280, 720, windowTitle.c_str(), nullptr, nullptr);

		// ウィンドウ配列に追加
		windows.push_back(window);

	}

	/**
	* ウィンドウの描画を開始
	*/
	void WindowManager::Begin()
	{
		if (windows.empty())
		{
			return;
		}

		for (auto window : windows)
		{
			// 描画先のウィンドウを設定
			glfwMakeContextCurrent(window);

			// バックバッファをクリア
			glClearColor(bufferColor.r, bufferColor.g, bufferColor.b, bufferColor.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

	}

	/**
	* ウィンドウの描画を終了
	*/
	void WindowManager::End()
	{
		size_t i = 0;
		for (auto window : windows)
		{

			// フロントバッファとバックバッファを入れ替え
			glfwSwapBuffers(window);

			// OSからの要求を処理する
			glfwPollEvents();

			// ウィンドウが閉じれられたら
			// ウィンドウとウィンドウオブジェクトを削除する
			if (IsClose(i))
			{
				glfwDestroyWindow(window);
			}

			// 描画先ウィンドウの設定を解除
			glfwMakeContextCurrent(nullptr);
			i++;
		}

	}

	/**
	* ウィンドウが閉じているか取得
	*
	* @retval true	閉じている
	* @retval false	閉じていない
	*/
	bool WindowManager::IsClose(size_t index)
	{
		if (!windows[index])
		{
			return true;
		}
		return glfwWindowShouldClose(windows[index]);
	}


	/**
	* ウィンドウオブジェクトを取得
	*/
	GLFWwindow& WindowManager::GetWindow(size_t index)
	{
		return *windows[index];
	}

	/**
	* ウィンドウのサイズをVector2で取得
	*/
	Vector2 WindowManager::GetWindowSize(size_t index)
	{
		// フレームバッファの大きさを取得
		int w, h;
		glfwGetFramebufferSize(windows[index], &w, &h);

		return Vector2{ static_cast<float>(w), static_cast<float>(h) };
	}

	/**
	* ウィンドウサイズを取得
	*
	* @param w ウィンドウの横幅を格納する
	* @param h ウィンドウの縦幅を格納する
	*/
	void WindowManager::GetWindowSize(GLsizei& w, GLsizei& h, size_t index)
	{
		glfwGetFramebufferSize(windows[index], &w, &h);
	}

	/**
	* ウィンドウのサイズのアスペクトを取得
	*/
	float WindowManager::GetWindowAspectRatio()
	{
		// フレームバッファの大きさを取得
		const Vector2 size = GetWindowSize();

		// アスペクト比を返す
		return size.x / size.y;
	}

	/**
	* バッファクリアのカラーを設定
	*/
	void WindowManager::SeteBufferClearColor(const Color& color)
	{
		bufferColor = color;
	}
}