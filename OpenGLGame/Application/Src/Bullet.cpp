/**
* @file Bullet.cpp
*/
#include "Bullet.h"
#include "BaseMs.h"

/**
* �������Ɏ��s 
*/
void Bullet::Awake()
{
	auto rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->isGravity = false;
	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->isTrigger = true;
}

void Bullet::Start()
{
	Destroy(OwnerObject(), 3);
}

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
		GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation, targetRotation, rotationSpeed * Time::DeltaTime());

		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
}


void Bullet::OnTriggerEnter(const CollisionPtr other)
{
	auto ms = other->GetGameObject()->GetComponent<BaseMs>();
	if (ms)
	{
		// �_���[�W��^����
		ms->Damage(damage);
	}

	// ���g���폜
	Destroy(OwnerObject());
}
