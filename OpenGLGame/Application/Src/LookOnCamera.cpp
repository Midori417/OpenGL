/**
* @file LookOnCamera.cpp
*/
#include "LookOnCamera.h"

/**
* 
*/
void LookOnCamera::StartOk()
{
	isStart = true;
}

/**
* 毎フレーム実行(Updateより後)
*/
void LookOnCamera::LateUpdate()
{
	if (isStart)
	{
		PositionCamera();
	}
	else
	{
		// 自身とターゲットのMSの位置を取得
		Vector3 playerMsPos = myMs->position;
		Vector3 targetMsPos = targetMs->position;

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
		Vector3 position = Vector3::Lerp(GetTransform()->position, playerMsPos + targetRotation * offsetPos, Time::DeltaTime());
		Quaternion rotation = Quaternion::LookRotation(targetMsPos - position);


		// 位置と回転を設定
		GetTransform()->SetPositionAndRotation(position, rotation);
	}
}

/**
* ターゲットを設定
*
* @param target ターゲットのTrs
*/
void LookOnCamera::SelectTarget(Transform* targetMs)
{
	this->targetMs = targetMs;
}

/**
* とりつくMSのトランスフォームを設定
*
* @param msTrs とりつくMsのTrs
*/
void LookOnCamera::SetMsTransform(Transform* myMs)
{
	this->myMs = myMs;
}

/**
* カメラの位置を調整
*/
void LookOnCamera::PositionCamera()
{
	// とりつくMSがなければ何もしない
	if (!myMs)
	{
		return;
	}

	// ターゲットが未設定ならロックオンカメラにしない
	if (!targetMs)
	{
		GetTransform()->position = myMs->position + offsetMaxPos;
		GetTransform()->LookAt(myMs);
	}
	else
	{
		// 自身とターゲットのMSの位置を取得
		Vector3 playerMsPos = myMs->position;
		Vector3 targetMsPos = targetMs->position;

		// ターゲットへのベクトル
		Vector3 targetVector = targetMsPos - playerMsPos;

		// ターゲットへのベクトルを前方とするクォータニオン
		Quaternion targetRotation = Quaternion::LookRotation(targetVector);


		// 距離を求める
		float distance = Vector3::Distance(targetMsPos, playerMsPos);

		// 高さを招請
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


		// 位置と回転をsってい
		GetTransform()->SetPositionAndRotation(position, rotation);
	}
}
