/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"

/**
* HP���擾
*/
int BaseMs::GetHP() const
{
	return static_cast<int>(hp);
}

/**
* HP���擾(0�`1)
*/
float BaseMs::GetHP01()
{
	return Mathf::Clamp01((hpMax - (hpMax - hp)) / hpMax);
}

/**
* �G�l���M�[�c�ʂ̎擾(0�`1)
*/
float BaseMs::GetBoostEnergy() const
{
	return Mathf::Clamp01((boostEnergyMax - (boostEnergyMax - boostEnergy)) / boostEnergyMax);
}

/**
* �@�̃R�X�g���擾
*/
int BaseMs::GetCost() const
{
	return cost;
}

/**
* ���S���擾
*/
bool BaseMs::IsDeath() const
{
	return isDeath;
}

/**
* �G�Ƃ̋�����ݒ�
* 
* @param distance �G�Ƃ̋���
*/
void BaseMs::SetDistance(float distance)
{
	this->distance = distance;
}

/**
* �G�Ƃ̋������擾
*/
float BaseMs::GetDistance() const
{
	return distance;
}

/**
* �J�����̃g�����X�t�H�[����ݒ�
*/
void BaseMs::SetCamera(Transform* camera)
{
	this->cameraTrasform = camera;
}

/**
* �J�����̃g�����X�t�H�[�����擾
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

