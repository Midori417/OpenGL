/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"

/**
* チームを取得
*/
Teum BaseMs::GetTeum() const
{
	return teum;
}

/**
* HPを取得
*/
int BaseMs::GetHP() const
{
	return hp;
}

/**
* エネルギーの残量(0～1)を取得
*/
float BaseMs::GetBoostPower() const
{
	return Mathf::Clamp01((boostPowerMax - boostPower) / (boostPowerMax));
}

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
* 敵との距離を取得
*/
float BaseMs::GetDistance() const
{
	return distance;
}

/**
* カメラのトランスフォームを設定
*/
void BaseMs::SetCamera(Transform* camera)
{
	this->cameraTrasform = camera;
}

/**
* カメラのトランスフォームを取得
*/
Transform* BaseMs::GetCameraTransform() const
{
	return cameraTrasform;
}

void BaseMs::SetTargetMS(BaseMs* baseMS)
{
	this->targetMs = baseMS;
}

BaseMs* BaseMs::GetTargetMs() const
{
	return targetMs;
}
