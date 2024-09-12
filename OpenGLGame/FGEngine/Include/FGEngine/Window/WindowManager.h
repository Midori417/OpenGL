/**
* @file WindowManger.h
*/
#ifndef FGENGINE_WINDOWMANAGER_H_INCLUDED
#define FGENGINE_WINDOWMANAGER_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Color.h"
#include <string>
#include <vector>

// 先行宣言
struct GLFWwindow;
	
namespace FGEngine
{
	/**
	* ウィンドウ管理クラス
	*/
	class WindowManager : public Singleton<WindowManager>
	{
		friend Singleton<WindowManager>;
		friend class EngineCore;
	private:

		/**
		* デフォルトコンストラクタ
		*/
		WindowManager() = default;

	public:	// 禁止事項

		// コピーを禁止
		WindowManager(const WindowManager&) = delete;

		// 代入を禁止
		WindowManager& operator=(const WindowManager&) = delete;

	private: // EngineCoreで呼び出す

		/**
		* ウィンドウマネージャーを初期化
		* 
		* @retval true	正常に初期化
		* @retval false	初期化失敗
		*/
		bool Initialize();

		/**
		* ウィンドウの描画を開始
		*/
		void Begin();

		/**
		* ウィンドウへの描画を終了
		*/
		void End();

	public:	// 名前を取得と設定

		/**
		* ウィンドウタイトルを取得
		*/
		static std::string GetTitle();

		/**
		* ウィンドウタイトルを設定
		* 
		* @param title 設定するウィンドウタイトル
		*/
		static void SetTitle(const std::string& title);

	public:

		/**
		* ウィンドウを終了
		*/
		static void WindowClose();

		/**
		* ウィンドウが閉じているか取得
		*
		* @retval true	閉じている
		* @retval false	閉じていない
		*/
		static bool IsClose();

		/**
		* ウィンドウオブジェクトを取得
		*/
		static GLFWwindow& GetWindow();

		/**
		* ウィンドウのサイズをVector2で取得
		*/
		static Vector2 GetWindowSize();

		/**
		* バッファクリアのカラーを設定
		*/
		static void SeteBufferClearColor(const Color& color);

	private:

		// ウィンドウオブジェクト
		static GLFWwindow* window;

		// クリアバッファのカラー
		static Color bufferColor;
	};
}

#endif // !FGENGINE_WINDOW_H_INCLUDED