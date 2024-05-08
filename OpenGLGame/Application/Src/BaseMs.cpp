/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"

/**
* �`�[�����擾
*/
Teum BaseMs::GetTeum() const
{
	return teum;
}

/**
* HP���擾
*/
int BaseMs::GetHP() const
{
	return hp;
}

/**
* �G�l���M�[�̎c��(0�`1)���擾
*/
float BaseMs::GetBoostPower() const
{
	return Mathf::Clamp01((boostPowerMax - boostPower) / (boostPowerMax));
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
