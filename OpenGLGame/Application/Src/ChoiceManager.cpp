/**
* @file ChoiceManager.cpp
*/
#include "ChoiceManager.h"
#include "FadeOut.h"
using namespace FGEngine::InputSystem;
using namespace FGEngine::WindowSystem;

/**
* 最初に実行
*/
void ChoiceManager::Start()
{
	// リソースシステムを取得
	auto resManager = AssetManager::GetInstance();

	float baseX = -570;
	float spaceX = 100;

	// バトルボタンを作成
	{
		auto battleButton = Instantate("BattleButton", Vector3(baseX, -200, 0), Quaternion::identity);
		auto image = battleButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("BattleButton");
		image->size = image->texture->GetSize() * 1.3f;
		imgButtons.push_back(image);
	}

	// オプションボタンを作成
	{
		auto optionButton = Instantate("OptionButton", Vector3(baseX + spaceX, 0, 0), Quaternion::identity);
		auto image = optionButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("OptionButton");
		image->size = image->texture->GetSize() * 1.3f;
		imgButtons.push_back(image);
	}

	// やめるボタンを作成
	{
		auto exitButton = Instantate("ExitButton", Vector3(baseX + spaceX * 2, 200, 0), Quaternion::identity);
		auto image = exitButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("ExitButton");
		image->size = image->texture->GetSize() * 1.3f;
		imgButtons.push_back(image);
	}

	// フェードオブジェクトを作成
	{
		auto fadeObject = Instantate("FadeObjectA");
		fadeOut = fadeObject->AddComponent<FadeOut>();
	}
}

/**
* 毎フレーム実行
*/
void ChoiceManager::Update()
{

	// フェードアウトが設定されていなければ何もしない
	if (!fadeOut)
	{
		return;
	}

	// フェードアウトが終わったら
	if (fadeOut->IsFadeOut())
	{
		switch (choiceNum)
		{
		case (int)ChoiceManager::GameChoice::Battle:
			SceneManager::LoadScene("バトル設定シーン");
			break;
		case (int)ChoiceManager::GameChoice::Option:
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

	/**
	* Eneterを押したら選択を決定
	*/
	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		if (choiceNum == (int)ChoiceManager::GameChoice::Exit)
		{
			// ウィンドウを閉じる
			WindowManager::GetInstance()->WindowClose();
		}
		else
		{
			// それ以外ならフェードアウトを開始する
			fadeOut->FadeStart();
		}
	}


	// 選択を移動
	if (InputKey::GetKeyDown(KeyCode::DownArrow))
	{
		choiceNum++;
	}
	else if (InputKey::GetKeyDown(KeyCode::UpArrow))
	{
		choiceNum--;
	}
	choiceNum = Mathf::Clamp(choiceNum, (int)GameChoice::Battle, (int)GameChoice::Exit);

	for (int i = 0; i < imgButtons.size(); ++i)
	{
		// 選択されたら通常色
		if (i == choiceNum)
		{
			imgButtons[i]->color = Color::white;
		}
		else
		{
			// 選択されていなければ色を黒くする
			imgButtons[i]->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
		}
	}
}
