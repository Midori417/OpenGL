/**
* @file BattleMap01Scene.cpp
*/
#include "BattleMap01Scene.h"
#include "../BattleManager.h"
#include <thread>
#include <chrono>
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::InputSystem;

/**
* 戦闘シーンの初期化
* 
* @param engine エンジン
* 
* @return true  初期化成功
* @return false 初期化失敗
*/
bool BattleMap01Scene::Initialize()
{
    auto objManager = ObjectManager::GetInstance();
    auto resManager = ResouceManager::GetInstance();

    resManager->LoadGlTF("Gundam", "Application/Res/Ms/Gundam/Model/GundamGL.gltf");

    // マップ01のリソース読み込み
    resManager->LoadObj("Biru01", "Application/Res/Map/Map01/Biru01.obj");
    resManager->LoadObj("Biru02", "Application/Res/Map/Map01/Biru02.obj");
    resManager->LoadObj("Biru03", "Application/Res/Map/Map01/Biru03.obj");
    resManager->LoadObj("Load", "Application/Res/Map/Map01/Load.obj");
    resManager->LoadObj("Ground", "Application/Res/Map/Map01/Ground.obj");
    resManager->LoadTga("Grass", "Application/Res/Map/Map01/Grass.tga");


    // カメラを作成
    auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -20), Quaternion::identity);
    camera->AddComponent<Camera>();
    objManager->SetMainCamera(camera);

    // ステージの大きさを設定
    mapX = 150;
    mapZ = 120;


    // バトルマネージェーを作成
    {
        auto battleManagerObj = objManager->CreateGameObject("BattleManager");
        auto battleManager = battleManagerObj->AddComponent<BattleManager>();
        battleManager->mapX = mapX;
        battleManager->mapZ = mapZ;
    }

    // テスト
    {
    }

    // ステージを作成
    {
        // 地面を作成
         auto ground = objManager->CreateGameObject("Ground", Vector3(0, -6.0f, 0));
        {
            ground->tag = "Ground";
            auto renderer = ground->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Ground");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("Grass");
            auto col = ground->AddComponent<AabbCollider>();
            col->min = Vector3(-150, -0.5f, -120);
            col->max = Vector3(150, 0.5f, 120);
        }

        // 道を作成
        {
            auto load = objManager->CreateGameObject("Load", Vector3(0, 0, 0));
            load->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = load->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Load");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.1f, 0.1f, 0.1f, 1);
        }
        // 建物01Aを作成
        {
            auto biru01 = objManager->CreateGameObject("Biru01A", Vector3(-37.0f, 6.0f, 0));
            biru01->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru01->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru01");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
        }
        // 建物01Bを作成
        {
            auto biru01 = objManager->CreateGameObject("Biru01B", Vector3(61.0f, 6.0f, -66.0f));
            biru01->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru01->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru01");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
        }
        // 建物02Aを作成
        {
            auto biru02 = objManager->CreateGameObject("Biru02A", Vector3(-91.0f, 6.0f, -0.4f));
            biru02->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru02->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru02");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
        }
        // 建物02Bを作成
        {
            auto biru02 = objManager->CreateGameObject("Biru02B", Vector3(-43.0f, 6.0f, 77.0f));
            biru02->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru02->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru02");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
        }
        // 建物03Aを作成
        {
            auto biru03 = objManager->CreateGameObject("Biru03A", Vector3(-37.0f, 6.0f, 38.0f));
            biru03->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru03->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru03");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
        }
        // 建物03Bを作成
        {
            auto biru03 = objManager->CreateGameObject("Biru03B", Vector3(-95.0f, 6.0f, 78.0f), Quaternion::AngleAxis(90, Vector3::up));
            biru03->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru03->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru03");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
        }

    }

    // スカイスフィアを設定
    auto material = std::make_shared<Material>();
    material->mainTexture = resManager->GetTexture("sky");
    skyMaterial = material;

	return true;
}

/**
* 戦闘シーンの更新
* 
* @param engine エンジン
*/
void BattleMap01Scene::Update()
{
}

/**
* 戦闘シーンの終了
* 
* @param engine エンジン
*/
void BattleMap01Scene::Finalize()
{

}
