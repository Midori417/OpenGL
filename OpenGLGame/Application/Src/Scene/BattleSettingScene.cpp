/**
* @file BattleSettingScene.cpp
*/
#include "BattleSettingScene.h"
#include "../BattleSettingManager.h"

/**
* �o�g���ݒ�V�[���̏�����
*/
bool BattleSettingScene::Initialize()
{

	// �o�g���ݒ�}�l�[�W�����쐬
	{
		auto battleSettingManagerObj = CreateGameObject("BattleSettingManager");
		battleSettingManagerObj->AddComponent<BattleSettingManager>();
	}

	return false;
}
