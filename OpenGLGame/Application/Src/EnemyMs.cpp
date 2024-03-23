/**
* @file EnemyMs.cpp
*/
#include "EnemyMs.h"

void EnemyMs::Awake()
{
	auto engine = GetGameObject()->GetEngine();

	// コライダーを追加
	auto colllder = GetGameObject()->AddComponent<AabbCollider>();
	colllder->aabb = { Vector3(-1,-6.5f,-1), Vector3(1,1,1) };

	// レンダラーを追加
	auto renderer = GetGameObject()->AddComponent<GltfAnimatedMeshRenderer>();
	renderer->fileBuffer = engine->GetGltfFileBuffer();
	renderer->file = engine->LoadGltf("Application/Res/Gundam/Model/GundamGL.gltf");
	GetGameObject()->AddComponent<CharacterMovement>();
}

/**
* ダメージを与える
*/
void EnemyMs::Damage(float damage)
{
	parameter.hp -= damage;
}

void EnemyMs::Start()
{
	// 最大HPを設定
	parameter.hpMax = 600;
	parameter.hp = parameter.hpMax;
	parameter.teum = 2;
	GetGameObject()->tag = "MS";
}

void EnemyMs::Update()
{
	if (parameter.hp <= 0)
	{
		Destory(this);
	}
}



void EnemyMs::OnCollision(const ComponentPtr& self, const ComponentPtr& other)
{
}
