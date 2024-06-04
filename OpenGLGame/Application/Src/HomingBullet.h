/**
* @file HomingBullet.h
*/
#ifndef HOMINGBULLET_H_INCLUDED
#define HOMINGBULLET_H_INCLUDED
#include "BaseBullet.h"


// 弾の基底クラス
class HomingBullet : public BaseBullet
{
public:

	// コンストラクタ・デストラクタ
	HomingBullet() = default;
	virtual ~HomingBullet() = default;

	/**
	* ターゲットを設定
	*
	* @param targetMs ターゲット機体
	*/
	void SetTargetMs(BaseMs* targetMs);

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update()override;

public:

	// ホーミング力
	float homingSpeed = 0;

	// ホーミングの有無
	bool isHoming = true;

private:

	// ターゲットMs
	BaseMs* targetMs = nullptr;

	Vector3 basePos = Vector3::zero;
};

#endif // !HOMINGBULLET_H_INCLUDED
