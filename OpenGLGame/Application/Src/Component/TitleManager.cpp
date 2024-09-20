/**
* @file TitleManager.cpp
*/
#include "TitleManager.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/CreateGameObjectType.h"
#include "FGEngine/Debug.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Scene/SceneManager.h"

#include "FadeOut.h"
#include "../GameSoundName.h"

/**
* Update���n�܂�O�Ɉ�x���s
*/
void TitleManager::Start()
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
void TitleManager::Update()
{
	if (!fadeOut)
	{
		LOG_ERROR("�t�F�[�h�I�u�W�F�N�g�����݂��܂���");
		return;
	}

	// �t�F�[�h���I��������V�[�����ړ�����
	if (fadeOut->IsFadeOut())
	{
		SceneManager::LoadScene("SelectScene");
	}

	// �t�F�[�h���n�܂��Ă����炱�����牺�̏����͎��s���Ȃ�
	if (fadeOut->IsFadeStart())
	{
		return;
	}

	// Enter�L�[�̓��͂�����΃t�F�[�h���J�n����
	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		audioSource->Play();
		fadeOut->FadeStart();
	}
}
