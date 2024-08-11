/**
* @file InputManager.cpp
*/
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"
#include <GLFW/glfw3.h>

namespace FGEngine::InputSystem
{
	// スタティック変数の初期化
	std::unordered_map<Axis, float> InputManager::axisList;

	/**
	* インプットマネージャを初期化
	*/
	int InputManager::Initialize()
	{
		// Axisの追加
		axisList.emplace(Axis::Horizontal, 0.0f);
		axisList.emplace(Axis::Vertical, 0.0f);

		return 0;
	}

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

		// アクシズの更新
		AxisUpdate();
	}

	/**
	* Axisの更新
	*/
	void InputManager::AxisUpdate()
	{
		// Horizontal
		{
			auto horizontal = axisList.find(Axis::Horizontal);
			if (horizontal != axisList.end())
			{
				if (InputKey::GetKey(KeyCode::A) || InputKey::GetKey(KeyCode::LeftArrow))
				{
					horizontal->second = -1;
				}
				else if (InputKey::GetKey(KeyCode::D) || InputKey::GetKey(KeyCode::RightArrow))
				{
					horizontal->second = 1;
				}
				else if (!InputKey::GetKey(KeyCode::A) && !InputKey::GetKey(KeyCode::LeftArrow) &&
					!InputKey::GetKey(KeyCode::D) && !InputKey::GetKey(KeyCode::RightArrow))
				{
					horizontal->second = 0;
				}
			}
		}
		// Vertical
		{
			auto vertical = axisList.find(Axis::Vertical);
			if (vertical != axisList.end())
			{
				if (InputKey::GetKey(KeyCode::S) || InputKey::GetKey(KeyCode::DownArrow))
				{
					vertical->second = -1;
				}
				else if (InputKey::GetKey(KeyCode::W) || InputKey::GetKey(KeyCode::UpArrow))
				{
					vertical->second = 1;
				}
				else if(!InputKey::GetKey(KeyCode::S) && !InputKey::GetKey(KeyCode::DownArrow) && 
					!InputKey::GetKey(KeyCode::W) && !InputKey::GetKey(KeyCode::UpArrow))
				{
					vertical->second = 0;
				}
			}
		}

	}

	/**
	* Axisを取得
	* 
	* @param axis アクシズ名
	*/
	float InputManager::GetAxis(Axis axis)
	{
		// axisを検索
		auto tmp = axisList.find(axis);
		if (tmp == axisList.end())
		{
			// アクシズが対応していない
			return 0.0f;
		}

		return tmp->second;
	}
}