/**
* TesScene.cpp
*/
#include "TestScene.h"
using namespace FGEngine;

bool TestScene::Initialize()
{
	auto resManager = AssetManager::GetInstance();
	// 空の画像
	resManager->LoadTga("Sky", "Application/Res/Map/sky2.tga");

	// カメラの作成
	auto camera = CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
	auto cameraInfo = camera->AddComponent<Camera>();
	SetMainCameraInfo(cameraInfo);

	// スカイスフィアを設定
	auto material = std::make_shared<Material>();
	material->mainTexture = resManager->GetTexture("Sky");
	skyBoxMaterial = material;

	return 0;
}