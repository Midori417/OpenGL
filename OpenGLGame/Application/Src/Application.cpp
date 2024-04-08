/**
* @file Application.cpp
*/
#include "Application.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;
using namespace FGEngine::ResouceSystem;

#include "TitleScene.h"
#include "MainScene.h"

/**
* アプリケーションの初期化
*
* @return 0		正常に終了
* @return 0以外 初期化に失敗
*/
int Application::Initialize()
{
	auto resouceManager = ResouceManager::GetInstance();
	// OBJファイルを読み込む

	// 画像読み込み
	resouceManager->LoadTga("sky", "Application/Res/Map/sky2.tga");

	// シーンの登録
	SceneManager::AddScene<TitleScene>("タイトルシーン");
	SceneManager::AddScene<MainScene>("メインシーン");

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
