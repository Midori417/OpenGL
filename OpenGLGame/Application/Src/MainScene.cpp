/**
* @file MainScene.cpp
*/
#include "MainScene.h"
#include "PlayerManager.h"

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
bool MainScene::Initialize(FGEngine::Engine& engine)
{
    // カメラを作成
    auto camera = engine.CreateCameraObject("Camera", Vector3(0, 4, 20));


    // ステージの作成
    {

        auto ground = engine.Create<GameObject>("Ground", Vector3(0, -7.8f, 0));
        {
            ground->transform->scale = Vector3(200, 1, 200);
            ground->tag = "Ground";
            auto renderer = ground->AddComponent<MeshRenderer>();
            renderer->mesh = engine.GetStaticMesh("box");
            renderer->mesh->materials = CloneMaterialList(renderer->mesh);
            renderer->mesh->materials[0]->texBaseColor = engine.GetTexture("Application/Res/Map/Gross.tga");
            auto collider = ground->AddComponent<AabbCollider>();
            collider->isStatic = true;
        }

        auto load = engine.Create<GameObject>("Load", Vector3(-90, 0, -100));
        {
            auto renderer = load->AddComponent<MeshRenderer>();

            renderer->mesh = engine.GetStaticMesh("Application/Res/Map/Load.obj");
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->mesh->materials[0]->texBaseColor = engine.GetTexture("FGEngine/Res/Texture/white.tga");
        }

        auto biru1 = engine.Create<GameObject>("Biru", Vector3(37, 0, 67));
        
        biru1->AddComponent<MeshRenderer>()->mesh = engine.GetStaticMesh("Application/Res/Map/Biru01.obj");
        biru1->SetParent(load);

        auto biru2 = engine.Create<GameObject>("Biru2", Vector3(-33, 0, 56));
        biru2->AddComponent<MeshRenderer>()->mesh = engine.GetStaticMesh("Application/Res/Map/Biru02.obj");
        biru2->SetParent(load);

        auto biru3 = engine.Create<GameObject>("Biru3", Vector3(37, 0, 0), Quaternion::AngleAxis(90.0f * Mathf::Deg2Rad, Vector3::up));
        biru3->AddComponent<MeshRenderer>()->mesh = engine.GetStaticMesh("Application/Res/Map/Biru03.obj");
        biru3->SetParent(load);

        auto biru4 = engine.Create<GameObject>("Biru4", Vector3(42, 0, -67));
        biru4->AddComponent<MeshRenderer>()->mesh = engine.GetStaticMesh("Application/Res/Map/Biru02.obj");
        biru4->SetParent(load);

        auto biru5 = engine.Create<GameObject>("Biru5", Vector3(-39, 0, -63));
        biru5->AddComponent<MeshRenderer>()->mesh = engine.GetStaticMesh("Application/Res/Map/Biru03.obj");
        biru5->SetParent(load);

        auto biru6 = engine.Create<GameObject>("Biru6", Vector3(209, 0, 244));
        biru6->AddComponent<MeshRenderer>()->mesh = engine.GetStaticMesh("Application/Res/Map/Biru01.obj");
        biru6->SetParent(load);

    }

    // プレイヤーを配置
    auto player = engine.Create<GameObject>("Player");
    player->AddComponent<PlayerManager>();
     
    // スカイスフィアを設定
    auto material = std::make_shared<FGEngine::Material>();
    material->texBaseColor = engine.GetTexture("Application/Res/Map/sky2.tga");
    SetSkyMaterial(material);

	return true;
}

/**
* メインシーンの更新
* 
* @param engine エンジン
*/
void MainScene::Update(FGEngine::Engine& engine)
{
}

/**
* メインシーンの終了
* 
* @param engine エンジン
*/
void MainScene::Finalize(FGEngine::Engine& engine)
{

    engine.AllClearGameObject();
}
