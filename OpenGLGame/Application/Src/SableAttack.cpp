/**
* @file SableAttack.cpp
*/
#include "SableAttack.h"
#include "BaseMS.h"

void SableAttack::Awake()
{
	auto renderer = GetGameObject()->AddComponent<MeshRenderer>();
	auto coll = GetGameObject()->AddComponent<SphereCollider>();
	coll->isTrigger = true;
}

void SableAttack::Update()
{
	destroyTimer += Time::deltaTime();
	if (destroyTimer > destoryTime)
	{
		GetGameObject()->Destory();
	}
}

void SableAttack::OnCollision(const ComponentPtr& self, const ComponentPtr& other)
{
	if (other->GetGameObject()->tag != "MS")
	{
		return;
	}
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
