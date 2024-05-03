/**
* @file Application.cpp
*/
#include "Application.h"
#include "TitleScene.h"
#include "MainScene.h"
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
	auto resouceManager = ResouceManager::GetInstance();

	// リソースの読み込み
	resouceManager->LoadGlTF("Gundam", "Application/Res/Gundam/Model/GundamGL.gltf");

	resouceManager->LoadTga("sky", "Application/Res/Map/sky2.tga");
	resouceManager->LoadTga("BoostbarBack", "Application/Res/UI/Battle/BoostbarBack.tga");
	resouceManager->LoadTga("Title", "Application/Res/UI/Title/Title.tga");

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
