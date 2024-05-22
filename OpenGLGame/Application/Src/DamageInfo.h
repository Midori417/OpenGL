/**
* @file DamageInfo.h
*/
#ifndef DAMAGEINFO_H_INCLUDED
#define DAMAGEINFO_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* �_���[�W���
*/
struct DamageInfo
{
	// �^����_���[�W
	float damage = 0;

	// �^����_�E���l
	float downPower = 0;

	// �_���[�W�̕���
	Vector3 direction = Vector3::zero;
};

#endif // !DAMAGEINFO_H_INCLUDED
