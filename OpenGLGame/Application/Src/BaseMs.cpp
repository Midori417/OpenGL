/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"

/**
* ƒ`[ƒ€‚ðŽæ“¾
*/
Teum BaseMs::GetTeum() const
{
	return teum;
}

/**
* HP‚ðŽæ“¾
*/
int BaseMs::GetHP() const
{
	return hp;
}

/**
* ƒGƒlƒ‹ƒM[‚ÌŽc—Ê(0`1)‚ðŽæ“¾
*/
float BaseMs::GetBoostPower() const
{
	return Mathf::Clamp01((boostPowerMax - boostPower) / (boostPowerMax));
}

/**
* “G‚Æ‚Ì‹——£‚ðÝ’è
* 
* @param distance “G‚Æ‚Ì‹——£
*/
void BaseMs::SetDistance(float distance)
{
	this->distance = distance;
}

/**
* “G‚Æ‚Ì‹——£‚ðŽæ“¾
*/
float BaseMs::GetDistance() const
{
	return distance;
}
