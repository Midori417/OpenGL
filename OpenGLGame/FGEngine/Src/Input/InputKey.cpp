/**
* @file InputKey.cpp
*/
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/KeyCode.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	/**
	* キー入力対応ビットマップ
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
	* キー入力を初期化
	*
	* @retval 0		初期化成功
	* @retval 0以外	初期化失敗
	*/
	int InputKey::Initialize()
	{
		keyState.resize((int)KeyCode::Max);
		return 0;
	}

	/**
	* キーボードの状態を更新
	* 
	* @param window ウィンドウオブジェクト
	*/
	void InputKey::Update(GLFWwindow* window)
	{
		isAnyKey = false;

		// キーの状態を更新
		for (int i = 0; i < (int)KeyCode::Max; ++i)
		{
			// 現在のキーボードの状態を取得する
			const bool now = glfwGetKey(window, KEY_ASSIGN[i]) == GLFW_PRESS;
			keyState[i].on = now;

			if (now)
			{
				isAnyKey = true;
			}

			// 前回のフレームで押されてなくて現在のフレームで押されていたら押し下がったにする
			keyState[i].down = now && !keyState[i].old;

			// 前回のフレームが押されていて現在のフレームが押されてなければ押しあがったにする
			keyState[i].up = !now && keyState[i].old;

			// 前回のフレームの更新
			keyState[i].old = now;
		}
	}

	/**
	* キーが押されているかを取得
	*
	* @param keyCode 対応しているキー
	*
	* @retval true	押している
	* @retval false	押していない
	*/
	bool InputKey::GetKey(KeyCode keyCode) const
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
	* @param keyCode 対応しているキー
	*
	* @retval true	押しあがっている
	* @retval false	押し上げっていない
	*/
	bool InputKey::GetKeyUp(KeyCode keyCode) const
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
	* @param keyCode 対応しているキー
	*
	* @retval true	押し下がった
	* @retval false	押し下がっていない
	*/
	bool InputKey::GetKeyDown(KeyCode keyCode) const
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
	bool InputKey::AnyKey() const
	{
		return isAnyKey;
	}
}