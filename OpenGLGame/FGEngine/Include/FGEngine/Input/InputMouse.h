/**
* @file InputMouse.h
*/
#ifndef FGENGINE_INPUTMOUSE_H_INCLUDED
#define FGENGINE_INPUTMOUSE_H_INCLUDED
#include "FGEngine/Math/Vector2.h"
#include <vector>

// 先行宣言
struct GLFWwindow;

namespace FGEngine
{
	// 先行宣言
	enum class MouseButton;

	/**
	* マウス入力
	* 入力管理クラスのみ生成したいのでコンストラクタはprivate
	*/
	class InputMouse
	{
		friend class InputManager;
	private:
		
		/**
		* デフォルトコンストラクタ
		*/
		InputMouse() = default;

	private:

		/**
		* マウス入力を初期化
		* 
		* @retval 0		正常に初期化
		* @retval 0以外	エラー発生
		*/
		int Initialize();

		/**
		* マウスの状態を更新
		*
		* @param winndow ウィンドウオブジェクト
		*/
		void Update(GLFWwindow* window);

	private:

		/**
		* マウスの位置を取得
		*/
		Vector2 GetMousePosition();

		/**
		* マウスのボタンを押しているを取得
		* 
		* @param mouseButton 対応しているボタン
		* 
		* @retval true	押している
		* @retval false	押していない
		*/
		bool GetMouseButton(MouseButton mouseButton);

		/**
		* マウスのボタンが上がったかを取得
		* 
		* @param mouseButton 対応しているボタン
		* 
		* @retval true	押しあがっている
		* @retval false	押し上げっていない
		*/
		bool GetMouseButtonUp(MouseButton mouseButton);

		/**
		* マウスのボタンが下がったかを取得
		* 
		* @param mouseButton 対応しているボタン
		* 
		* @retval true	押し下がった
		* @retval false	押し下がっていない
		*/
		bool GetMouseButtonDown(MouseButton mouseButton);

		/**
		* マウスがクリックしたかを取得
		* 
		* @param mouseButton 対応しているボタン
		* 
		* @retval true クリックした
		* @retval false クリックしていない
		*/
		bool GetMouseButtonClick(MouseButton mouseButton);

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

		// マウスの状態
		std::vector<MouseButtonState> mouseButtonsState;

		// マウスの位置
		Vector2 mousePosition = Vector2::zero;

		// マウスのクリック受付時間
		const float mouseClickSpeed = 0.3f;
	};
}

#endif // !FGENGINE_INPUTMOUSE_H_INCLUDED
