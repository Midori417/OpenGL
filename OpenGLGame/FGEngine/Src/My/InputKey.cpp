/**
* @file InputKey.cpp
*/
#include "InputKey.h"

namespace FGEngine::InputSystem
{
	// スタティック変数の初期
	InputKey::KeyState InputKey::keyState[] = { InputKey::KeyState() };

	/**
	* キーボードの状態を更新
	* 
	* @param window ウィンドウオブジェクト
	*/
	void InputKey::Update(GLFWwindow* window)
	{
		for (int i = 0; i < (int)KeyCode::Max; ++i)
		{
			const bool now = glfwGetKey(window, KEY_ASSIGN[i]) == GLFW_PRESS;

			keyState[i].on = now;
			keyState[i].down = now && !keyState[i].old;
			keyState[i].up = !now && keyState[i].old;

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
		return keyState[int(keyCode)].down;
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
		if (keyCode == KeyCode::Max) {
			return false;
		}
		return keyState[int(keyCode)].up;
	}
}