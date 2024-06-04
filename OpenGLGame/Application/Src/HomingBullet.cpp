/**
* @file HomingBullet.cpp
*/
#include "HomingBullet.h"
#include "BaseMs.h"
#include "DamageInfo.h"

/**
* ターゲットを設定
*
* @param targetMs ターゲット機体
*/
void HomingBullet::SetTargetMs(BaseMs* targetMs)
{
	this->targetMs = targetMs;
}


/**
* 最初に実行
*/
void HomingBullet::Start()
{
	// destoryTime後に削除
	Destroy(OwnerObject(), destroyTime);

	// 撃った位置を設定
	basePos = GetTransform()->position;
}

/**
* 毎フレーム実行
*/
void HomingBullet::Update()
{
	if (!targetMs || !isHoming)
	{
		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
	else
	{
		// 方向ベクトルを計算
		Vector3 direction = (targetMs->GetTransform()->position - basePos);

		// 目標の回転を計算
		Quaternion targetRotation = Quaternion::LookRotation(direction);

		// ミサイルの回転を目標の回転に近づける
		GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation, targetRotation, homingSpeed);

		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
}

