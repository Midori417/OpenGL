/**
* @file InputKey.h
*/
#ifndef FGENGINE_INPUTKEY_H_INCLUDED
#define FGENGINE_INPUTKEY_H_INCLUDED
#include "SystemFrd.h"
#include "KeyCode.h"

namespace FGEngine::InputSystem
{
	/**
	* キーボード入力
	*/
	class InputKey
	{
	public:

		friend InputSystem::InputManager;

		// コンストラクタ・デストラクタ
		InputKey() = default;
		~InputKey() = default;

	private:

		/**
		* キーボードの状態を更新
		* 
		* @param window ウィンドウオブジェクト
		*/
		static void Update(GLFWwindow* window);

	public:

		/**
		* キーが押されているかを取得
		*
		* @param keyCod	対応しているキー
		*
		* @retval true	押している
		* @retval false	押していない
		*/
		static bool GetKey(KeyCode keyCode);

		/**
		* キーが上がったかを取得
		*
		* @param keyCod	対応しているキー
		*
		* @retval true	押しあがっている
		* @retval false	押し上げっていない
		*/
		static bool GetKeyUp(KeyCode keyCode);

		/**
		* キーが下がったかを取得
		*
		* @param keyCod	対応しているキー
		*
		* @retval true	押し下がった
		* @retval false	押し下がっていない
		*/
		static bool GetKeyDown(KeyCode keyCode);

		/**
		* 何かしらのキーが押されているか取得
		* 
		* @retval true 押されている
		* @retval false 押されていない
		*/
		static bool AnyKey();

	private:

		/**
		* キーの状態
		*/
		struct KeyState
		{
			// 前回のフレームに押されていたかの有無
			// true=押されていた : false=押されていない
			bool old = false;

			//	キーが下がったかの有無
			// true=下がった : false=下がっていない
			bool down = false;

			// キーが上がったかの有無
			// true=上がった : false=上がっていない
			bool up = false;

			// キーが押されているかの有無
			// true=押されている : false=押されていない
			bool on = false;
		};


		// キーの状態配列
		static KeyState keyState[(int)KeyCode::Max];

		// 何かしらのキーが押されていたらtrue:何も押されていなければfasle
		static bool anyKey;
	};
}

#endif // !FGENGINE_INPUTKEY_H_INCLUDED
