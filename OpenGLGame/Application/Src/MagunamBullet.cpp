/**
* @file MagunamBullet.cpp
*/
#include "MagunamBullet.h"
#include "BaseMS.h"

/**
*　生成イベント
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
* 更新イベント
*/
void MagunamBullet::Update()
{
	if (!targetTrs || !isHoming)
	{
		transform->position += transform->forward() * speed * Time::deltaTime();

	}
	else
	{
		// 方向ベクトルを計算
		Vector3 direction = (targetTrs->position - transform->position);
		direction.Normalize();

		// 誘導具合を考慮した方向ベクトルの計算
		Vector3 disiredDirection = Vector3::Lerp(transform->forward(), direction, homingRate);
		disiredDirection.Normalize();

		// 回転
		Quaternion toRotation = Quaternion::LookRotation(disiredDirection);
		transform->rotation = Quaternion::Slerp(transform->rotation, toRotation, rotationSpeed);

		transform->position += transform->forward() * speed * Time::deltaTime();
	}
	// 削除時間
	destoryTimer -= Time::deltaTime();
	if (destoryTimer <= 0)
	{
		GetGameObject()->Destory();
	}
}

/**
* 衝突イベント
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
