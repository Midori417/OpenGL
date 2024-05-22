/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"

/**
* HPを取得
*/
int BaseMs::GetHP() const
{
	return static_cast<int>(hp);
}

/**
* HPを取得(0～1)
*/
float BaseMs::GetHP01()
{
	return Mathf::Clamp01((hpMax - (hpMax - hp)) / hpMax);
}

/**
* エネルギー残量の取得(0～1)
*/
float BaseMs::GetBoostEnergy() const
{
	return Mathf::Clamp01((boostEnergyMax - (boostEnergyMax - boostEnergy)) / boostEnergyMax);
}

/**
* 機体コストを取得
*/
int BaseMs::GetCost() const
{
	return cost;
}

/**
* 死亡か取得
*/
bool BaseMs::IsDeath() const
{
	return isDeath;
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

