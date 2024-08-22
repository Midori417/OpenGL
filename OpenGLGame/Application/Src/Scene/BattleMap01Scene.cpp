/**
* @file BattleMap01Scene.cpp
*/
#include "BattleMap01Scene.h"
#include "../BattleManager.h"
#include <thread>
#include <chrono>
using namespace FGEngine::InputSystem;

bool BattleMap01Scene::isResouceLoad = false;

/**
* 戦闘シーンの初期化
*
* @return true  初期化成功
* @return false 初期化失敗
*/
bool BattleMap01Scene::Initialize()
{
	// 各マネージャを取得
	auto resManager = AssetManager::GetInstance();

	if (!isResouceLoad)
	{
		// 空の画像
		resManager->LoadTga("Sky", "Application/Res/Map/sky2.tga");
		// マップ01のリソース読み込み
		resManager->LoadGlTF("Map01", "Application/Res/Map/Map01/Map01.gltf");
		resManager->LoadGlTF("Map01/Ground", "Application/Res/Map/Map01/Ground.gltf");
		//resManager->LoadGlTF("Map01/Biru01", "Application/Res/Map/Map01/Biru01.gltf");
		//resManager->LoadGlTF("Map01/Biru02", "Application/Res/Map/Map01/Biru02.gltf");
		//resManager->LoadGlTF("Map01/Biru03", "Application/Res/Map/Map01/Biru03.gltf");
		isResouceLoad = true;
	}
	// カメラを作成
	auto camera = CreateGameObject("Camera", Vector3(0, 0, -20), Quaternion::identity);
	auto cameraInfo = camera->AddComponent<Camera>();
	SetMainCameraInfo(cameraInfo);

	// ステージの大きさを設定
	mapSize.x = 150;
	mapSize.y = 180;

	// 復帰位置
	std::vector<Vector3> responPoses;
	responPoses.push_back(Vector3(0, 20, 50));
	responPoses.push_back(Vector3(0, 20, -50));
	responPoses.push_back(Vector3(-118, 20, -30));
	responPoses.push_back(Vector3(-100, 20, -79));
	responPoses.push_back(Vector3(140, 20, 112));

	// バトルマネージャを作成
	{
		auto battleManagerObj = CreateGameObject("BattleManager");
		auto battleManager = battleManagerObj->AddComponent<BattleManager>();
		battleManager->SetResponPos(responPoses);
	}

	// 壁を作成
	{
		// 前
		{
			auto wall = CreateGameObject("Wall", Vector3(0, -6.0f, mapSize.y), Quaternion::identity);
			wall->tag = "Wall";
			wall->GetTransform()->scale = Vector3(mapSize.x, 100, 1);
			auto col = wall->AddComponent<AabbCollider>();
			col->min = Vector3(-1, -1, -10);

			auto line = CreateGameObject("Line", Vector3(0, 1.0f, mapSize.y), Quaternion::identity);
			line->GetTransform()->scale = Vector3(mapSize.x, 1, 1);
			auto render = line->AddComponent<MeshRenderer>();
			render->mesh = resManager->GetStaticMesh("Cube");
			render->shader = resManager->GetShader(DefalutShader::Unlit);
			render->materials = CloneMaterialList(render->mesh);
			render->materials[0]->mainTexture = resManager->GetTexture("white");
			render->materials[0]->color = Color::red;
		}
		// 後ろ
		{
			auto wall = CreateGameObject("Wall", Vector3(0, -6.0f, -mapSize.y), Quaternion::identity);
			wall->tag = "Wall";
			wall->GetTransform()->scale = Vector3(mapSize.x, 100, 1);
			auto col = wall->AddComponent<AabbCollider>();
			col->max = Vector3(1, 1, 10);

			auto line = CreateGameObject("Line", Vector3(0, 1.0f, -mapSize.y), Quaternion::identity);
			line->GetTransform()->scale = Vector3(mapSize.x, 1, 1);
			auto render = line->AddComponent<MeshRenderer>();
			render->mesh = resManager->GetStaticMesh("Cube");
			render->shader = resManager->GetShader(DefalutShader::Unlit);
			render->materials = CloneMaterialList(render->mesh);
			render->materials[0]->mainTexture = resManager->GetTexture("white");
			render->materials[0]->color = Color::red;

		}

		// 右
		{
			auto wall = CreateGameObject("Wall", Vector3(mapSize.x, -6.0f, 0), Quaternion::identity);
			wall->tag = "Wall";
			wall->GetTransform()->scale = Vector3(1, 100, mapSize.y);
			auto col = wall->AddComponent<AabbCollider>();
			col->max = Vector3(10, 1, 1);

			auto line = CreateGameObject("Line", Vector3(mapSize.x, 1.0f, 0), Quaternion::identity);
			line->GetTransform()->scale = Vector3(1, 1, mapSize.y);
			auto render = line->AddComponent<MeshRenderer>();
			render->mesh = resManager->GetStaticMesh("Cube");
			render->shader = resManager->GetShader(DefalutShader::Unlit);
			render->materials = CloneMaterialList(render->mesh);
			render->materials[0]->mainTexture = resManager->GetTexture("white");
			render->materials[0]->color = Color::red;

		}
		// 左
		{
			auto wall = CreateGameObject("Wall", Vector3(-mapSize.x, -6.0f, 0), Quaternion::identity);
			wall->tag = "Wall";
			wall->GetTransform()->scale = Vector3(1, 100, mapSize.y);
			auto col = wall->AddComponent<AabbCollider>();
			col->min = Vector3(-10, -1, -1);

			auto line = CreateGameObject("Line", Vector3(-mapSize.x, 1.0f, 0), Quaternion::identity);
			line->GetTransform()->scale = Vector3(1, 1, mapSize.y);
			auto render = line->AddComponent<MeshRenderer>();
			render->mesh = resManager->GetStaticMesh("Cube");
			render->shader = resManager->GetShader(DefalutShader::Unlit);
			render->materials = CloneMaterialList(render->mesh);
			render->materials[0]->mainTexture = resManager->GetTexture("white");
			render->materials[0]->color = Color::red;
		}

	}

	// ステージを作成
	{
		// 土台
		{
			auto ground = CreateGameObject("Ground", Vector3(0, -1.0f, 0), Quaternion::identity);
			ground->tag = "Ground";
			auto renderer = ground->AddComponent<GltfMeshRenderer>();
			renderer->glTFfile = resManager->GetGltfFile("Map01/Ground");
			renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
			auto col = ground->AddComponent<AabbCollider>();
			col->min = Vector3(-mapSize.x, -10.0f, -mapSize.y);
			col->max = Vector3(mapSize.x, 1.0f, mapSize.y);
		}
	}


	// スカイスフィアを設定
	auto material = std::make_shared<Material>();
	material->mainTexture = resManager->GetTexture("Sky");
	skyBoxMaterial = material;

	return true;
}