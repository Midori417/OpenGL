/**
* @file InputKey.h
*/
#ifndef FGENGINE_INPUTKEY_H_INCLUDED
#define FGENGINE_INPUTKEY_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include "KeyCode.h"
#include <vector>

// 先行宣言
struct GLFWwindow;

namespace FGEngine
{
	/**
	* キーボード入力
	*/
	class InputKey : public Singleton<InputKey>
	{
		friend Singleton<InputKey>;
		friend class InputManager;
	private:

		/**
		* デフォルトコンストラクタ
		*/
		InputKey() = default;

	private: // InputMangerで呼び出す

		/**
		* キーボード入力を初期化
		* 
		* @retval true	正常に初期化
		* @retval false	初期化失敗
		*/
		bool Initialize();

		/**
		* キーボード入力の状態を更新
		* 
		* @param window ウィンドウオブジェクト
		*/
		void Update(GLFWwindow* window);

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
		static std::vector<KeyState> keyState;

		// 何かしらのキーが押されていたらtrue
		static bool anyKey;
	};
}

#endif // !FGENGINE_INPUTKEY_H_INCLUDED
