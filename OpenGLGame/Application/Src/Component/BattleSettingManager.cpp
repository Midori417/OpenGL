/**
* @file BattleSettingManager,cpp
*/
#include "BattleSettingManager.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Debug.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Scene/SceneManager.h"

#include "../Component/FadeOut.h"
#include "../GameSoundName.h"

/**
* Update���n�܂�O�Ɉ�x���s
*/
void BattleSettingManager::Start()
{
	// �A�Z�b�g�}�l�[�W���[���擾
	auto assetManager = AssetManager::GetInstance();

	// �t�F�[�h�I�u�W�F�N�g���쐬
	{
		auto obj = Instantate(assetManager->GetGameObject("FadeObject"));
		fadeOut = obj->GetComponent<FadeOut>();
	}

	// ���艹��炷���߂ɃT�E���h�R���|�[�l���g��ǉ�
	audioSource = OwnerObject()->AddComponent<AudioSource>();
	audioSource->SetSoundFilename(GameSound::select);
}

/**
* ���t���[�����s
*/
void BattleSettingManager::Update()
{
	if (!fadeOut)
	{
		LOG_ERROR("�t�F�[�h�I�u�W�F�N�g�����݂��܂���");
		return;
	}

	// �t�F�[�h���I��������V�[�����ړ�����
	if (fadeOut->IsFadeOut())
	{
		switch (select)
		{
		case BattleSettingManager::BattleStart:
			SceneManager::LoadScene("BattleMap01Scene");
			break;
		case BattleSettingManager::Espace:
			SceneManager::LoadScene("SelectScene");
			break;
		}
	}

	// �t�F�[�h���n�܂��Ă����炱�����牺�̏����͎��s���Ȃ�
	if (fadeOut->IsFadeStart())
	{
		return;
	}

	// Enter�L�[�̓��͂�����΃t�F�[�h���J�n����
	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		select = Select::BattleStart;
		audioSource->Play();
		fadeOut->FadeStart();
	}

	// Espace�L�[�̓��͂�����΃t�F�[�h���J�n����
	if (InputKey::GetKeyDown(KeyCode::Escape))
	{
		select = Select::Espace;
		audioSource->Play();
		fadeOut->FadeStart();
	}
}
