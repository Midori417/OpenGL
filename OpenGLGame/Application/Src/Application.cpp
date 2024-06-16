/**
* @file Application.cpp
*/
#include "Application.h"
#include "Scene/TitleScene.h"
#include "Scene/BattleMap01Scene.h"
#include "Scene/BattleSettingScene.h"
#include "Scene/ChoiceScene.h"
#include "Scene/TestScene.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;
using namespace FGEngine::ResouceSystem;

/**
* アプリケーションの初期化
*
* @return 0		正常に終了
* @return 0以外 初期化に失敗
*/
int Application::Initialize()
{
	auto resManager = ResouceManager::GetInstance();

	// リソースの読み込み
	for (int i = 0; i < 10; i++)
	{
		std::string num = "Num" + std::to_string(i);
		resManager->LoadTga(num, "Application/Res/UI/Num/" + num + ".tga");
	}
	// タイトル
	{
		resManager->LoadTga("TitleBack", "Application/Res/UI/Title/TitleBack.tga");
		resManager->LoadTga("TitleGundam", "Application/Res/UI/Title/TitleGundam.tga");
		resManager->LoadTga("TitleGundamEye", "Application/Res/UI/Title/GundamEye.tga");
		resManager->LoadTga("TitleLogo", "Application/Res/UI/Title/TitleLogo.tga");
	}
	resManager->LoadTga("PleaseButton", "Application/Res/UI/Title/PleaseButton.tga");
	resManager->LoadTga("BattleButton", "Application/Res/UI/Title/BattleButton.tga");
	resManager->LoadTga("OptionButton", "Application/Res/UI/Title/OptionButton.tga");
	resManager->LoadTga("ExitButton", "Application/Res/UI/Title/ExitButton.tga");
	resManager->LoadTga("BattleSetting", "Application/Res/UI/BattleSetting/BattleSetting.tga");

	// ブーストバー
	resManager->LoadTga("BoostBar", "Application/Res/UI/Battle/BoostBar/BoostBar.tga");
	resManager->LoadTga("BoostBarBack", "Application/Res/UI/Battle/BoostBar/BoostBarBack.tga");
	resManager->LoadTga("BoostBarOVERHEAT", "Application/Res/UI/Battle/BoostBar/BoostBarOverHeat.tga");

	resManager->LoadTga("BurstBar", "Application/Res/UI/Battle/BurstBar.tga");
	resManager->LoadTga("BurstBarBack", "Application/Res/UI/Battle/BurstBarBack.tga");
	resManager->LoadTga("GO", "Application/Res/UI/Battle/Go.tga");
	resManager->LoadTga("GoBack", "Application/Res/UI/Battle/GoBack.tga");
	resManager->LoadTga("PlayerInfo", "Application/Res/UI/Battle/PlayerInfo.tga");
	resManager->LoadTga("STANDBAY", "Application/Res/UI/Battle/Standbay.tga");
	resManager->LoadTga("Timer", "Application/Res/UI/Battle/Timer.tga");
	resManager->LoadTga("OtherTeumMsInfo", "Application/Res/UI/Battle/TargetMsInfo.tga");
	resManager->LoadTga("OtherTeumMsHpBar", "Application/Res/UI/Battle/TargetMsHpBar.tga");

	// ターゲットマーク
	resManager->LoadTga("TargetMarkGreen", "Application/Res/UI/Battle/TargetMark/TargetMarkGreen.tga");
	resManager->LoadTga("TargetMarkRed", "Application/Res/UI/Battle/TargetMark/TargetMarkRed.tga");
	resManager->LoadTga("TargetMarkLock", "Application/Res/UI/Battle/TargetMark/TargetMarkLock.tga");
	resManager->LoadTga("TargetMarkYellow", "Application/Res/UI/Battle/TargetMark/TargetMarkYellow.tga");

	// 味方の体力
	resManager->LoadTga("MyTeumOtherMsInfo", "Application/Res/UI/Battle/TeumOtherMsInfo.tga");
	resManager->LoadTga("MyTeumOtherMsHpBar", "Application/Res/UI/Battle/TeumOtherMsHpBar.tga");
	resManager->LoadTga("PartnerHpBack", "Application/Res/UI/Battle/PartnerHpBack.tga");

	// 武装
	resManager->LoadTga("WeaponBack", "Application/Res/UI/Battle/WeaponBack.tga");
	resManager->LoadTga("WeaponBar", "Application/Res/UI/Battle/WeaponBar.tga");

	// チーム体力
	resManager->LoadTga("TeamHpFrame", "Application/Res/UI/Battle/TeamHp/TeamHpFrame.tga");
	resManager->LoadTga("MyTeamHpBar", "Application/Res/UI/Battle/TeamHp/MyTeamHpBar.tga");
	resManager->LoadTga("OtherTeamHpBar", "Application/Res/UI/Battle/TeamHp/OtherTeamHpBar.tga");

	// 勝敗
	resManager->LoadTga("Win", "Application/Res/UI/Battle/Win.tga");
	resManager->LoadTga("Lose", "Application/Res/UI/Battle/Lose.tga");

	resManager->LoadTga("Particle", "Application/Res/particle.tga", GL_LINEAR);

	// シーンの登録
	SceneManager::AddScene<TitleScene>("タイトルシーン");
	SceneManager::AddScene<ChoiceScene>("ゲーム選択シーン");
	SceneManager::AddScene<BattleSettingScene>("バトル設定シーン");
	SceneManager::AddScene<BattleMap01Scene>("バトルマップ01シーン");

	// 最初に流すシーン
	//SceneManager::LoadScene("タイトルシーン");
	SceneManager::LoadScene("バトル設定シーン");

	//SceneManager::AddScene<TestScene>("テストシーン");
	//SceneManager::LoadScene("テストシーン");


	return 0;
}

/**
* アプリケーションの更新
*/
void Application::Update()
{
}

/**
* アプリケーションの終了
*/
void Application::Fainalize()
{
}
