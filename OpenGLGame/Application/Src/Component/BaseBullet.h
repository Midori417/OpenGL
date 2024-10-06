/**
* @file BaseBullet.h
*/
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

/**
* 弾の基底コンポーネント
*/
class BaseBullet : public GameEvent
{
protected:

	/**
	* デフォルトコンストラクタ
	*/
	BaseBullet() = default;

protected:

	// 与えるダメージ
	float damage = 0;

	// 速度
	float speed = 0;

	// 生成されてから消えるまでの時間
	float destroyTime = 0;
};