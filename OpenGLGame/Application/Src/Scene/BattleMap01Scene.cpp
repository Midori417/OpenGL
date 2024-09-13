/**
* @file BattleMap01Scene,cpp
*/
#include "BattleMap01Scene.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/AabbCollider.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Asset/Material.h"

#include "../Component/BattleManger.h"

/**
* バトルマップ01シーンの初期化
*
* @return true  初期化成功
* @return false 初期化失敗
*/
bool BattleMap01Scene::Initialize()
{
    // アセットマネージャーを取得
    auto assetManager = AssetManager::GetInstance();

    // カメラ作成
    auto camera = Instantate(CreateObjectType::Camera);

    // バトルマネージャーを作成
    GameObjectPtr manager = Instantate(CreateObjectType::Empty);
    auto batManager = manager->AddComponent<BattleManager>();
    
    // ステージの大きさを設定
    const Vector2 mapSize(150, 180);

    // 復帰位置
    std::vector<Vector3> responPoses;
    responPoses.push_back(Vector3(0, 20, 50));
    responPoses.push_back(Vector3(0, 20, -50));
    responPoses.push_back(Vector3(-118, 20, -30));
    responPoses.push_back(Vector3(-100, 20, -79));
    responPoses.push_back(Vector3(140, 20, 112));

    // マネージャーにリスポーン位置を設定
    batManager->SetResponPos(responPoses);

    // マップを作成
    {
        // 地面
        {
            GameObjectPtr ground = Instantate(CreateObjectType::Empty);
            ground->name = "Ground";
            ground->GetTransform()->position = Vector3::zero;

            GltfMeshRendererPtr render = ground->AddComponent<GltfMeshRenderer>();
            render->glTFfile = assetManager->GetGltfFile("Map01/Ground");
            render->shader = assetManager->GetShader(DefalutShader::Standard3D);

            auto col = ground->AddComponent<AabbCollider>();
            col->min = Vector3(-mapSize.x, -10.0f, -mapSize.y);
            col->max = Vector3(mapSize.x, 1, mapSize.y);
        }
        // 建物
        {

        }
    }

    // スカイスフィアを設定
    auto material = std::make_shared<Material>();
    material->mainTexture = assetManager->GetTexture("SkyBox");
    skyBoxMaterial = material;

    return false;
}
