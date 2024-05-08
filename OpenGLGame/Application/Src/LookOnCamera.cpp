/**
* @file LookOnCamera.cpp
*/
#include "LookOnCamera.h"

void LookOnCamera::Start()
{
}

/**
* ���t���[�����s(Update����)
*/
void LookOnCamera::LateUpdate()
{
	PositionCamera();
}

/**
* �^�[�Q�b�g��ݒ�
*/
void LookOnCamera::SelectTarget(Transform* target)
{
	currentTarget = target;
}

/**
* �J�����̈ʒu�𒲐�
*/
void LookOnCamera::PositionCamera()
{
	// �Ƃ��MS���Ȃ���Ή������Ȃ�
	if (!playerMs)
	{
		return;
	}

	// �^�[�Q�b�g�����ݒ�Ȃ烍�b�N�I���J�����ɂ��Ȃ�
	if (!currentTarget)
	{
		GetTransform()->position = playerMs->position + cameraOffset;
		GetTransform()->LookAt(playerMs);
	}
	else
	{
		Vector3 playerMsPos = playerMs->position;
		// �^�[�Q�b�g�ւ̃x�N�g��
		Vector3 targetVector = currentTarget->position - playerMsPos;

		// �^�[�Q�b�g�ւ̃x�N�g����O���Ƃ���N�H�[�^�j�I��
		Quaternion targetRotation = Quaternion::LookRotation(targetVector);

		// �ʒu�Ɖ�]
		Vector3 position = playerMsPos + targetRotation * cameraOffset;
		Quaternion rotation = Quaternion::LookRotation(currentTarget->position - position);

		// �ʒu�Ɖ�]��s���Ă�
		GetTransform()->SetPositionAndRotation(position, rotation);
	}
}
