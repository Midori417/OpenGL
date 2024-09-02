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

	// カメラを作成
	GameObjectPtr camer = Create(CreateObject::Camera);

	// スカイスフィアを設定
	auto material = std::make_shared<Material>();
	material->mainTexture = resManager->GetTexture("Sky");
	skyBoxMaterial = material;

	return 0;
}