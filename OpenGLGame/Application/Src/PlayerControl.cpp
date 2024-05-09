/**
* @file Player.cpp
*/
#include "PlayerControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"

/**
* Å‰‚ÉŽÀs
*/
void PlayerControl::Start()
{
	// ƒJƒƒ‰‚ÉÝ’è
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
