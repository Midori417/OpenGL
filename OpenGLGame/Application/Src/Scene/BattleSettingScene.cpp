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
	GameObjectPtr manager = Create(CreateObject::Empty);
	manager->name = "BattleSettingManager";
	manager->AddComponent<BattleSettingManager>();

	return false;
}
