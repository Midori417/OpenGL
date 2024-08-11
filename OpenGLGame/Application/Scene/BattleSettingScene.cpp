/**
* @file BattleSettingScene.cpp
*/
#include "BattleSettingScene.h"
#include "../BattleSettingManager.h"
using namespace FGEngine::ObjectSystem;

/**
* �o�g���ݒ�V�[���̏�����
*/
bool BattleSettingScene::Initialize()
{
	// �I�u�W�F�N�g�}�l�[�W�����擾
	auto objManager = ObjectSystem::ObjectManager::GetInstance();

	// �o�g���ݒ�}�l�[�W�����쐬
	{
		auto battleSettingManagerObj = objManager->CreateGameObject("BattleSettingManager");
		battleSettingManagerObj->AddComponent<BattleSettingManager>();
	}

	return false;
}
