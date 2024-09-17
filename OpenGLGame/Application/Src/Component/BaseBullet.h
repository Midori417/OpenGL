/**
* @file BaseBullet.h
*/
#ifndef BASEBULLET_H_INCLUDED
#define BASEBULLET_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

// 先行宣言
class BaseMs;

/**
* 弾の基底クラス
*/
class BaseBullet : public GameEvent
{
public:

	// コンストラクタ・デストラクタ
	BaseBullet() = default;
	virtual ~BaseBullet() = default;

private:

	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

	/**
	* 生成時に実行
	*/
	virtual void Awake() override;

	/**
	* 他のコリジョンに触れたときに実行
	*/
	virtual void OnCollisionEnter(const CollisionPtr other) override;

public:

	// 弾の速度
	float speed = 0;

	// 与えるダメージ
	float damage = 0;

	// 与えるダウン値
	float downPower = 0;

	// 撃ってから消えるまでの時間
	float destroyTime = 5;

	struct Col
	{
		float radius = 1;
		Vector3 ceneter = Vector3::zero;
	};
	Col colllider;

};
#endif // !BASEBULLET_H_INCLUDED
