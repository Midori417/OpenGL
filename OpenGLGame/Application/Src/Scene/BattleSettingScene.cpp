/**
* @file BattleSettingScene.cpp
*/
#include "BattleSettingScene.h"
#include "../BattleSettingManager.h"
using namespace FGEngine::ObjectSystem;

/**
* バトル設定シーンの初期化
*/
bool BattleSettingScene::Initialize()
{
	// オブジェクトマネージャを取得
	auto objManager = ObjectSystem::ObjectManager::GetInstance();

	// バトル設定マネージャを作成
	{
		auto battleSettingManagerObj = objManager->CreateGameObject("BattleSettingManager");
		battleSettingManagerObj->AddComponent<BattleSettingManager>();
	}

	return false;
}
