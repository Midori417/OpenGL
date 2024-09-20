/**
* @file LookOnCamera.cpp
*/
#include "LookOnCamera.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Math/Mathf.h"
#include "FGEngine/Other/Time.h"

/**
* ���b�N�I���J�����̋���
*/
void LookOnCamera::LookCamera(Transform* target, Transform* myMs)
{
	// ���g�ƃ^�[�Q�b�g��MS�̈ʒu���擾
	Vector3 playerMsPos = myMs->position;

	Vector3 targetMsPos = target ? target->position : Vector3::zero;

	// �^�[�Q�b�g�ւ̃x�N�g��
	Vector3 targetVector = targetMsPos - playerMsPos;

	// �^�[�Q�b�g�ւ̃x�N�g����O���Ƃ���N�H�[�^�j�I��
	Quaternion targetRotation = Quaternion::LookRotation(targetVector);

	// ���������߂�
	float distance = Vector3::Distance(targetMsPos, playerMsPos);

	// �����𒲐�
	float posY = offsetMaxPos.y * (1 - (distance / offsetMaxPos.y));

	// �I�t�Z�b�g�ʒu��␳
	Vector3 offsetPos(
		0.0f,
		Mathf::Clamp(posY, offsetMinPos.y, offsetMaxPos.y),
		Mathf::Clamp(distance, offsetMinPos.z, offsetMaxPos.z)
	);

	// �ʒu�Ɖ�]
	Vector3 position = Vector3::Lerp(GetTransform()->position, playerMsPos + targetRotation * offsetPos, 1);
	Quaternion rotation = Quaternion::LookRotation(targetMsPos - position);

	// �ʒu�Ɖ�]��ݒ�
	GetTransform()->SetPositionAndRotation(position, rotation);
}