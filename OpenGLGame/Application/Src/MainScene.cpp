/**
* @file MainScene.cpp
*/
#include "MainScene.h"
#include <thread>
#include <chrono>

/**
* メインシーンの初期化
* 
* @param engine エンジン
* 
* @return true  初期化成功
* @return false 初期化失敗
*/
bool MainScene::Initialize()
{
    auto objManager = ObjectSystem::ObjectManager::GetInstance();
    auto resManager = ResouceSystem::ResouceManager::GetInstance();

    auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
    camera->AddComponent<Camera>();
    objManager->SetMainCamera(camera);


    auto material = std::make_shared<Material>();
    material->mainTexture = resManager->GetTexture("sky");

    skyMaterial = material;


	return true;
}

/**
* メインシーンの更新
* 
* @param engine エンジン
*/
void MainScene::Update()
{
}

/**
* メインシーンの終了
* 
* @param engine エンジン
*/
void MainScene::Finalize()
{

}
