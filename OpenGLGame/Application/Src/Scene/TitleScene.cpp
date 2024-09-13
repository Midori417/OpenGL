/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Asset/AssetManager.h"

#include "../Component/TitleManager.h"
#include "../Component/ImageBlinking.h"

/**
* タイトルシーンの初期化
*
* @return true  初期化成功
* @return false 初期化失敗
*/
bool TitleScene::Initialize()
{
    // アセットマネージャーを取得
    auto assetManager = AssetManager::GetInstance();

    // カメラ作成
    auto camera = Instantate(CreateObjectType::Camera);
    AudioSourcePtr audio = camera->AddComponent<AudioSource>();

    // タイトルBGMを流す
    audio->SetSoundFilename("Application/Res/Sound/Title/Title.mp3");
    audio->Play();
    audio->isLooop = true;

    // タイトル管理オブジェクトを作成
    GameObjectPtr manager = Instantate(CreateObjectType::Empty);
    manager->AddComponent<TitleManager>();

    // 背景を作成
    {
        GameObjectPtr backGround = Instantate(CreateObjectType::Empty);
        backGround->name = "TitleBackGround";

        ImagePtr image = backGround->AddComponent<Image>();
        image->texture = assetManager->GetTexture("TitleBackGround");
        image->SetWindowSize();
    }
    // 点滅するガンダムの眼を作成
    {
        GameObjectPtr gundamEye = Instantate(CreateObjectType::Empty);
        gundamEye->name = "GundamEye";

        auto image = gundamEye->AddComponent<Image>();
        image->texture = assetManager->GetTexture("TitleGundamEye");
        image->SetWindowSize();

        ImageBlinkingPtr blinking = gundamEye->AddComponent<ImageBlinking>();
        blinking->speed = 0.5f;
    }
    // PleaseButtonを作成
    {
        GameObjectPtr pleaseButton = Instantate(CreateObjectType::Empty);
        pleaseButton->name = "PleaseButton";
        pleaseButton->GetTransform()->position = Vector3(-50, 350, 0);

        ImagePtr image = pleaseButton->AddComponent<Image>();
        image->texture = assetManager->GetTexture("PleaseButton");
        if (image)
        {
            image->size = image->texture->GetSize() * 1.5f;
        }

        ImageBlinkingPtr blinking = pleaseButton->AddComponent<ImageBlinking>();
    }

    // 初期化成功
    return true;
}
