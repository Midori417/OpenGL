/**
* @file InputMouse.cpp
*/
#include "FGEngine/Input/InputMouse.h"
#include "FGEngine/Input/MouseButton.h"
//#include "FGEngine/Time.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	/**
	* マウスボタンリスト対応ビットマップ
	*/
	const int MOUSEBUTTON_ASSIGN[(int)MouseButton::Max]
	{
		GLFW_MOUSE_BUTTON_LEFT,
		GLFW_MOUSE_BUTTON_RIGHT,
		GLFW_MOUSE_BUTTON_MIDDLE,
	};

	/**
	* マウス入力を初期化
	*
	* @retval 0		正常に初期化
	* @retval 0以外	エラー発生
	*/
	int InputMouse::Initialize()
	{
		// マウスボタン配列を確保
		mouseButtonsState.resize((int)MouseButton::Max);

		return 0;
	}

	/**
	* マウスの状態を更新
	*
	* @param window ウィンドウオブジェクト
	*/
	void InputMouse::Update(GLFWwindow* window)
	{
		for (int i = 0; i < (int)MouseButton::Max; ++i)
		{
			// 現在のマウスの状態を取得する
			const bool now = glfwGetMouseButton(window, MOUSEBUTTON_ASSIGN[i]) == GLFW_PRESS;
			mouseButtonsState[i].on = now;

			// 前回のフレームで押されてなくて現在のフレームで押されていたら押し下がったにする
			mouseButtonsState[i].down = now && !mouseButtonsState[i].old;

			// 前回のフレームが押されていて現在のフレームが押されてなければ押しあがったにする
			mouseButtonsState[i].up = !now && mouseButtonsState[i].old;

			// 押されている時間を更新
			if (mouseButtonsState[i].old)
			{
				//mouseButtonsState[i].timer += Time::DeltaTime();
			}
			else
			{
				mouseButtonsState[i].timer = 0;
			}
			// 以下の条件をすべて満たす場合はクリックと判定
			// - 前フレームで押されている
			// - 現在のフレームで押されていない
			// - 押されている時間が0.3秒以下
			if (mouseButtonsState[i].old && !mouseButtonsState[i].on && mouseButtonsState[i].timer <= mouseClickSpeed)
			{
				mouseButtonsState[i].click = true;
			}
			else
			{
				mouseButtonsState[i].click = false;
			}

			// 前回のフレームの更新
			mouseButtonsState[i].old = now;
		}
	}

	/**
	* マウスの位置を取得
	*/
	Vector2 InputMouse::GetMousePosition()
	{
		return mousePosition;
	}

	/**
	* マウスのボタンを押しているを取得
	*
	* @param mouseButton 対応しているボタン
	*
	* @retval true	押している
	* @retval false	押していない
	*/
	bool InputMouse::GetMouseButton(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].on;
	}

	/**
	* マウスのボタンが上がったかを取得
	*
	* @param mouseButton 対応しているボタン
	*
	* @retval true	押しあがっている
	* @retval false	押し上げっていない
	*/
	bool InputMouse::GetMouseButtonUp(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].up;
	}

	/**
	* マウスのボタンが下がったかを取得
	*
	* @param mouseButton 対応しているボタン
	*
	* @retval true	押し下がった
	* @retval false	押し下がっていない
	*/
	bool InputMouse::GetMouseButtonDown(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].down;
	}

	/**
	* マウスがクリックしたかを取得
	*
	* @param mouseButton 対応しているボタン
	*
	* @retval true クリックした
	* @retval false クリックしていない
	*/
	bool InputMouse::GetMouseButtonClick(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].click;
	}

}