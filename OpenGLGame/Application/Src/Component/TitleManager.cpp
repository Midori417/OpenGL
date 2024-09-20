/**
* @file TitleManager.cpp
*/
#include "TitleManager.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/CreateGameObjectType.h"
#include "FGEngine/Debug.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Scene/SceneManager.h"

#include "FadeOut.h"
#include "../GameSoundName.h"

/**
* Updateが始まる前に一度実行
*/
void TitleManager::Start()
{
	// アセットマネージャーを取得
	auto assetManager = AssetManager::GetInstance();

	// フェードオブジェクトを作成
	{
		auto obj = Instantate(assetManager->GetGameObject("FadeObject"));
		fadeOut = obj->GetComponent<FadeOut>();
	}

	// 決定音を鳴らすためにサウンドコンポーネントを追加
	audioSource = OwnerObject()->AddComponent<AudioSource>();
	audioSource->SetSoundFilename(GameSound::select);
}

/**
* 毎フレーム実行
*/
void TitleManager::Update()
{
	if (!fadeOut)
	{
		LOG_ERROR("フェードオブジェクトが存在しません");
		return;
	}

	// フェードが終了したらシーンを移動する
	if (fadeOut->IsFadeOut())
	{
		SceneManager::LoadScene("SelectScene");
	}

	// フェードが始まっていたらここから下の処理は実行しない
	if (fadeOut->IsFadeStart())
	{
		return;
	}

	// Enterキーの入力があればフェードを開始する
	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		audioSource->Play();
		fadeOut->FadeStart();
	}
}
