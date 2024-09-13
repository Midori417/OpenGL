/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Rigidbody.h"

/**
* 敵との距離を設定
*
* @param distance 敵との距離
*/
void BaseMs::SetDistance(float distance)
{
	this->distance = distance;
}

/**
* カメラのトランスフォームを設定
*/
void BaseMs::SetCamera(Transform* camera)
{
	this->trsCamera = camera;
}

/**
* ターゲットMSの設定
*/
void BaseMs::SetTargetMS(BaseMs* baseMS)
{
	this->targetMs = baseMS;
}

/**
* 機体入力を設定する
*/
void BaseMs::SetGameInput(GameInput* gameInput)
{
	this->gameInput = gameInput;
}

/**
* 機体が破壊されているか取得
*/
bool BaseMs::IsDestroy() const
{
	// すでに死亡していたら何もしない
	if (isDestroy)
	{
		return true;
	}

	// HPがなければ死亡状態にする
	if (paramater.hp <= 0 || GetTransform()->position.y < -10)
	{
		// 描画しない
		meshRender->enabled = false;
		rb->velocity = Vector3::zero;
		return true;
	}
	return false;
}

/**
* カメラのトランスフォームを取得
*/
Transform* BaseMs::GetCameraTransform() const
{
	return trsCamera;
}

/**
* 破壊チェック
*/
bool BaseMs::DestroyCheck() const
{
	return false;
}

/**
* 破壊する
*/
void BaseMs::Destroy()
{
	isDestroy = true;
}
