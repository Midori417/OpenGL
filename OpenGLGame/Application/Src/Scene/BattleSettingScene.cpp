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
* �o�g���ݒ�V�[���̏�����
*
* @return true  ����������
* @return false ���������s
*/
bool BattleSettingScene::Initialize()
{
    // �A�Z�b�g�}�l�[�W���[���擾
    auto assetManager = AssetManager::GetInstance();

    // �J�����쐬
    auto camera = Instantate(CreateObjectType::Camera);
    AudioSourcePtr audio = camera->AddComponent<AudioSource>();

    // ����BGM���������Ă��Ȃ��̂ň�U�^�C�g��BGM�𗬂�
    audio->SetSoundFilename(GameSound::BGM::title);
    audio->Play();
    audio->isLooop = true;

    // �o�g���ݒ�Ǘ��I�u�W�F�N�g���쐬
    GameObjectPtr manager = Instantate(CreateObjectType::Empty);
    manager->AddComponent<BattleSettingManager>();

    // �w�i���쐬
    {
        GameObjectPtr backGround = Instantate(CreateObjectType::Empty);
        backGround->name = "BattleSettingBackGround";

        ImagePtr image = backGround->AddComponent<Image>();
        image->texture = assetManager->GetTexture("BattleSettingBackGround");
        image->SetWindowSize();
    }

    return false;
}
