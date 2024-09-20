/**
* @file HumanPilot.cpp
*/
#include "HumanPilot.h"
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"

#include "../GameInput.h"

/**
* 最初に実行
*/
void HumanPilot::Start()
{
	Initialize();
}

/**
* 毎フレーム実行
*/
void HumanPilot::Update()
{
	GameInputUpdate();
}

/**
* ゲーム入力を更新
*/
void HumanPilot::GameInputUpdate()
{
	// ゲーム入力
	gameInput->moveAxis = Vector2(InputManager::GetAxis(Axis::Horizontal), InputManager::GetAxis(Axis::Vertical));
	gameInput->jumpBtn = InputKey::GetKey(KeyCode::Space);
	gameInput->dashBtn = InputKey::GetKey(KeyCode::LeftShift);
	gameInput->stepBtn = InputKey::GetKey(KeyCode::LeftControl);
	gameInput->action1Btn = InputMouse::GetMouseButton(MouseButton::LeftButton);
	gameInput->action2Btn = InputKey::GetKey(KeyCode::E);
	gameInput->action3Btn = InputMouse::GetMouseButton(MouseButton::RightButton);
	gameInput->targetChangeBtn = InputMouse::GetMouseButtonDown(MouseButton::CenterButton);
}