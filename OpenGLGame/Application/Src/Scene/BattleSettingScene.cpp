/**
* @file BattleSettingScene.cpp
*/
#include "BattleSettingScene.h"
#include "../BattleSettingManager.h"

/**
* バトル設定シーンの初期化
*/
bool BattleSettingScene::Initialize()
{

	// バトル設定マネージャを作成
	{
		auto battleSettingManagerObj = CreateGameObject("BattleSettingManager");
		battleSettingManagerObj->AddComponent<BattleSettingManager>();
	}

	return false;
}
