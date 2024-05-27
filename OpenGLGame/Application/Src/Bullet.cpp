/**
* @file Bullet.cpp
*/
#include "Bullet.h"
#include "BaseMs.h"
#include "DamageInfo.h"

/**
* 生成時に実行 
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
* 最初に実行
*/
void Bullet::Start()
{
	// 生成してから3秒後に削除
	Destroy(OwnerObject(), 3);

	basePos = GetTransform()->position;
}

/**
* 毎フレーム実行
*/
void Bullet::Update()
{
	if (!targetMS || !isHoming)
	{
		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
	else
	{

		// 方向ベクトルを計算
		Vector3 direction = (targetMS->GetTransform()->position - basePos);

		// 目標の回転を計算
		Quaternion targetRotation = Quaternion::LookRotation(direction);

		// ミサイルの回転を目標の回転に近づける
		GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation, targetRotation, rotationSpeed);

		GetTransform()->position += GetTransform()->Forward() * speed * Time::DeltaTime();
	}
}

/**
* 他のコリジョンに触れたときに実行
*/
void Bullet::OnTriggerEnter(const CollisionPtr other)
{
	// 触れたオブジェクトのタグがBulletなら何もしない
	if (other->GetGameObject()->tag == "Bullet")
	{
		return;
	}

	auto ms = other->GetGameObject()->GetComponent<BaseMs>();
	if (ms)
	{
		// ダメージ情報を作成
		DamageInfo damageInfo;
		damageInfo.damage = damage;
		damageInfo.direction = Vector3(GetTransform()->position - other->GetTransform()->position).Normalized();
		damageInfo.downPower = downPower;

		// ダメージを与える
		ms->Damage(damageInfo);
	}

	// 自身を削除
	Destroy(OwnerObject());
}
