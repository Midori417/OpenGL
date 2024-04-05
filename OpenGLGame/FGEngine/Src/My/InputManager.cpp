/**
* @file InputManager.cpp
*/
#include "InputManager.h"
#include "InputKey.h"
#include "InputMouse.h"

namespace FGEngine::InputSystem
{
	/**
	* インプットマネージャを更新
	* 
	* @param window ウィンドウオブジェクト
	*/
	void InputManager::Update(GLFWwindow* window)
	{
		// キーボードの更新
		InputKey::Update(window);

		// マウスを更新
		InputMouse::Update(window);
	}
}