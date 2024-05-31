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
* �������Ɏ��s
*/
void HomingBullet::Awake()
{
	auto rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->isGravity = false;
	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->isTrigger = true;
	OwnerObject()->tag = "Bullet";
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

/**
* ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
*/
void HomingBullet::OnTriggerEnter(const CollisionPtr other)
{
	// �G�ꂽ�I�u�W�F�N�g�̃^�O��Bullet�Ȃ牽�����Ȃ�
	if (other->GetGameObject()->tag == "Bullet")
	{
		return;
	}

	auto ms = other->GetGameObject()->GetComponent<BaseMs>();
	if (ms)
	{
		if (ms->IsDeath())
		{
			return;
		}
		// �_���[�W�����쐬
		DamageInfo damageInfo;
		damageInfo.damage = damage;
		damageInfo.direction = Vector3(GetTransform()->position - other->GetTransform()->position).Normalized();
		damageInfo.downPower = downPower;

		// �_���[�W��^����
		ms->Damage(damageInfo);
	}

	// ���g���폜
	Destroy(OwnerObject());
}