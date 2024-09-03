/**
* @file BattleSettingManager.cpp
*/
#include "BattleSettingManager.h"
#include "BattleManager.h"
#include "Global.h"
#include "FadeOut.h"
using namespace FGEngine::UI;

/**
* 生成時に実行
*/
void BattleSettingManager::Awake()
{
	// マネージャを取得
	auto resManager = AssetManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// バトル設定画面を作成
	{
		auto battleSetting = Instantate("BattleSetting");
		auto image = battleSetting->AddComponent<Image>();
		image->texture = resManager->GetTexture("BattleSetting");
		image->size = winManager->GetWindowSize();
	}

	// フェードオブジェクトを作成
	{
		auto fadeObject = Instantate("FadeObjectB");
		fadeOut = fadeObject->AddComponent<FadeOut>();
	}

	// バトル情報を作成
	battleInfo = std::make_shared<BattleInfo>();
	// 配列を予約
	battleInfo->controlInfo.reserve(playerMax);
	for (int i = 0; i < playerMax; ++i)
	{
		battleInfo->controlInfo.push_back(std::make_shared<ControlInfo>());
	}

	// テスト
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
* 毎フレーム実行
*/
void BattleSettingManager::Update()
{
	// フェードアウトが終わったら
	if (fadeOut->IsFadeOut())
	{
		switch (select)
		{
		case BattleSettingManager::Select::BattleStart:
			SceneManager::LoadScene("バトルマップ01シーン");
			BattleManager::SetBattleInfo(battleInfo);
			break;
		case BattleSettingManager::Select::Back:
			SceneManager::LoadScene("ゲーム選択シーン");
			break;
		}
	}

	/**
	* フェードが開始したら何もしない
	*/
	if (fadeOut->IsFadeStart())
	{
		return;
	}

	// Eneter(決定ボタン)をフェード開始
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
