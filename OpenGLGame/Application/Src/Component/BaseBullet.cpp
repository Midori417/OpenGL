/**
* @file BaseBullet.cpp
*/
#include "BaseBullet.h"
#include "DamageInfo.h"
#include "BaseMs.h"


/**
* 生成時に実行
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
* 他のコリジョンに触れたときに実行
*/
void BaseBullet::OnCollisionEnter(const CollisionPtr other)
{
	auto obj = other->GetGameObject();

	// 触れたオブジェクトのタグがBulletなら何もしない
	if (obj->tag == "Bullet")
	{
		return;
	}
	// 壁と地面なら弾を破壊
	if (obj->tag == "Ground" || obj->tag == "Wall" || obj->tag == "Bilding")
	{
		// 自身を削除
		OwnerObject()->Destroy();
		return;
	}

	// タグがMS
	if (obj->tag == "Ms")
	{
		auto ms = obj->GetComponent<BaseMs>();

		// Msがいれば何もしない
		if (ms->IsDeath())
		{
			return;
		}

		// ダメージ情報を作成
		DamageInfo damageInfo;
		damageInfo.damage = damage;
		damageInfo.direction = Vector3::Normalize(GetTransform()->position - obj->GetTransform()->position);
		damageInfo.downPower = downPower;

		// ダメージを与える
		ms->Damage(damageInfo);

		// 自身を削除
		OwnerObject()->Destroy();
	}

}