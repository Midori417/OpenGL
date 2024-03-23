/**
* @file MagunamBullet.cpp
*/
#include "MagunamBullet.h"
#include "BaseMS.h"

/**
*�@�����C�x���g
*/
void MagunamBullet::Awake()
{
	auto engine = GetGameObject()->GetEngine();
	auto renderer = GetGameObject()->AddComponent<MeshRenderer>();
	renderer->mesh = engine->GetStaticMesh("Application/Res/Gundam/Model/MagunamBullet.obj");
	renderer->materials = CloneMaterialList(renderer->mesh);
	renderer->materials[0]->texBaseColor = engine->GetTexture("Application/Res/Gundam/Model/Bullet.tga");
	auto collder = GetGameObject()->AddComponent<SphereCollider>();
	collder->isTrigger = true;
}

/**
* �X�V�C�x���g
*/
void MagunamBullet::Update()
{
	if (!targetTrs || !isHoming)
	{
		transform->position += transform->forward() * speed * Time::deltaTime();

	}
	else
	{
		// �����x�N�g�����v�Z
		Vector3 direction = (targetTrs->position - transform->position);
		direction.Normalize();

		// �U������l�����������x�N�g���̌v�Z
		Vector3 disiredDirection = Vector3::Lerp(transform->forward(), direction, homingRate);
		disiredDirection.Normalize();

		// ��]
		Quaternion toRotation = Quaternion::LookRotation(disiredDirection);
		transform->rotation = Quaternion::Slerp(transform->rotation, toRotation, rotationSpeed);

		transform->position += transform->forward() * speed * Time::deltaTime();
	}
	// �폜����
	destoryTimer -= Time::deltaTime();
	if (destoryTimer <= 0)
	{
		GetGameObject()->Destory();
	}
}

/**
* �Փ˃C�x���g
*/
void MagunamBullet::OnCollision(const ComponentPtr& self, const ComponentPtr& other)
{
	auto otherMs = other->GetComponent<BaseMS>();
	if (otherMs)
	{
		if (otherMs->GetParameter().teum != teum)
		{
			otherMs->Damage(atk);
			GetGameObject()->Destory();
		}
	}
}
