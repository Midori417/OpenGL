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
        // �^�[�Q�b�g�ւ̃x�N�g��
        targetVector = targetTrs->position - myMsPos;
    }
    else
    {
        targetVector = Vector3::zero;
    }
    // �^�[�Q�b�g�ւ̃x�N�g����O���Ƃ���N�H�[�^�j�I��
    Quaternion targetRotation = targetVector != Vector3::zero ? Quaternion::LookRotation(targetVector) : transform->rotation;

    // ���������߂�
    float distance = Vector3::Distance(targetTrs->position, myMsPos);
    float y = offsetNearPos.y * (1 - (distance / offsetNearPos.y));

    Vector3 offsetPos(
        0.0f,
        Mathf::Clamp(y, offsetFarPos.y, offsetNearPos.y),
        Mathf::Clamp(distance, offsetNearPos.z, offsetFarPos.z)
    );

    // �ʒu�Ɖ�]
    Vector3 position = myMsPos + targetRotation * offsetPos;
    Quaternion rotation = Quaternion::LookRotation(targetTrs->position - position);

    // �ʒu�Ɖ�]��ݒ�
    transform->SetPositionAndRotation(position, rotation);
}
