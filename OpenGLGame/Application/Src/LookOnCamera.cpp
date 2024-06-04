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
* ���t���[�����s(Update����)
*/
void LookOnCamera::LateUpdate()
{
	if (isStart)
	{
		PositionCamera();
	}
	else
	{
		// ���g�ƃ^�[�Q�b�g��MS�̈ʒu���擾
		Vector3 playerMsPos = myMs->position;
		Vector3 targetMsPos = targetMs->position;

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
		Vector3 position = Vector3::Lerp(GetTransform()->position, playerMsPos + targetRotation * offsetPos, Time::DeltaTime());
		Quaternion rotation = Quaternion::LookRotation(targetMsPos - position);


		// �ʒu�Ɖ�]��ݒ�
		GetTransform()->SetPositionAndRotation(position, rotation);
	}
}

/**
* �^�[�Q�b�g��ݒ�
*
* @param target �^�[�Q�b�g��Trs
*/
void LookOnCamera::SelectTarget(Transform* targetMs)
{
	this->targetMs = targetMs;
}

/**
* �Ƃ��MS�̃g�����X�t�H�[����ݒ�
*
* @param msTrs �Ƃ��Ms��Trs
*/
void LookOnCamera::SetMsTransform(Transform* myMs)
{
	this->myMs = myMs;
}

/**
* �J�����̈ʒu�𒲐�
*/
void LookOnCamera::PositionCamera()
{
	// �Ƃ��MS���Ȃ���Ή������Ȃ�
	if (!myMs)
	{
		return;
	}

	// �^�[�Q�b�g�����ݒ�Ȃ烍�b�N�I���J�����ɂ��Ȃ�
	if (!targetMs)
	{
		GetTransform()->position = myMs->position + offsetMaxPos;
		GetTransform()->LookAt(myMs);
	}
	else
	{
		// ���g�ƃ^�[�Q�b�g��MS�̈ʒu���擾
		Vector3 playerMsPos = myMs->position;
		Vector3 targetMsPos = targetMs->position;

		// �^�[�Q�b�g�ւ̃x�N�g��
		Vector3 targetVector = targetMsPos - playerMsPos;

		// �^�[�Q�b�g�ւ̃x�N�g����O���Ƃ���N�H�[�^�j�I��
		Quaternion targetRotation = Quaternion::LookRotation(targetVector);


		// ���������߂�
		float distance = Vector3::Distance(targetMsPos, playerMsPos);

		// ����������
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


		// �ʒu�Ɖ�]��s���Ă�
		GetTransform()->SetPositionAndRotation(position, rotation);
	}
}
