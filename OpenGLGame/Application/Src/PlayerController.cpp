/**
* @file PlayerController.cpp
*/
#include "PlayerController.h"

void PlayerController::Update()
{
	// �R���g���[�����ڑ����ꂢ�Ȃ����
	if (GamePad::GetGamePad() == nullptr)
	{
		inputAxis = Vector2(Input::GetAxis("Horizontal"), Input::GetAxis("Vertical"));
		jumpBtn = Input::GetKey(KeyCode::Space);
		shotBtn = Input::GetMouseButton(MouseButton::LeftButton);
		fightBtn = Input::GetMouseButton(MouseButton::RightButton);
	}
	else
	{
		GamePad* gamepad = GamePad::GetGamePad();
		inputAxis = Vector2(gamepad->leftStick().x, gamepad->leftStick().y);
		jumpBtn = gamepad->crossButton();
		shotBtn = gamepad->squareButton();
		fightBtn = gamepad->triangleButton();
	}

}
