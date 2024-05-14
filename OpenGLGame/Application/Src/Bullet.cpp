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
	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->isTrigger = true;
}

void Bullet::Start()
{
	//Destroy(OwnerObject(), 3);
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
		direction.Normalize();

		// 誘導具合を考慮した方向ベクトルの計算
		Vector3 disiredDirection = Vector3::Lerp(GetTransform()->Forward(), direction, homingPower);
		disiredDirection.Normalize();

		// 回転
		Quaternion toRotation = Quaternion::LookRotation(disiredDirection);
		GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation, toRotation, rotationSpeed);

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
