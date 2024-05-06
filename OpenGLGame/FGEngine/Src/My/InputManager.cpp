/**
* @file InputManager.cpp
*/
#include "InputManager.h"
#include "InputKey.h"
#include "InputMouse.h"
#include <GLFW/glfw3.h>

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

	/**
	* Axisを取得
	* 
	* @param axis アクシズ名
	*/
	float InputManager::GetAxis(const std::string& axis)
	{
		return 0.0f;
	}
}