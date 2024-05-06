/**
* @file GameChoiceScene.cpp
*/
#include "GameChoiceScene.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;
using namespace FGEngine::UI;

/**
* ゲーム選択シーンの初期化
*/
bool GameChiecScene::Initialize()
{
	// マネージャーを取得
	auto objManager = ObjectManager::GetInstance();
	auto resManager = ResouceManager::GetInstance();

	// リソースの読み込み
	resManager->LoadTga("BattleButton", "Application/Res/UI/Title/BattleButton.tga");
	resManager->LoadTga("OptionButton", "Application/Res/UI/Title/OptionButton.tga");
	resManager->LoadTga("ExitButton", "Application/Res/UI/Title/ExitButton.tga");


	// カメラの作成
	auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);

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
		imgButtons.push_back(image);
	}

	// オプションボタンを作成
	{
		auto optionButton = objManager->CreateGameObject("OptionButton", Vector3(500, 0, 0));
		auto image = optionButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("OptionButton");
		image->size = image->texture->GetSize() * 1.3f;
		imgButtons.push_back(image);
	}

	// やめるボタンを作成
	{
		auto exitButton = objManager->CreateGameObject("ExitButton", Vector3(500, 200, 0));
		auto image = exitButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("ExitButton");
		image->size = image->texture->GetSize() * 1.3f;
		imgButtons.push_back(image);
	}

	return false;
}

/**
* ゲーム選択シーンの更新
*/
void GameChiecScene::Update()
{
	// 選択を移動
	if (InputKey::GetKeyDown(KeyCode::DownArrow))
	{
		choiceNum++;
		choiceNum = Mathf::Clamp(choiceNum, (int)Choice::Battle, (int)Choice::Exit);
	}
	else if (InputKey::GetKeyDown(KeyCode::UpArrow))
	{
		choiceNum--;
		choiceNum = Mathf::Clamp(choiceNum, (int)Choice::Battle, (int)Choice::Exit);
	}

	for (int i = 0; i < imgButtons.size(); ++i)
	{
		// 選択されてたら色を暗くする
		if (i == choiceNum)
		{
			imgButtons[i]->color = Color::white;
		}
		else
		{
			imgButtons[i]->color = Color(0.7f, 0.7f, 0.7f, 1.0f);
		}
	}

}

/**
* ゲーム選択シーンの終了
*/
void GameChiecScene::Finalize()
{
}
