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
* �^�C�g���V�[���̏�����
*
* @return true  ����������
* @return false ���������s
*/
bool TitleScene::Initialize()
{
    // �A�Z�b�g�}�l�[�W���[���擾
    auto assetManager = AssetManager::GetInstance();

    // �J�����쐬
    auto camera = Instantate(CreateObjectType::Camera);
    AudioSourcePtr audio = camera->AddComponent<AudioSource>();

    // �^�C�g��BGM�𗬂�
    audio->SetSoundFilename("Application/Res/Sound/Title/Title.mp3");
    audio->Play();
    audio->isLooop = true;

    // �^�C�g���Ǘ��I�u�W�F�N�g���쐬
    GameObjectPtr manager = Instantate(CreateObjectType::Empty);
    manager->AddComponent<TitleManager>();

    // �w�i���쐬
    {
        GameObjectPtr backGround = Instantate(CreateObjectType::Empty);
        backGround->name = "TitleBackGround";

        ImagePtr image = backGround->AddComponent<Image>();
        image->texture = assetManager->GetTexture("TitleBackGround");
        image->SetWindowSize();
    }
    // �_�ł���K���_���̊���쐬
    {
        GameObjectPtr gundamEye = Instantate(CreateObjectType::Empty);
        gundamEye->name = "GundamEye";

        auto image = gundamEye->AddComponent<Image>();
        image->texture = assetManager->GetTexture("TitleGundamEye");
        image->SetWindowSize();

        ImageBlinkingPtr blinking = gundamEye->AddComponent<ImageBlinking>();
        blinking->speed = 0.5f;
    }
    // PleaseButton���쐬
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

    // ����������
    return true;
}
