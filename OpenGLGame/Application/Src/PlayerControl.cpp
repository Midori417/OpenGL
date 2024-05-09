/**
* @file Player.cpp
*/
#include "PlayerControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"

/**
* �ŏ��Ɏ��s
*/
void PlayerControl::Start()
{
	// �J�����ɐݒ�
	lookOnCamera->playerMs = myMs->GetTransform().get();
	lookOnCamera->SelectTarget(otherOwner->myMs->GetTransform().get());
}

void PlayerControl::Update()
{
	myMs->Move(Vector2::up);
}

void PlayerControl::LateUpdate()
{
}
