/**
* @file BaseSlash.cpp
*/
#include "BaseSlash.h"
#include "DamageInfo.h"
#include "BaseMs.h"

/**
* 生成時に実行
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
* 最初に実行
*/
void BaseSlash::Start()
{
	GetTransform()->scale = Vector3(3);

	Destroy(OwnerObject(), destoryTime);
}

/**
* 他のコリジョンに触れたときに実行
*/
void BaseSlash::OnTriggerEnter(const CollisionPtr other)
{
	auto obj = other->GetGameObject();

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

		audioSource->Play();

		// ダメージを与える
		ms->Damage(damageInfo);

		// 自身を削除
		Destroy(OwnerObject());
	}

	// 壁と地面なら弾を破壊
	if (obj->tag == "Ground" || obj->tag == "Wall")
	{
		// 自身を削除
		Destroy(OwnerObject());
		return;
	}

}