/**
* @file Player.cpp
*/
#include "PlayerControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
using namespace FGEngine::InputSystem;

/**
* 最初に実行
*/
void PlayerControl::Start()
{
	// カメラに設定
	lookOnCamera->playerMs = myMs->GetTransform().get();
	lookOnCamera->SelectTarget(otherOwner->myMs->GetTransform().get());
	
	// プレイヤーにカメラ設定
	myMs->SetCamera(lookOnCamera->GetTransform().get());
}

void PlayerControl::Update()
{

	// 移動
	Vector2 moveAxis = Vector2(InputManager::GetAxis(Axis::Horizontal), InputManager::GetAxis(Axis::Vertical));
	myMs->Move(moveAxis);

	// ジャンプ
	bool jumpKey = InputKey::GetKey(KeyCode::Space);
	myMs->Jump(jumpKey);

	// ダッシュ
	bool dashKey = InputKey::GetKey(KeyCode::LeftShift);
	myMs->Dash(dashKey, moveAxis);
}

void PlayerControl::LateUpdate()
{
}
