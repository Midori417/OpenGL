/**
* @file LookOnCamera.cpp
*/
#include "LookOnCamera.h"

void LookOnCamera::Start()
{
}

/**
* 毎フレーム実行(Updateより後)
*/
void LookOnCamera::LateUpdate()
{
	PositionCamera();
}

/**
* ターゲットを設定
*/
void LookOnCamera::SelectTarget(Transform* target)
{
	currentTarget = target;
}

/**
* カメラの位置を調整
*/
void LookOnCamera::PositionCamera()
{
	// とりつくMSがなければ何もしない
	if (!playerMs)
	{
		return;
	}

	// ターゲットが未設定ならロックオンカメラにしない
	if (!currentTarget)
	{
		GetTransform()->position = playerMs->position + cameraOffset;
		GetTransform()->LookAt(playerMs);
	}
	else
	{
		Vector3 playerMsPos = playerMs->position;
		// ターゲットへのベクトル
		Vector3 targetVector = currentTarget->position - playerMsPos;

		// ターゲットへのベクトルを前方とするクォータニオン
		Quaternion targetRotation = Quaternion::LookRotation(targetVector);

		// 位置と回転
		Vector3 position = playerMsPos + targetRotation * cameraOffset;
		Quaternion rotation = Quaternion::LookRotation(currentTarget->position - position);

		// 位置と回転をsってい
		GetTransform()->SetPositionAndRotation(position, rotation);
	}
}
