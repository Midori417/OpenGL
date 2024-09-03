/**
* @file InputMouse.h
*/
#ifndef FGENGINE_INPUTMOUSE_H_INCLUDED
#define FGENGINE_INPUTMOUSE_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "FGEngine/Math/Vector2.h"
#include "MouseButton.h"
#include <vector>

// 先行宣言
struct GLFWwindow;

namespace FGEngine
{
	/**
	* マウス入力
	*/
	class InputMouse : public Singleton<InputMouse>
	{
		friend Singleton<InputMouse>;
		friend class InputManager;
	private:

		/**
		* デフォルトコンストラクタ
		*/
		InputMouse() = default;
		
	private: // InputMangerで呼び出す

		/**
		* マウス入力を初期化
		* 
		* @retval true	正常に初期化
		* @retval false	初期化失敗
		*/
		bool Initialize();

		/**
		* マウス入力の状態を更新
		* 
		* @param winndow ウィンドウオブジェクト
		*/
		void Update(GLFWwindow* window);

	public:

		/**
		* マウスの位置を取得
		*/
		static Vector2 GetMousePosition();

		/**
		* マウスのボタンを押しているを取得
		* 
		* @param mouseButton 対応しているボタン
		* 
		* @retval true	押している
		* @retval false	押していない
		*/
		static bool GetMouseButton(MouseButton mouseButton);

		/**
		* マウスのボタンが上がったかを取得
		* 
		* @param mouseButton 対応しているボタン
		* 
		* @retval true	押しあがっている
		* @retval false	押し上げっていない
		*/
		static bool GetMouseButtonUp(MouseButton mouseButton);

		/**
		* マウスのボタンが下がったかを取得
		* 
		* @param mouseButton 対応しているボタン
		* 
		* @retval true	押し下がった
		* @retval false	押し下がっていない
		*/
		static bool GetMouseButtonDown(MouseButton mouseButton);

		/**
		* マウスがクリックしたかを取得
		* 
		* @param mouseButton 対応しているボタン
		* 
		* @retval true クリックした
		* @retval false クリックしていない
		*/
		static bool GetMouseButtonClick(MouseButton mouseButton);

	private:

		/**
		* マウスボタンの状態
		*/
		struct MouseButtonState
		{
		public:

			// 前回のフレームに押されていたかの有無
			// true=押されていた : false=押されていない
			bool old = false;

			// ボタンが下がったかの有無
			// true=下がった : false=下がっていない
			bool down = false;
			
			// ボタンが上がったかの有無
			// true=上がった : false=上がっていない
			bool up = false;
			
			// ボタンが押されているかの有無
			// true=押されている : false=押されていない
			bool on = false;

			// クリックの有無
			// true=クリックした : false=クリックしていない
			bool click = false;

			// ボタンが押されている時間
			float timer = 0;
		};

		// マウスの状態配列
		static std::vector<MouseButtonState> mouseButtonsState;

		// マウスの位置
		static Vector2 mousePosition;

		// マウスのクリック受付時間
		static constexpr float mouseClickSpeed = 0.3f;
	};
}

#endif // !FGENGINE_INPUTMOUSE_H_INCLUDED
