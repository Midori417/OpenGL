/**
* @file MapRangeLimit.h
*/
#include "MapRangeLimit.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/CreateGameObjectType.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/AabbCollider.h"
#include "FGEngine/Component/MeshRenderer.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Asset/Material.h"

/**
* Updateが始まる前に一度実行
*/
void MapRangeLimit::Start()
{
	auto assetManager = AssetManager::GetInstance();
	mesh = assetManager->GetStaticMesh("Cube");
	shader = assetManager->GetShader(DefalutShader::Unlit);
	material = Material::Create("MapRed");
	material->mainTexture = assetManager->GetTexture("white");
	material->color = Color::red;

	{
		Vector2 pos = Vector2(0, mapSize.y);
		Vector2 size = Vector2(mapSize.x, 1);
		CreateMapWall(pos, size);
	}
	{
		Vector2 pos = Vector2(0, -mapSize.y);
		Vector2 size = Vector2(mapSize.x, 1);
		CreateMapWall(pos, size);
	}
	{
		Vector2 pos = Vector2(mapSize.x, 0);
		Vector2 size = Vector2(1, mapSize.y);
		CreateMapWall(pos, size);
	}
	{
		Vector2 pos = Vector2(-mapSize.x, 0);
		Vector2 size = Vector2(1, mapSize.y);
		CreateMapWall(pos, size);
	}
}

/**
* 毎フレーム実行
*/
void MapRangeLimit::Update()
{
}

/**
* コンポーネントのクローンを作成する
*
* @return 作成したクローン
*/
ComponentPtr MapRangeLimit::Clone() const
{
    return ComponentPtr();
}

/**
* 壁を作成
*/
void MapRangeLimit::CreateMapWall(const Vector2& pos, const Vector2& size)
{
	GameObjectPtr wall = Instantate(CreateObjectType::Empty);
	wall->name = "Wall";
	wall->GetTransform()->position = Vector3(pos.x, -6.0f, pos.y);
	wall->GetTransform()->scale = Vector3(size.x, 100, size.y);
	wall->tag = "Wall";

	// 衝突判定を追加
	auto col = wall->AddComponent<AabbCollider>();

	// 赤色の線を作成
	GameObjectPtr line = Instantate(CreateObjectType::Empty);
	line->name = "Line";
	line->GetTransform()->position = Vector3(pos.x, 1.0f, pos.y);
	line->GetTransform()->scale = Vector3(size.x, 1, size.y);

	auto render = line->AddComponent<MeshRenderer>();
	render->mesh = mesh;
	render->shader = shader;
	render->materials.push_back(material);
}
