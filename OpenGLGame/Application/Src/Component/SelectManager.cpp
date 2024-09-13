/**
* @file SelectManager.cpp
*/
#include "SelectManager.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/CreateGameObjectType.h"
#include "FGEngine/Debug.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Component/AudioSource.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Scene/SceneManager.h"
#include "FGEngine/Input/InputKey.h"
#include "FGEngine/Window/WindowManager.h"
#include "FGEngine/Math/Mathf.h"

#include "FadeOut.h"
#include "../GameSoundName.h"

/**
* Updateが始まる前に一度実行
*/
void SelectManager::Start()
{
	// アセットマネージャーを取得
	auto assetManager = AssetManager::GetInstance();

	// UIの基準x座標
	const float baseX = -570;
	// 空ける距離
	const float spaceX = 100;

	// バトルボタンを作成
	{
		GameObjectPtr button = Instantate(CreateObjectType::Empty);
		button->name = "BattleButton";
		button->GetTransform()->position = Vector3(baseX, -200, 0);

		ImagePtr image = button->AddComponent<Image>();
		image->texture = assetManager->GetTexture("BattleButton");
		image->size = image->texture->GetSize() * 1.3f;

		imgButtons.push_back(image);
	}

	// やめるボタンを作成
	{
		GameObjectPtr button = Instantate(CreateObjectType::Empty);
		button->name = "ExitButton";
		button->GetTransform()->position = Vector3(baseX + spaceX * 2, 200, 0);

		ImagePtr image = button->AddComponent<Image>();
		image->texture = assetManager->GetTexture("ExitButton");
		image->size = image->texture->GetSize() * 1.3f;

		imgButtons.push_back(image);
	}

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
void SelectManager::Update()
{
	if (!fadeOut)
	{
		LOG_ERROR("フェードオブジェクトが存在しません");
		return;
	}

	// フェードアウトが終わったら現在選択されている項目を実行する
	// 後々オプションを追加したいのでスイッチ文にして拡張性を持たせる
	if (fadeOut->IsFadeOut())
	{
		switch (selectNum)
		{
		case Select::Battle:
			SceneManager::LoadScene("BattleSettingScene");
			break;
		}
	}

	// フェードが始まっていたらここから下の処理は実行しない
	if (fadeOut->IsFadeStart())
	{
		return;
	}

	// Enterキーの入力があればフェードを開始する
	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		// Exitが選択されていたらウィンドウを閉じる
		// それ以外が選択されていたらフェードを開始する
		if (selectNum == Select::Exit)
		{
			WindowManager::WindowClose();
		}
		else
		{
			audioSource->Play();
			fadeOut->FadeStart();
		}
	}

	// 選択項目の切り替え
	if (InputKey::GetKeyDown(KeyCode::DownArrow))
	{
		selectNum++;
	}
	else if (InputKey::GetKeyDown(KeyCode::UpArrow))
	{
		selectNum--;
	}
	// 選択項目を超えないように値を補正する
	selectNum = Mathf::Clamp(selectNum, Select::Battle, Select::Exit);

	// 選択、未選択時のボタンの色を設定
	for (int i = 0; i < imgButtons.size(); ++i)
	{
		ImagePtr image = imgButtons[i];
		// 選択されている項目なら通常色
		if (i == selectNum)
		{
			image->color = Color::white;
		}
		// 未選択なら少し暗めにする
		else
		{
			image->color = noSelectColor;
		}
	}

}
