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

	// カメラを作成
	GameObjectPtr camer = Create(CreateObject::Camera);

	// 選択シーン管理マネージャーを作成
	GameObjectPtr choiceManagerObject = Create(CreateObject::Empty);
	choiceManagerObject->name = "ChoiceManager";
	auto choiceManager = choiceManagerObject->AddComponent<ChoiceManager>();

	// タイトル背景を作成
	{
		GameObjectPtr titleBack = Create(CreateObject::Empty);
		titleBack->name = "TitleBack";

		auto image = titleBack->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleBack");
		image->size = winManager->GetWindowSize();
	}

	// ガンダムを作成
	{
		GameObjectPtr titleGundam = Create(CreateObject::Empty);
		titleGundam->name = "TitleGundam";

		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = winManager->GetWindowSize();
	}

	// 背景を少し暗くしたいので薄い黒いオブジェクトを設置
	{
		GameObjectPtr blackObject = Create(CreateObject::Empty);
		blackObject->name = "BlackObject";

		auto image = blackObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color(0, 0, 0, 0.7f);
		image->size = winManager->GetWindowSize();
	}

	// タイトルロゴを作成
	{
		GameObjectPtr titleLogo = Create(CreateObject::Empty);
		titleLogo->name = "TitleLogoA";
		titleLogo->GetTransform()->position.x = 400;

		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 0.9f;
	}

	return false;
}
