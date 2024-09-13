/**
* @file HyumanControl.h
*/
#include "HyumanControl.h"
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"

#include "BaseMs.h"

/**
* Updateが始まる前に一度実行
*/
void HyumanControl::Start()
{
	Initialize();
}

/**
* 毎フレーム実行
*/
void HyumanControl::Update()
{
	// スタート合図が出ていければ何もしない
	if (!IsStart())
	{
		return;
	}

	GameInputUpdate();

	// 破壊されていなければ
	if (!myMs->IsDestroy())
	{
		myMs->SetDistance(GetDistance());
		TargetUpdate();
	}
}

/**
* 機体の操作を更新
*/
void HyumanControl::GameInputUpdate()
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
