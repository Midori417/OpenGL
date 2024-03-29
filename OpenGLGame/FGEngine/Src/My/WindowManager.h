/**
* @file WindowManger.h
*/
#ifndef FGENGINE_WINDOWMANAGER_H_INCLUDED
#define FGENGINE_WINDOWMANAGER_H_INCLUDED
#include "Package/Glad.h"
#include <GLFW/glfw3.h>
#include "Singleton.h"
#include "VecMath.h"
#include "Color.h"
#include <string>
	
namespace FGEngine::WindowSystem
{
	/**
	* ウィンドウ管理クラス
	*/
	class WindowManager : public Singleton<WindowManager>
	{
	private:
		
		friend Singleton<WindowManager>;

		// コンストラクタ
		WindowManager() = default;

	public:



		// コピーと代入を禁止
		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;

		/**
		* ウィンドウを作成
		*
		* @param windowTitle ウィンドウタイトル
		*
		* @retval	作成したウィンドウオブジェクト
		*			nullptr 作成に失敗
		*/
		void CreateWindow(const std::string& windowTitle);

		/**
		* ウィンドウの描画を開始
		*/
		void Begin();

		/**
		* ウィンドウへの描画を終了
		*/
		void End();

		/**
		* ウィンドウが閉じているか取得
		*
		* @retval true	閉じている
		* @retval false	閉じていない
		*/
		bool IsClose(size_t index = 0);

		/**
		* ウィンドウオブジェクトを取得
		*/
		GLFWwindow& GetWindow(size_t index = 0);

		/**
		* ウィンドウのサイズをVector2で取得
		*/
		Vector2 GetWindowSize(size_t index = 0);

		/**
		* ウィンドウサイズを取得
		*
		* @param w ウィンドウの横幅を格納する
		* @param h ウィンドウの縦幅を格納する
		*/
		void GetWindowSize(GLsizei& w, GLsizei& h, size_t index = 0);

		/**
		* ウィンドウのサイズのアスペクトを取得
		*/
		float GetWindowAspectRatio();

		/**
		* バッファクリアのカラーを設定
		*/
		void SeteBufferClearColor(const Color& color);

	private:

		std::vector<GLFWwindow*> windows;	// ウィンドウ配列
		Color bufferColor = Color::black;

	};
}

#endif // !FGENGINE_WINDOW_H_INCLUDED
