/**
* @file DamageInfo.h
*/
#ifndef DAMAGEINFO_H_INCLUDED
#define DAMAGEINFO_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* ダメージ情報
*/
struct DamageInfo
{
	// 与えるダメージ
	float damage = 0;

	// 与えるダウン値
	float downPower = 0;

	// ダメージの方向
	Vector3 direction = Vector3::zero;
};

#endif // !DAMAGEINFO_H_INCLUDED
