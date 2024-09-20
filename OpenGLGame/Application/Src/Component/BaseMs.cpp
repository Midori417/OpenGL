/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Animator.h"

/**
* 機体入力を設定
*/
void BaseMs::SetMsInput(const GameInputPtr& gameInput)
{
	msInput = gameInput;
}

/**
* カメラのトランスフォームを設定する
*/
void BaseMs::SetTrsCamera(const TransformPtr& camera)
{
	trsCamera = camera.get();
}

/**
* ターゲット機体を設定
*/
void BaseMs::SetTargetMs(const BaseMsPtr& targetMs)
{
	this->targetMs = targetMs.get();
}

/**
* カメラ正面を基準に移動方向を計算する
*/
Vector3 BaseMs::MoveForward(const Vector2& moveAxis)
{
	// カメラの方向から、X-Z単位ベクトル(正規化)を取得
	Vector3 cameraForward = Vector3::Normalize(GetTrsCamera()->Forward() * Vector3(1, 0, 1));
	Vector3 moveForward = cameraForward * moveAxis.y + GetTrsCamera()->Right() * moveAxis.x;

	return moveForward;
}

/**
* 共通コンポーネントの取得
*/
void BaseMs::ComponentGet()
{
	rb = OwnerObject()->AddComponent<Rigidbody>();
	renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	anim = OwnerObject()->AddComponent<Animator>();
}

/**
* カメラのトランスフォームを取得する
*/
Transform* BaseMs::GetTrsCamera() const
{
	return trsCamera;
}

/**
* ターゲット機体を取得
*/
BaseMs* BaseMs::GetTarget() const
{
	return targetMs;
}
