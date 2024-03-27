/**
* @file MagunamBullet.h
*/
#ifndef MAGUNAMBULLET_H_INCLUDED
#define MAGUNAMBULLET_H_INCLUDED
#include "FGEngineSub.h"
using namespace FGEngine;

class MagunamBullet :public MonoBehaviour
{
public:

	// === コンストラクタ・デストラクタ === //
	MagunamBullet() = default;
	virtual ~MagunamBullet() = default;

	// === Component基本イベント === //
	virtual void Awake() override;
	virtual void Update() override;
	virtual void OnCollisionEnter(const CollisionPtr collision) override;

	/**
	* ターゲットの設定
	* 
	* @param target ターゲット
	*/
	void SetTargetTrs(Transform* target)
	{
		targetTrs = target;
	}

	/**
	* ホーミングの設定
	* 
	* @param value trueホーミングする:falaseホーミング市内
	*/
	void SetHoming(bool value)
	{
		isHoming = value;
	}

	void SetTeum(int value)
	{
		teum = value;
	}

private:

	Transform* targetTrs = nullptr;
	float speed = 70;			// 速度
	float rotationSpeed = 0.05f;// 旋回速度
	float homingRate = 0.1f;		// 誘導率
	float destoryTimer = 10;	// 消滅時間
	bool isHoming = true;		// 誘導するか
	float atk = 70;				// 攻撃力
	int teum = -1;
};

#endif // !MAGUNAMBULLET_H_INCLUDED
