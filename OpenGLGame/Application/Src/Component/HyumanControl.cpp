/**
* @file HyumanControl.h
*/
#include "HyumanControl.h"
#include "FGEngine/Input/InputManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Input/InputMouse.h"

#include "BaseMs.h"

/**
* Update���n�܂�O�Ɉ�x���s
*/
void HyumanControl::Start()
{
	Initialize();
}

/**
* ���t���[�����s
*/
void HyumanControl::Update()
{
	// �X�^�[�g���}���o�Ă�����Ή������Ȃ�
	if (!IsStart())
	{
		return;
	}

	GameInputUpdate();

	// �j�󂳂�Ă��Ȃ����
	if (!myMs->IsDestroy())
	{
		myMs->SetDistance(GetDistance());
		TargetUpdate();
	}
}

/**
* �@�̂̑�����X�V
*/
void HyumanControl::GameInputUpdate()
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
