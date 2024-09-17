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
* Update���n�܂�O�Ɉ�x���s
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
* ���t���[�����s
*/
void MapRangeLimit::Update()
{
}

/**
* �R���|�[�l���g�̃N���[�����쐬����
*
* @return �쐬�����N���[��
*/
ComponentPtr MapRangeLimit::Clone() const
{
    return ComponentPtr();
}

/**
* �ǂ��쐬
*/
void MapRangeLimit::CreateMapWall(const Vector2& pos, const Vector2& size)
{
	GameObjectPtr wall = Instantate(CreateObjectType::Empty);
	wall->name = "Wall";
	wall->GetTransform()->position = Vector3(pos.x, -6.0f, pos.y);
	wall->GetTransform()->scale = Vector3(size.x, 100, size.y);
	wall->tag = "Wall";

	// �Փ˔����ǉ�
	auto col = wall->AddComponent<AabbCollider>();

	// �ԐF�̐����쐬
	GameObjectPtr line = Instantate(CreateObjectType::Empty);
	line->name = "Line";
	line->GetTransform()->position = Vector3(pos.x, 1.0f, pos.y);
	line->GetTransform()->scale = Vector3(size.x, 1, size.y);

	auto render = line->AddComponent<MeshRenderer>();
	render->mesh = mesh;
	render->shader = shader;
	render->materials.push_back(material);
}
