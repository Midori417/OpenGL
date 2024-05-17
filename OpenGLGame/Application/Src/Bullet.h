/**
* @file Bullet.h
*/
#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

class BaseMs;

class Bullet : public MonoBehaviour
{
public:

	Bullet() = default;
	virtual ~Bullet() = default;

	virtual void Awake() override;

private:

	virtual void Start() override;

	virtual void Update()override;

	// 他のコリジョンに触れたときに実行
	virtual void OnTriggerEnter(const CollisionPtr other) override;

public:

	// ターゲットMs
	BaseMs* targetMS;

	float rotationSpeed = 0;

	// ホーミングの有無
	bool isHoming = true;

	// 弾の速度
	float speed = 0;

	// 与えるダメージ
	float damage = 0;
};


#endif // !RIFLEBULLET_H_INCLUDED
