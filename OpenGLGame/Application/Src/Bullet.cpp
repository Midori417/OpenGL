/**
* @file Bullet.cpp
*/
#include "Bullet.h"
#include "BaseMs.h"

/**
* 生成時に実行 
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

		// 方向ベクトルを計算
		Vector3 direction = (targetMS->GetTransform()->position - GetTransform()->position);

		// 目標の回転を計算
		Quaternion targetRotation = Quaternion::LookRotation(direction);

		// ミサイルの回転を目標の回転に近づける
		GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation, targetRotation, rotationSpeed * Time::DeltaTime());

		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
}


void Bullet::OnTriggerEnter(const CollisionPtr other)
{
	auto ms = other->GetGameObject()->GetComponent<BaseMs>();
	if (ms)
	{
		// ダメージを与える
		ms->Damage(damage);
	}

	// 自身を削除
	Destroy(OwnerObject());
}
