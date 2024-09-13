/**
* @file SelectManager.cpp
*/
#include "SelectManager.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/CreateGameObjectType.h"
#include "FGEngine/Debug.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Scene/SceneManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Math/Mathf.h"

#include "FadeOut.h"
#include "../GameSoundName.h"

/**
* Update���n�܂�O�Ɉ�x���s
*/
void SelectManager::Start()
{
	// �A�Z�b�g�}�l�[�W���[���擾
	auto assetManager = AssetManager::GetInstance();

	// UI�̊x���W
	const float baseX = -570;
	// �󂯂鋗��
	const float spaceX = 100;

	// �o�g���{�^�����쐬
	{
		GameObjectPtr button = Instantate(CreateObjectType::Empty);
		button->name = "BattleButton";
		button->GetTransform()->position = Vector3(baseX, -200, 0);

		ImagePtr image = button->AddComponent<Image>();
		image->texture = assetManager->GetTexture("BattleButton");
		image->size = image->texture->GetSize() * 1.3f;

		imgButtons.push_back(image);
	}

	// ��߂�{�^�����쐬
	{
		GameObjectPtr button = Instantate(CreateObjectType::Empty);
		button->name = "ExitButton";
		button->GetTransform()->position = Vector3(baseX + spaceX * 2, 200, 0);

		ImagePtr image = button->AddComponent<Image>();
		image->texture = assetManager->GetTexture("ExitButton");
		image->size = image->texture->GetSize() * 1.3f;

		imgButtons.push_back(image);
	}

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
void SelectManager::Update()
{
	if (!fadeOut)
	{
		LOG_ERROR("�t�F�[�h�I�u�W�F�N�g�����݂��܂���");
		return;
	}

	// �t�F�[�h�A�E�g���I������猻�ݑI������Ă��鍀�ڂ����s����
	// ��X�I�v�V������ǉ��������̂ŃX�C�b�`���ɂ��Ċg��������������
	if (fadeOut->IsFadeOut())
	{
		switch (selectNum)
		{
		case Select::Battle:
			SceneManager::LoadScene("BattleSettingScene");
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
		// Exit���I������Ă�����E�B���h�E�����
		// ����ȊO���I������Ă�����t�F�[�h���J�n����
		if (selectNum == Select::Exit)
		{
			WindowManager::WindowClose();
		}
		else
		{
			audioSource->Play();
			fadeOut->FadeStart();
		}
	}

	// �I�����ڂ̐؂�ւ�
	if (InputKey::GetKeyDown(KeyCode::DownArrow))
	{
		selectNum++;
	}
	else if (InputKey::GetKeyDown(KeyCode::UpArrow))
	{
		selectNum--;
	}
	// �I�����ڂ𒴂��Ȃ��悤�ɒl��␳����
	selectNum = Mathf::Clamp(selectNum, Select::Battle, Select::Exit);

	// �I���A���I�����̃{�^���̐F��ݒ�
	for (int i = 0; i < imgButtons.size(); ++i)
	{
		ImagePtr image = imgButtons[i];
		// �I������Ă��鍀�ڂȂ�ʏ�F
		if (i == selectNum)
		{
			image->color = Color::white;
		}
		// ���I���Ȃ班���Â߂ɂ���
		else
		{
			image->color = noSelectColor;
		}
	}

}
