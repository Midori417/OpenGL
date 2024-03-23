/**
* @file CameraMove.h
*/
#include "CameraMove.h"

void CameraMove::LateUpdate()
{
    if (!myMsTrs)
    {
        return;
    }
    Vector3 myMsPos = myMsTrs->position;

    Vector3 targetVector(0);
    if (targetTrs)
    {
        // ターゲットへのベクトル
        targetVector = targetTrs->position - myMsPos;
    }
    else
    {
        targetVector = Vector3::zero;
    }
    // ターゲットへのベクトルを前方とするクォータニオン
    Quaternion targetRotation = targetVector != Vector3::zero ? Quaternion::LookRotation(targetVector) : transform->rotation;

    // 距離を求める
    float distance = Vector3::Distance(targetTrs->position, myMsPos);
    float y = offsetNearPos.y * (1 - (distance / offsetNearPos.y));

    Vector3 offsetPos(
        0.0f,
        Mathf::Clamp(y, offsetFarPos.y, offsetNearPos.y),
        Mathf::Clamp(distance, offsetNearPos.z, offsetFarPos.z)
    );

    // 位置と回転
    Vector3 position = myMsPos + targetRotation * offsetPos;
    Quaternion rotation = Quaternion::LookRotation(targetTrs->position - position);

    // 位置と回転を設定
    transform->SetPositionAndRotation(position, rotation);
}
