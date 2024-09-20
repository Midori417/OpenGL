/**
* @file HumanPilot.cpp
*/
#include "HumanPilot.h"
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"

#include "../GameInput.h"

/**
* �ŏ��Ɏ��s
*/
void HumanPilot::Start()
{
	Initialize();
}

/**
* ���t���[�����s
*/
void HumanPilot::Update()
{
	GameInputUpdate();
}

/**
* �Q�[�����͂��X�V
*/
void HumanPilot::GameInputUpdate()
{
	// �Q�[������
	gameInput->moveAxis = Vector2(InputManager::GetAxis(Axis::Horizontal), InputManager::GetAxis(Axis::Vertical));
	gameInput->jumpBtn = InputKey::GetKey(KeyCode::Space);
	gameInput->dashBtn = InputKey::GetKey(KeyCode::LeftShift);
	gameInput->stepBtn = InputKey::GetKey(KeyCode::LeftControl);
	gameInput->action1Btn = InputMouse::GetMouseButton(MouseButton::LeftButton);
	gameInput->action2Btn = InputKey::GetKey(KeyCode::E);
	gameInput->action3Btn = InputMouse::GetMouseButton(MouseButton::RightButton);
	gameInput->targetChangeBtn = InputMouse::GetMouseButtonDown(MouseButton::CenterButton);
}