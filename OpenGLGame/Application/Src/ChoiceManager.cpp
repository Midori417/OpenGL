/**
* @file ChoiceManager.cpp
*/
#include "ChoiceManager.h"
using namespace FGEngine::InputSystem;
using namespace FGEngine::WindowSystem;
using namespace FGEngine::SceneSystem;
#include "FadeOut.h"

/**
* 最初に実行
*/
void ChoiceManager::Start()
{

}

/**
* 毎フレーム実行
*/
void ChoiceManager::Update()
{

	if (fadeOut)
	{
		if (fadeOut->IsFadeOut())
		{
			SceneManager::LoadScene("バトルマップ01シーン");
		}
	}

	/**
	* フェードが開始したら何もしない
	*/
	if (isFadeStart)
	{
		return;
	}

	// 選択を移動
	if (InputKey::GetKeyDown(KeyCode::DownArrow))
	{
		choiceNum++;
		choiceNum = Mathf::Clamp(choiceNum, (int)GameChoice::Battle, (int)GameChoice::Exit);
	}
	else if (InputKey::GetKeyDown(KeyCode::UpArrow))
	{
		choiceNum--;
		choiceNum = Mathf::Clamp(choiceNum, (int)GameChoice::Battle, (int)GameChoice::Exit);
	}

	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		switch (choiceNum)
		{
		case (int)ChoiceManager::GameChoice::Battle:
			isFadeStart = true;
			if (fadeOut)
			{
				fadeOut->isStart = true;
			}
			break;
		case (int)ChoiceManager::GameChoice::Option:
			break;
		case (int)ChoiceManager::GameChoice::Exit:
			// ウィンドウを閉じる
			WindowManager::GetInstance()->WindowClose();
			break;
		}
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
			imgButtons[i]->color = Color(0.5f, 0.5f, 0.5f, 1.0f);
		}
	}
}
