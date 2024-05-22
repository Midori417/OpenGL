/**
* @file BattleSettingManager.cpp
*/
#include "BattleSettingManager.h"
#include "FadeOut.h"
using namespace FGEngine::UI;
using namespace FGEngine::SceneSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;
using namespace FGEngine::WindowSystem;

/**
* 生成時に実行
*/
void BattleSettingManager::Awake()
{
	// マネージャを取得
	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// バトル設定画面を作成
	{
		auto battleSetting = Instantate("BattleSetting");
		auto image = battleSetting->AddComponent<Image>();
		image->texture = resManager->GetTexture("BattleSetting");
		image->size = winManager->GetWindowSize();
	}

	// フェードオブジェクトを作成
	{
		auto fadeObject = Instantate("FadeObjectB");
		fadeOut = fadeObject->AddComponent<FadeOut>();
	}
}

/**
* 毎フレーム実行
*/
void BattleSettingManager::Update()
{
	// フェードアウトが終わったら
	if (fadeOut->IsFadeOut())
	{
		SceneManager::LoadScene("バトルマップ01シーン");
	}

	/**
	* フェードが開始したら何もしない
	*/
	if (fadeOut->IsFadeStart())
	{
		return;
	}

	// Eneter(決定ボタン)をフェード開始
	if (InputKey::GetKey(KeyCode::Enter))
	{
		fadeOut->FadeStart();
	}
}
