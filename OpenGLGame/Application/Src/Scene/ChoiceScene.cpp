/**
* @file ChoiceScene.cpp
*/
#include "ChoiceScene.h"
#include "../ChoiceManager.h"
#include "../FadeOut.h"
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
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}

	// ガンダムを作成
	{
		auto titleGundam = objManager->CreateGameObject("TitleGundam");
		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}

	// ブラックオブジェクトを作成
	{
		auto blackObject = objManager->CreateGameObject("BlackObject");
		auto image = blackObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color(0, 0, 0, 0.7f);
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}

	// タイトルロゴを作成
	{
		auto titleLogo = objManager->CreateGameObject("TitleLogoA", Vector3(-400, 0, 0));
		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 0.9f;
	}

	// バトルボタンを作成
	{
		auto battleButton = objManager->CreateGameObject("BattleButton", Vector3(500, -200, 0));
		auto image = battleButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("BattleButton");
		image->size = image->texture->GetSize() * 1.3f;
		choiceManager->imgButtons.push_back(image);
	}

	// オプションボタンを作成
	{
		auto optionButton = objManager->CreateGameObject("OptionButton", Vector3(500, 0, 0));
		auto image = optionButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("OptionButton");
		image->size = image->texture->GetSize() * 1.3f;
		choiceManager->imgButtons.push_back(image);
	}

	// やめるボタンを作成
	{
		auto exitButton = objManager->CreateGameObject("ExitButton", Vector3(500, 200, 0));
		auto image = exitButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("ExitButton");
		image->size = image->texture->GetSize() * 1.3f;
		choiceManager->imgButtons.push_back(image);
	}

	// フェードオブジェクトを作成
	{
		auto fadeObject = objManager->CreateGameObject("FadeObjectA");
		auto image = fadeObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color::black;
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
		choiceManager->fadeOut = fadeObject->AddComponent<FadeOut>();
	}

	return false;
}

/**
* ゲーム選択シーンの更新
*/
void ChoiceScene::Update()
{
}

/**
* ゲーム選択シーンの終了
*/
void ChoiceScene::Finalize()
{
}
