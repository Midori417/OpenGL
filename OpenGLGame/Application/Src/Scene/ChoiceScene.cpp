/**
* @file ChoiceScene.cpp
*/
#include "ChoiceScene.h"
#include "../ChoiceManager.h"
using namespace FGEngine::WindowSystem;
using namespace FGEngine::UI;

/**
* ゲーム選択シーンの初期化
*/
bool ChoiceScene::Initialize()
{
	// マネージャーを取得
	auto resManager = AssetManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// カメラの作成
	auto camera = CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
	auto cameraInfo = camera->AddComponent<Camera>();
	SetMainCameraInfo(cameraInfo);

	// 選択シーン管理マネージャーを作成
	auto choiceManagerObj = CreateGameObject("ChoiceManager");
	auto choiceManager = choiceManagerObj->AddComponent<ChoiceManager>();

	// タイトル背景を作成
	{
		auto titleBack = CreateGameObject("TitleBack");
		auto image = titleBack->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleBack");
		image->size = winManager->GetWindowSize();
	}

	// ガンダムを作成
	{
		auto titleGundam = CreateGameObject("TitleGundam");
		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = winManager->GetWindowSize();
	}

	// ブラックオブジェクトを作成
	{
		auto blackObject = CreateGameObject("BlackObject");
		auto image = blackObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color(0, 0, 0, 0.7f);
		image->size = winManager->GetWindowSize();
	}

	// タイトルロゴを作成
	{
		auto titleLogo = CreateGameObject("TitleLogoA", Vector3(400, 0, 0), Quaternion::identity);
		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 0.9f;
	}

	return false;
}
