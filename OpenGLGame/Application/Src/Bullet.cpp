/**
* @file Bullet.cpp
*/
#include "Bullet.h"
#include "BaseMs.h"
#include "DamageInfo.h"

/**
* �������Ɏ��s 
*/
void Bullet::Awake()
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
void Bullet::Start()
{
	// �������Ă���3�b��ɍ폜
	Destroy(OwnerObject(), 3);
}

/**
* ���t���[�����s
*/
void Bullet::Update()
{
	if (!targetMS || !isHoming)
	{
		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
	else
	{

		// �����x�N�g�����v�Z
		Vector3 direction = (targetMS->GetTransform()->position - GetTransform()->position);

		// �ڕW�̉�]���v�Z
		Quaternion targetRotation = Quaternion::LookRotation(direction);

		// �~�T�C���̉�]��ڕW�̉�]�ɋ߂Â���
		GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation, targetRotation, Mathf::Clamp01(rotationSpeed * Time::DeltaTime()));

		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
}

/**
* ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
*/
void Bullet::OnTriggerEnter(const CollisionPtr other)
{
	// �G�ꂽ�I�u�W�F�N�g�̃^�O��Bullet�Ȃ牽�����Ȃ�
	if (other->GetGameObject()->tag == "Bullet")
	{
		return;
	}

	auto ms = other->GetGameObject()->GetComponent<BaseMs>();
	if (ms)
	{
		// �_���[�W�����쐬
		DamageInfo damageInfo;
		damageInfo.damage = damage;
		damageInfo.direction = GetTransform()->position;
		damageInfo.downPower = downPower;

		// �_���[�W��^����
		ms->Damage(damageInfo);
	}

	// ���g���폜
	Destroy(OwnerObject());
}
