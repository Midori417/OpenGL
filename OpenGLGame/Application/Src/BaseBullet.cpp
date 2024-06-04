/**
* @file BaseBullet.cpp
*/
#include "BaseBullet.h"
#include "DamageInfo.h"
#include "BaseMs.h"


/**
* �������Ɏ��s
*/
void BaseBullet::Awake()
{
	auto rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->isGravity = false;
	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = colllider.radius;
	col->ceneter = colllider.ceneter;
	col->isTrigger = true;
	OwnerObject()->tag = "Bullet";
}

/**
* ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
*/
void BaseBullet::OnTriggerEnter(const CollisionPtr other)
{
	auto obj = other->GetGameObject();

	// �G�ꂽ�I�u�W�F�N�g�̃^�O��Bullet�Ȃ牽�����Ȃ�
	if (obj->tag == "Bullet")
	{
		return;
	}
	// �ǂƒn�ʂȂ�e��j��
	if (obj->tag == "Ground" || obj->tag == "Wall")
	{
		// ���g���폜
		Destroy(OwnerObject());
		return;
	}

	// �^�O��MS
	if (obj->tag == "Ms")
	{
		auto ms = obj->GetComponent<BaseMs>();

		// Ms������Ή������Ȃ�
		if (ms->IsDeath())
		{
			return;
		}

		// �_���[�W�����쐬
		DamageInfo damageInfo;
		damageInfo.damage = damage;
		damageInfo.direction = Vector3(GetTransform()->position - obj->GetTransform()->position).Normalized();
		damageInfo.downPower = downPower;

		// �_���[�W��^����
		ms->Damage(damageInfo);

		// ���g���폜
		Destroy(OwnerObject());
	}

}