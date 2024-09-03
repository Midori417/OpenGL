/**
* @file TitleManager.cpp
*/
#include "TitleManager.h"
#include "FadeOut.h"

/**
* 最初に実行
*/
void TitleManager::Start()
{
	// フェードオブジェクトを作成
	{
		auto fadeObject = Instantate("FadeObject");
		fadeOut = fadeObject->AddComponent<FadeOut>();
	}

}

/**
* 毎フレーム実行
*/
void TitleManager::Update()
{
	// フェードが終了したらシーン移動
	if (fadeOut->IsFadeOut())
	{
		SceneManager::LoadScene("ゲーム選択シーン");
	}

	// 何かしらの入力があればフェードを開始させる
	if (InputKey::AnyKey() && !fadeOut->IsFadeStart())
	{
		fadeOut->FadeStart();
	}

}
