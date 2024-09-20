/**
* @file BattleSettingScene.cpp
*/
#include "BattleSettingScene.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Asset/AssetManager.h"

#include "../Component/BattleSettingManager.h"
#include "../GameSoundName.h"

/**
* バトル設定シーンの初期化
*
* @return true  初期化成功
* @return false 初期化失敗
*/
bool BattleSettingScene::Initialize()
{
    // アセットマネージャーを取得
    auto assetManager = AssetManager::GetInstance();

    // カメラ作成
    auto camera = Instantate(CreateObjectType::Camera);
    AudioSourcePtr audio = camera->AddComponent<AudioSource>();

    // いいBGMが見つかっていないので一旦タイトルBGMを流す
    audio->SetSoundFilename(GameSound::BGM::title);
    audio->Play();
    audio->isLooop = true;

    // バトル設定管理オブジェクトを作成
    GameObjectPtr manager = Instantate(CreateObjectType::Empty);
    manager->AddComponent<BattleSettingManager>();

    // 背景を作成
    {
        GameObjectPtr backGround = Instantate(CreateObjectType::Empty);
        backGround->name = "BattleSettingBackGround";

        ImagePtr image = backGround->AddComponent<Image>();
        image->texture = assetManager->GetTexture("BattleSettingBackGround");
        image->SetWindowSize();
    }

    return false;
}
