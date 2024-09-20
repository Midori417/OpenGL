/**
* @file LookOnCamera.cpp
*/
#include "LookOnCamera.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Math/Mathf.h"
#include "FGEngine/Other/Time.h"

/**
* ロックオンカメラの挙動
*/
void LookOnCamera::LookCamera(Transform* target, Transform* myMs)
{
	// 自身とターゲットのMSの位置を取得
	Vector3 playerMsPos = myMs->position;

	Vector3 targetMsPos = target ? target->position : Vector3::zero;

	// ターゲットへのベクトル
	Vector3 targetVector = targetMsPos - playerMsPos;

	// ターゲットへのベクトルを前方とするクォータニオン
	Quaternion targetRotation = Quaternion::LookRotation(targetVector);

	// 距離を求める
	float distance = Vector3::Distance(targetMsPos, playerMsPos);

	// 高さを調整
	float posY = offsetMaxPos.y * (1 - (distance / offsetMaxPos.y));

	// オフセット位置を補正
	Vector3 offsetPos(
		0.0f,
		Mathf::Clamp(posY, offsetMinPos.y, offsetMaxPos.y),
		Mathf::Clamp(distance, offsetMinPos.z, offsetMaxPos.z)
	);

	// 位置と回転
	Vector3 position = Vector3::Lerp(GetTransform()->position, playerMsPos + targetRotation * offsetPos, 1);
	Quaternion rotation = Quaternion::LookRotation(targetMsPos - position);

	// 位置と回転を設定
	GetTransform()->SetPositionAndRotation(position, rotation);
}