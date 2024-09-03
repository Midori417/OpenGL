/**
* @file InputKey.cpp
*/
#include "FGEngine/Input/InputKey.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// 静的変数の初期化
	std::vector<InputKey::KeyState> InputKey::keyState;
	bool InputKey::anyKey = false;

	/**
	* キーボードリスト対応ビットマップ
	*/
	const int KEY_ASSIGN[(int)KeyCode::Max]
	{
		GLFW_KEY_ENTER,

		GLFW_KEY_ESCAPE,
		GLFW_KEY_F1,
		GLFW_KEY_F2,
		GLFW_KEY_F3,
		GLFW_KEY_F4,
		GLFW_KEY_F5,
		GLFW_KEY_F6,
		GLFW_KEY_F7,
		GLFW_KEY_F8,
		GLFW_KEY_F9,
		GLFW_KEY_F10,
		GLFW_KEY_F11,
		GLFW_KEY_F12,

		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_4,
		GLFW_KEY_5,
		GLFW_KEY_6,
		GLFW_KEY_7,
		GLFW_KEY_8,
		GLFW_KEY_9,
		GLFW_KEY_0,

		GLFW_KEY_TAB,
		GLFW_KEY_Q,
		GLFW_KEY_W,
		GLFW_KEY_E,
		GLFW_KEY_R,
		GLFW_KEY_T,
		GLFW_KEY_Y,
		GLFW_KEY_U,
		GLFW_KEY_I,
		GLFW_KEY_O,
		GLFW_KEY_P,

		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_D,
		GLFW_KEY_F,
		GLFW_KEY_G,
		GLFW_KEY_H,
		GLFW_KEY_J,
		GLFW_KEY_K,
		GLFW_KEY_L,
		GLFW_KEY_SEMICOLON,

		GLFW_KEY_LEFT_SHIFT,
		GLFW_KEY_Z,
		GLFW_KEY_X,
		GLFW_KEY_C,
		GLFW_KEY_V,
		GLFW_KEY_B,
		GLFW_KEY_N,
		GLFW_KEY_M,
		GLFW_KEY_COMMA,
		GLFW_KEY_RIGHT_SHIFT,

		GLFW_KEY_LEFT_CONTROL,
		GLFW_KEY_LEFT_ALT,
		GLFW_KEY_SPACE,
		GLFW_KEY_RIGHT_CONTROL,

		GLFW_KEY_UP,
		GLFW_KEY_DOWN,
		GLFW_KEY_LEFT,
		GLFW_KEY_RIGHT,
	};

	/**
	* キーボード入力を初期化
	*
	* @retval true	正常に初期化
	* @retval false	初期化失敗
	*/
	bool FGEngine::InputKey::Initialize()
	{
		// キー状態配列を生成
		keyState.resize((int)KeyCode::Max);

		return true;
	}

	/**
	* キーボードの状態を更新
	* 
	* @param window ウィンドウオブジェクト
	*/
	void InputKey::Update(GLFWwindow* window)
	{
		anyKey = false;

		for (int i = 0; i < (int)KeyCode::Max; ++i)
		{
			// 押されているから取得
			const bool now = glfwGetKey(window, KEY_ASSIGN[i]) == GLFW_PRESS;

			// 一個でも押されていたらtrue
			if (now)
			{
				anyKey = true;
			}

			// 押されているか
			keyState[i].on = now;

			// 押し下がった条件
			// 現在押されていて、前回押されていない
			keyState[i].down = now && !keyState[i].old;

			// 押しあがった条件
			// 現在押されていない、前回押されている
			keyState[i].up = !now && keyState[i].old;

			// 次に前回の状態を使うためここで代入
			keyState[i].old = now;
		}
	}

	/**
	* キーが押されているかを取得
	*
	* @param keyCod	対応しているキー
	*
	* @retval true	押している
	* @retval false	押していない
	*/
	bool InputKey::GetKey(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max)
		{
			return false;
		}
		return keyState[int(keyCode)].on;
	}

	/**
	* キーが上がったかを取得
	*
	* @param keyCod	対応しているキー
	*
	* @retval true	押しあがっている
	* @retval false	押し上げっていない
	*/
	bool InputKey::GetKeyUp(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max)
		{
			return false;
		}
		return keyState[int(keyCode)].up;
	}

	/**
	* キーが下がったかを取得
	*
	* @param keyCod	対応しているキー
	*
	* @retval true	押し下がった
	* @retval false	押し下がっていない
	*/
	bool InputKey::GetKeyDown(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max) 
		{
			return false;
		}
		return keyState[int(keyCode)].down;
	}

	/**
	* 何かしらのキーが押されているか取得
	*
	* @retval true 押されている
	* @retval false 押されていない
	*/
	bool InputKey::AnyKey()
	{
		return anyKey;
	}
}