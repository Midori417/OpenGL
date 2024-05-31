/**
* @file BaseBullet.h
*/
#ifndef BASEBULLET_H_INCLUDED
#define BASEBULLET_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* 弾の基底クラス
*/
class BaseBullet : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	BaseBullet() = default;
	virtual ~BaseBullet() = default;

public:

	// 弾の速度
	float speed = 0;

	// 与えるダメージ
	float damage = 0;

	// 与えるダウン値
	float downPower = 0;

	// 撃ってから消えるまでの時間
	float destroyTime = 5;
};


#endif // !BASEBULLET_H_INCLUDED
