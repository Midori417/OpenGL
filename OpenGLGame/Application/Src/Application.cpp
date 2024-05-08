/**
* @file Application.cpp
*/
#include "Application.h"
#include "Scene/TitleScene.h"
#include "Scene/BattleMap01Scene.h"
#include "Scene/ChoiceScene.h"
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
	resManager->LoadTga("TitleBack", "Application/Res/UI/Title/TitleBack.tga");
	resManager->LoadTga("TitleGundam", "Application/Res/UI/Title/TitleGundam.tga");
	resManager->LoadTga("TitleGundamEye", "Application/Res/UI/Title/GundamEye.tga");
	resManager->LoadTga("TitleLogo", "Application/Res/UI/Title/TitleLogo.tga");
	resManager->LoadTga("TitleLogoWhite", "Application/Res/UI/Title/TitleLogoWhite.tga");
	resManager->LoadTga("sky", "Application/Res/Map/sky2.tga");
	resManager->LoadTga("PleaseButton", "Application/Res/UI/Title/PleaseButton.tga");

	// シーンの登録
	SceneManager::AddScene<TitleScene>("タイトルシーン");
	SceneManager::AddScene<ChoiceScene>("ゲーム選択シーン");
	SceneManager::AddScene<BattleMap01Scene>("バトルマップ01シーン");
	SceneManager::LoadScene("バトルマップ01シーン");

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
