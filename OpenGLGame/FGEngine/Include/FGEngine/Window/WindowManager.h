/**
* @file WindowManger.h
*/
#ifndef FGENGINE_WINDOWMANAGER_H_INCLUDED
#define FGENGINE_WINDOWMANAGER_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "FGEngine/Math/MathFrd.h"
#include <vector>
#include <string>

// 先行宣言
struct GLFWwindow;

namespace FGEngine
{
	/**
	* ウィンドウ管理クラス
	*/
	class WindowManager :  public Singleton<WindowManager>
	{
		friend Singleton<WindowManager>;
		friend class GameEngine;
	private:
		
		/**
		* デフォルトコンストラクタ
		*/
		WindowManager() = default;

		/**
		* デストラクタ
		*/
		~WindowManager();

		// コピーと代入を禁止
		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;

	private:

		/**
		* ウィンドウマネージャーを初期化
		* 
		* @retval 0		初期化成功
		* @retval 0以外	初期化失敗
		*/
		int Initialze();

		/**
		* ウィンドウの描画開始
		*/
		void Begin();

		/**
		* ウィンドウの描画終了
		*/
		void End();

	public:

		/**
		* ウィンドウタイトルを取得
		*/
		std::string GetTitle() const;

		/**
		* ウィンドウタイトルを変更
		* 
		* @param title 変更するタイトル
		*/
		void SetTitle(const std::string& title);

		/**
		* ウィンドウのサイズを取得
		*/
		Vector2 GetSize() const;

		/**
		* ウィンドウオブジェクトを取得
		*/
		GLFWwindow& GetObject() const;

		/**
		* ウィンドウが閉じているか取得
		* 
		* @retval true	ウィンドウが閉じている
		* @retval false ウィンドウが開いている
		*/
		bool IsClose() const;

		/**
		* ウィンドウを閉じる
		*/
		void Close();

	private:

		// ウィンドウオブジェクト
		GLFWwindow* window = nullptr;
	};
}

#endif // !FGENGINE_WINDOW_H_INCLUDED
