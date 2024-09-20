/**
* @file SelectScene.cpp
*/
#include "SelectScene.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Asset/AssetManager.h"

#include "../Component/SelectManager.h"
#include "../GameSoundName.h"

/**
* ゲーム選択シーンの初期化
*
* @return true  初期化成功
* @return false 初期化失敗
*/
bool SelectScene::Initialize()
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

    // 選択管理オブジェクトを作成
    GameObjectPtr manager = Instantate(CreateObjectType::Empty);
    manager->AddComponent<SelectManager>();

    // 背景を作成
    {
        GameObjectPtr backGround = Instantate(CreateObjectType::Empty);
        backGround->name = "SelectBackGround";

        ImagePtr image = backGround->AddComponent<Image>();
        image->texture = assetManager->GetTexture("SelectBackGround");
        image->SetWindowSize();
    }

    return true;
}
