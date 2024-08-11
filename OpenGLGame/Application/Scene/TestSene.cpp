/**
* TesScene.cpp
*/
#include "TestScene.h"
using namespace FGEngine;
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;

bool TestScene::Initialize()
{
	auto objManager = ObjectManager::GetInstance();
	auto resManager = ResouceManager::GetInstance();
	// 空の画像
	resManager->LoadTga("Sky", "Application/Res/Map/sky2.tga");

	// カメラの作成
	auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -10));
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);


	// スカイスフィアを設定
	auto material = std::make_shared<Material>();
	material->mainTexture = resManager->GetTexture("Sky");
	skyMaterial = material;

	return 0;
}