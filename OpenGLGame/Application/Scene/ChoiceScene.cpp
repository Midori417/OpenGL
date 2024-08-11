/**
* @file ChoiceScene.cpp
*/
#include "ChoiceScene.h"
#include "../ChoiceManager.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::WindowSystem;
using namespace FGEngine::UI;

/**
* ゲーム選択シーンの初期化
*/
bool ChoiceScene::Initialize()
{
	// マネージャーを取得
	auto objManager = ObjectManager::GetInstance();
	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// カメラの作成
	auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);

	// 選択シーン管理マネージャーを作成
	auto choiceManagerObj = objManager->CreateGameObject("ChoiceManager");
	auto choiceManager = choiceManagerObj->AddComponent<ChoiceManager>();

	// タイトル背景を作成
	{
		auto titleBack = objManager->CreateGameObject("TitleBack");
		auto image = titleBack->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleBack");
		image->size = winManager->GetWindowSize();
	}

	// ガンダムを作成
	{
		auto titleGundam = objManager->CreateGameObject("TitleGundam");
		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = winManager->GetWindowSize();
	}

	// ブラックオブジェクトを作成
	{
		auto blackObject = objManager->CreateGameObject("BlackObject");
		auto image = blackObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color(0, 0, 0, 0.7f);
		image->size = winManager->GetWindowSize();
	}

	// タイトルロゴを作成
	{
		auto titleLogo = objManager->CreateGameObject("TitleLogoA", Vector3(400, 0, 0));
		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 0.9f;
	}

	return false;
}
