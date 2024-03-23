/**
* @file GamePad.cpp
*/
#include "GamePad.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	GamePad* GamePad::gamepad = nullptr;
	float* GamePad::axes = nullptr;
	unsigned char* GamePad::buttons = nullptr;
	int GamePad::padId = 0;

	/**
	* ゲームパッドを破壊
	*/
	void GamePad::DestoryGamePad()
	{
		if (axes != nullptr)
		{
			axes = nullptr;
			delete axes;
		}
		if (buttons != nullptr)
		{
			buttons = nullptr;
			delete buttons;
		}
		gamepad = nullptr;
		delete gamepad;
	}

	/**
	* ゲームパッドを取得
	*/
	GamePad* GamePad::GetGamePad()
	{
		return gamepad;
	}

	void GamePad::Update()
	{
		// コントローラが接続されているか調べる
		if (glfwJoystickPresent(padId)) {
			// 生成されていなけば生成
			gamepad = new GamePad;
			axes = new float(0);
			buttons = new unsigned char(0);
			int buttonCount, axisCount;
			axes = const_cast<float*>(glfwGetJoystickAxes(GamePad::GetGamePad()->GetPadId(), &axisCount));
			buttons = const_cast<unsigned char*>(glfwGetJoystickButtons(GamePad::GetGamePad()->GetPadId(), &buttonCount));
		}
		else if (!glfwJoystickPresent(padId)) {
			if (GamePad::GetGamePad() != nullptr)
			{
				DestoryGamePad();
			}
		}
	}

	/**
	* パットナンバーを取得
	*/
	int GamePad::GetPadId()
	{
		return padId;
	}

	bool GamePad::leftStickButton()
	{
		return  buttons[10] == GLFW_PRESS;
	}
	bool GamePad::rightStickButton()
	{
		return  buttons[11] == GLFW_PRESS;
	}
	DpadControl GamePad::dpad()
	{
		bool upButton = buttons[14] == GLFW_PRESS;
		bool rightButton = buttons[15] == GLFW_PRESS;
		bool downButton = buttons[16] == GLFW_PRESS;
		bool leftButton = buttons[17] == GLFW_PRESS;

		return { upButton, rightButton, downButton, leftButton };
	}
	bool GamePad::leftShoulder()
	{
		return buttons[4] == GLFW_PRESS;
	}
	bool GamePad::rightShoulder()
	{
		return buttons[5] == GLFW_PRESS;
	}
	StickControl GamePad::leftStick()
	{
		float x = 0;
		if (axes[0] > 0.5 || axes[0] < -0.5f)
		{
			x = axes[0];
		}
		else
		{
			x = 0;
		}
		float y = 0;
		if (axes[1] > 0.2 || axes[1] < -0.2f)
		{
			y = axes[1];
		}
		else
		{
			y = 0;
		}


		return { x, -y };
	}
	StickControl GamePad::rightStick()
	{
		float x = 0;
		if (axes[2] > 0.5 || axes[2] < -0.5f)
		{
			x = axes[2];
		}
		else
		{
			x = 0;
		}
		float y = 0;
		if (axes[5] > 0.2 || axes[5] < -0.2f)
		{
			y = axes[5];
		}
		else
		{
			y = 0;
		}

		return { x, -y };
	}
	bool GamePad::leftTrigger()
	{
		return axes[3] > -1;
	}
	bool GamePad::rightTrigger()
	{
		return axes[4] > -1;
	}
	bool GamePad::aButton()
	{
		return buttons[1] == GLFW_PRESS;
	}
	bool GamePad::bButton()
	{
		return buttons[2] == GLFW_PRESS;
	}

	/**
	* Xボタンの取得
	*/
	bool GamePad::xButton()
	{
		return buttons[0] == GLFW_PRESS;
	}

	/**
	* Yボタンの取得
	*/
	bool GamePad::yButton()
	{
		return buttons[3] == GLFW_PRESS;
	}

	/**
	* △ボタンの取得
	*/
	bool GamePad::triangleButton()
	{
		return yButton();
	}

	/**
	* □ボタンの取得
	*/
	bool GamePad::squareButton()
	{
		return xButton();
	}

	/**
	* 〇ボタンの取得
	*/
	bool GamePad::circleButton()
	{
		return bButton();
	}

	/**
	* ×ボタンの取得
	*/
	bool GamePad::crossButton()
	{
		return aButton();
	}
}