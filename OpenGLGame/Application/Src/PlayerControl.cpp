/**
* @file Player.cpp
*/
#include "PlayerControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
using namespace FGEngine::InputSystem;

/**
* �ŏ��Ɏ��s
*/
void PlayerControl::Start()
{
	// �J�����ɐݒ�
	lookOnCamera->playerMs = myMs->GetTransform().get();
	lookOnCamera->SelectTarget(otherOwner->myMs->GetTransform().get());
	
	// �v���C���[�ɃJ�����ݒ�
	myMs->SetCamera(lookOnCamera->GetTransform().get());
}

void PlayerControl::Update()
{

	// �ړ�
	Vector2 moveAxis = Vector2(InputManager::GetAxis(Axis::Horizontal), InputManager::GetAxis(Axis::Vertical));
	myMs->Move(moveAxis);

	// �W�����v
	bool jumpKey = InputKey::GetKey(KeyCode::Space);
	myMs->Jump(jumpKey);

	// �_�b�V��
	bool dashKey = InputKey::GetKey(KeyCode::LeftShift);
	myMs->Dash(dashKey, moveAxis);
}

void PlayerControl::LateUpdate()
{
}
