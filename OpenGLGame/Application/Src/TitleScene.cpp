/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
using namespace FGEngine::SceneSystem;
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;

/**
* タイトルシーンの初期化
* 
* @param engine エンジン
*/
bool TitleScene::Initialize()
{
	auto objManager = ObjectManager::GetInstance();
	auto resouceManager = ResouceManager::GetInstance();

	auto camera = objManager->CreateGameObject("Camera");
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);

	auto material = std::make_shared<Material>();
	material->mainTexture = resouceManager->GetTexture("sky");

	skyMaterial = material;

	return true;
}

/**
* タイトルシーンの更新
* 
* @param engine		エンジン
* @param deltaTime	前回の更新からの経過時間
*/
void TitleScene::Update()
{
}

/**
* タイトルシーンの終了
* 
* @param engine エンジン
*/
void TitleScene::Finalize()
{
}
