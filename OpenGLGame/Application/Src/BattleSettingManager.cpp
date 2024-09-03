/**
* @file BattleSettingManager.cpp
*/
#include "BattleSettingManager.h"
#include "BattleManager.h"
#include "Global.h"
#include "FadeOut.h"
using namespace FGEngine::UI;

/**
* �������Ɏ��s
*/
void BattleSettingManager::Awake()
{
	// �}�l�[�W�����擾
	auto resManager = AssetManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// �o�g���ݒ��ʂ��쐬
	{
		auto battleSetting = Instantate("BattleSetting");
		auto image = battleSetting->AddComponent<Image>();
		image->texture = resManager->GetTexture("BattleSetting");
		image->size = winManager->GetWindowSize();
	}

	// �t�F�[�h�I�u�W�F�N�g���쐬
	{
		auto fadeObject = Instantate("FadeObjectB");
		fadeOut = fadeObject->AddComponent<FadeOut>();
	}

	// �o�g�������쐬
	battleInfo = std::make_shared<BattleInfo>();
	// �z���\��
	battleInfo->controlInfo.reserve(playerMax);
	for (int i = 0; i < playerMax; ++i)
	{
		battleInfo->controlInfo.push_back(std::make_shared<ControlInfo>());
	}

	// �e�X�g
	battleInfo->controlInfo[0]->teumId = 1;
	battleInfo->controlInfo[0]->playerId = 0;
	battleInfo->controlInfo[0]->ms = MsList::Gundam;

	battleInfo->controlInfo[1]->teumId = 2;
	battleInfo->controlInfo[1]->playerId = 1;
	battleInfo->controlInfo[1]->ms = MsList::Gundam;

	battleInfo->controlInfo[2]->teumId = 2;
	battleInfo->controlInfo[2]->playerId = 1;
	battleInfo->controlInfo[2]->ms = MsList::Gundam;

	battleInfo->controlInfo[3]->teumId = 1;
	battleInfo->controlInfo[3]->playerId = 1;
	battleInfo->controlInfo[3]->ms = MsList::Gundam;
}

/**
* ���t���[�����s
*/
void BattleSettingManager::Update()
{
	// �t�F�[�h�A�E�g���I�������
	if (fadeOut->IsFadeOut())
	{
		switch (select)
		{
		case BattleSettingManager::Select::BattleStart:
			SceneManager::LoadScene("�o�g���}�b�v01�V�[��");
			BattleManager::SetBattleInfo(battleInfo);
			break;
		case BattleSettingManager::Select::Back:
			SceneManager::LoadScene("�Q�[���I���V�[��");
			break;
		}
	}

	/**
	* �t�F�[�h���J�n�����牽�����Ȃ�
	*/
	if (fadeOut->IsFadeStart())
	{
		return;
	}

	// Eneter(����{�^��)���t�F�[�h�J�n
	if (InputKey::GetKey(KeyCode::Enter))
	{
		fadeOut->FadeStart();
		select = Select::BattleStart;

	}
	else if (InputKey::GetKey(KeyCode::Escape))
	{
		fadeOut->FadeStart();
		select = Select::Back;
	}
}
