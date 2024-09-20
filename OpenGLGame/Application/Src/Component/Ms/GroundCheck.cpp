/**
* @file GroundCheck.cpp
*/
#include "GroundCheck.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/MeshRenderer.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Asset/AssetManager.h"

/**
* Updateの前に実行
*/
void GroundCheck::Start()
{
	// アセットマネージャーを取得
	auto assetManager = AssetManager::GetInstance();

	if (isRender)
	{
		renderer = OwnerObject()->AddComponent<MeshRenderer>();
		renderer->mesh = assetManager->GetStaticMesh("Sphere");
		renderer->shader = assetManager->GetShader(DefalutShader::Unlit);
	}

	SphereColliderPtr col = OwnerObject()->AddComponent<SphereCollider>();
	col->isTrigger = true;
}

/**
* 他のコリジョンに触れたときに実行
*/
void GroundCheck::OnCollisionEnter(const CollisionPtr& other)
{
	isGround = true;
}

/**
* 他のコリジョンから離れたときに実行
*/
void GroundCheck::OnCollisionExit(const CollisionPtr& other)
{
	isGround = false;
}
