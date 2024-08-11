/**
* @file BaseSlash.cpp
*/
#include "BaseSlash.h"
#include "DamageInfo.h"
#include "BaseMs.h"

/**
* �������Ɏ��s
*/
void BaseSlash::Awake()
{
	auto rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->isGravity = false;
	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = colllider.radius;
	col->ceneter = colllider.ceneter;
	col->isTrigger = true;
	audioSource = OwnerObject()->AddComponent<AudioSource>();
	audioSource->SetSoundFilename(filenameSE);
	audioSource->is3DSound = true;
	OwnerObject()->tag = "Slash";
}

/**
* �ŏ��Ɏ��s
*/
void BaseSlash::Start()
{
	GetTransform()->scale = Vector3(3);

	Destroy(OwnerObject(), destoryTime);
}

/**
* ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
*/
void BaseSlash::OnTriggerEnter(const CollisionPtr other)
{
	auto obj = other->GetGameObject();

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
		damageInfo.direction = Vector3::Normalize(GetTransform()->position - obj->GetTransform()->position);
		damageInfo.downPower = downPower;

		audioSource->Play();

		// �_���[�W��^����
		ms->Damage(damageInfo);

		// ���g���폜
		Destroy(OwnerObject());
	}

	// �ǂƒn�ʂȂ�e��j��
	if (obj->tag == "Ground" || obj->tag == "Wall")
	{
		// ���g���폜
		Destroy(OwnerObject());
		return;
	}

}