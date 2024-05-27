/**
* @file Bullet.h
*/
#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

class BaseMs;

// 弾の基底クラス
class Bullet : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	Bullet() = default;
	virtual ~Bullet() = default;

private:

	/**
	* 生成時に実行
	*/
	virtual void Awake() override;

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update()override;

	// 他のコリジョンに触れたときに実行
	virtual void OnTriggerEnter(const CollisionPtr other) override;

public:

	// ターゲットMs
	BaseMs* targetMS = nullptr;

	float rotationSpeed = 0;

	// ホーミングの有無
	bool isHoming = true;

	// 弾の速度
	float speed = 0;

	// 与えるダメージ
	float damage = 0;

	// 与えるダウン値
	float downPower = 0;

	Vector3 basePos = Vector3::zero;
};


#endif // !RIFLEBULLET_H_INCLUDED
