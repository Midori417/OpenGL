/**
* @file HomingBullet.cpp
*/
#include "HomingBullet.h"
#include "BaseMs.h"
#include "DamageInfo.h"

/**
* �^�[�Q�b�g��ݒ�
*
* @param targetMs �^�[�Q�b�g�@��
*/
void HomingBullet::SetTargetMs(BaseMs* targetMs)
{
	this->targetMs = targetMs;
}


/**
* �ŏ��Ɏ��s
*/
void HomingBullet::Start()
{
	// destoryTime��ɍ폜
	Destroy(OwnerObject(), destroyTime);

	// �������ʒu��ݒ�
	basePos = GetTransform()->position;
}

/**
* ���t���[�����s
*/
void HomingBullet::Update()
{
	if (!targetMs || !isHoming)
	{
		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
	else
	{
		// �����x�N�g�����v�Z
		Vector3 direction = (targetMs->GetTransform()->position - basePos);

		// �ڕW�̉�]���v�Z
		Quaternion targetRotation = Quaternion::LookRotation(direction);

		// �~�T�C���̉�]��ڕW�̉�]�ɋ߂Â���
		GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation, targetRotation, homingSpeed);

		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
}

