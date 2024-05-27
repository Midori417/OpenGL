/**
* @file HumanControl.cpp
*/
#include "HumanControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "ImageBlinking.h"
#include "ImageNum.h"
#include "Global.h"
using namespace FGEngine::InputSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::WindowSystem;

/**
* 最初に実行
*/
void HumanControl::Start()
{
	// 必要なマネージャーを取得
	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// 初期する
	Initialize();

	// UIの作成
	{
		// 自身の情報背景を作成
		{
			auto myInfoBack = Instantate("MysInfo", Vector3(-725, 330, 0));
			imgMyInfoBack = myInfoBack->AddComponent<Image>();
			imgMyInfoBack->texture = resManager->GetTexture("PlayerInfo");
			imgMyInfoBack->size = Vector2(imgMyInfoBack->texture->GetWidth() * 1.4f,
				imgMyInfoBack->texture->GetHeight() * 1.1f);
		}
		// 自身の機体の体力を作成
		{
			auto myMsHp = Instantate("MyMsHp", Vector3(-670, 280, 0));
			inMyMsHp = myMsHp->AddComponent<ImageNum>();
			inMyMsHp->space = -70;
			inMyMsHp->scale = 1.35f;
		}
		// ブーストバーの背景を作成
		{
			auto boostBarBack = Instantate("BoostBarBack", Vector3(250, 450, 0));
			imgBoostBarBack = boostBarBack->AddComponent<Image>();
			imgBoostBarBack->texture = resManager->GetTexture("BoostBarBack");
			imgBoostBarBack->size = imgBoostBarBack->texture->GetSize() * 1.2f;
		}
		// ブーストバーのオーバーヒートを作成
		{
			auto boostBarOverHeat = Instantate("BoosetBarOverHeat", Vector3(245, 435, 0));
			imgBoostBarOverHeat = boostBarOverHeat->AddComponent<Image>();
			imgBoostBarOverHeat->texture = resManager->GetTexture("BoostBarOVERHEAT");
			imgBoostBarOverHeat->size = imgBoostBarOverHeat->texture->GetSize() * 1.2f;
			// 点滅コンポーネント
			ibBoostBarOverHeat = boostBarOverHeat->AddComponent<ImageBlinking>();
			ibBoostBarOverHeat->image = imgBoostBarOverHeat;
			ibBoostBarOverHeat->speed = 5.0f;
		}
		// ブーストバーを作成
		{
			auto boostBar = Instantate("BoostBar", Vector3(245, 435, 0));
			imgBoostBar = boostBar->AddComponent<Image>();
			imgBoostBar->texture = resManager->GetTexture("BoostBar");
			imgBoostBar->size = imgBoostBar->texture->GetSize() * 1.2f;
			imgBoostBar->fillAmout = 0.5f;
		}
		// 覚醒バーの背景を作成
		{
			auto burstBarBack = Instantate("burstBarBack", Vector3(-250, 450, 0));
			imgBurstBarBack = burstBarBack->AddComponent<Image>();
			imgBurstBarBack->texture = resManager->GetTexture("BurstBarBack");
			imgBurstBarBack->size = imgBurstBarBack->texture->GetSize() * 1.2f;
		}
		// 覚醒バーを作成
		{
			auto burstBar = Instantate("burstBar", Vector3(-253, 428, 0));
			imgBurstBar = burstBar->AddComponent<Image>();
			imgBurstBar->texture = resManager->GetTexture("BurstBar");
			imgBurstBar->size = imgBurstBar->texture->GetSize() * 1.2f;
			imgBurstBar->fillType = Image::FillType::HorizontalInverse;
			imgBurstBar->fillAmout = 0.5f;
		}
		// 武器UI
		{
			// 自身のMSの武器が空なら何もしない
			if (!myMs->numWeapons.empty())
			{
				// サイズを予約
				imgWeaponBacks.reserve(myMs->numWeapons.size());
				int i = 0;
				for (auto x : myMs->numWeapons)
				{
					// 武器アイコンの背景
					{
						auto weaponBack = Instantate("WeaponBack" + std::to_string(i), Vector3(765.0f, 400.0f + (-160.0f * i), 0));
						auto image = weaponBack->AddComponent<Image>();
						image->texture = resManager->GetTexture("WeaponBack");
						image->size = image->texture->GetSize() * 1.3f;
						imgWeaponBacks.push_back(image);
					}
					// 武器の残弾
					{
						auto weaponAmo = Instantate("WeapnAmo" + std::to_string(i), Vector3(715.0f, 410.0f + (-160.0f * i), 0));
						auto imageNum = weaponAmo->AddComponent<ImageNum>();
						imageNum->scale = 0.8f;
						imageNum->space = -45;
						inWeaponAmos.push_back(imageNum);
					}
					// 武器の残弾バー
					{
						auto weaponAmoBar = Instantate("WeapnAmoBar" + std::to_string(i), Vector3(665.0f, 448.0f + (-160 * i), 0));
						auto image = weaponAmoBar->AddComponent<Image>();
						image->texture = resManager->GetTexture("WeaponBar");
						image->size = image->texture->GetSize() * 1.3f;
						imgWeaponBars.push_back(image);
					}
					// 武器のアイコン
					{
						auto weaponIcon = Instantate(x->name, Vector3(830, 410 + (-160.0f * i), 0));
						auto image = weaponIcon->AddComponent<Image>();
						image->texture = x->iconTexture;
						image->size = image->texture->GetSize() * 1.3f;
						imgWeapnIcons.push_back(image);
					}
					i++;
				}
			}
		}
		// ターゲットマークを作成
		{
			// ターゲットマークのテクスチャを取得
			texTargetMark01 = resManager->GetTexture("TargetMark01");
			texTargetMark02 = resManager->GetTexture("TargetMark02");
			texTargetMark03 = resManager->GetTexture("TargetMark03");

			auto targetMark = Instantate("TargetMark");
			imgTargetMark = targetMark->AddComponent<Image>();
			imgTargetMark->texture = texTargetMark01;
			imgTargetMark->size = imgTargetMark->texture->GetSize();
		}
		// ターゲットの情報を作成
		{
			auto targetMark = Instantate("TargetMsInfo", Vector3(120, -70, 0));
			imgTargetInfo = targetMark->AddComponent<Image>();
			imgTargetInfo->texture = resManager->GetTexture("TargetMsInfo");
			imgTargetInfo->size = imgTargetInfo->texture->GetSize();
		}
		// ターゲットの体力バーを作成
		{
			auto targetHP = Instantate("TargetMsHpBar", Vector3(162, -75, 0));
			imgTargetHPBar = targetHP->AddComponent<Image>();
			imgTargetHPBar->texture = resManager->GetTexture("TargetMsHpBar");
			imgTargetHPBar->size = imgTargetHPBar->texture->GetSize();
		}
		// 自チームの体力バーを作成
		{
			auto myTeumHpBar = Instantate("TeumHpBar", Vector3(-640, -465, 0));
			imgMyTeumHpBar = myTeumHpBar->AddComponent<Image>();
			imgMyTeumHpBar->texture = resManager->GetTexture("TeumHpBar");
			imgMyTeumHpBar->size = imgMyTeumHpBar->texture->GetSize() * 1.2f;

			float max = static_cast<float>(teumMaxHp);
			float hp = static_cast<float>(MyTeumHp());
			imgMyTeumHpBar->fillAmout = (max - (max - hp)) / max;
		}
		// 相手チームの体力バーを作成
		{
			auto otherTeumHpBar = Instantate("OtherTeumHpBar", Vector3(-620, -420, 0));
			imgOtherTeumHpBar = otherTeumHpBar->AddComponent<Image>();
			imgOtherTeumHpBar->texture = resManager->GetTexture("TeumEnemyHpBar");
			imgOtherTeumHpBar->size = imgOtherTeumHpBar->texture->GetSize() * 1.2f;

			float max = static_cast<float>(teumMaxHp);
			float hp = static_cast<float>(OtherTeumHp());
			imgOtherTeumHpBar->fillAmout = (max - (max - hp)) / max;
		}
		// チーム体力フレームを作成
		{
			auto teumHp = Instantate("TeumHpFrame", Vector3(-635, -430, 0));
			imgTeumHpFrame = teumHp->AddComponent<Image>();
			imgTeumHpFrame->texture = resManager->GetTexture("TeumFrame");
			imgTeumHpFrame->size = imgTeumHpFrame->texture->GetSize() * 1.2f;
		}
		// 時間(張りぼて)
		{
			auto timer = Instantate("Timer", Vector3(800, -450, 0));
			imgTimer = timer->AddComponent<Image>();
			imgTimer->texture = resManager->GetTexture("Timer");
			imgTimer->size = imgTimer->texture->GetSize() * 1.2f;
		}
		// WINを作成
		{
			auto win = Instantate("Win");
			imgWin = win->AddComponent<Image>();
			imgWin->texture = resManager->GetTexture("Win");
			imgWin->size = winManager->GetWindowSize();
		}
		// Loseを作成
		{
			auto lose = Instantate("Lose");
			imgLose = lose->AddComponent<Image>();
			imgLose->texture = resManager->GetTexture("Lose");
			imgLose->size = winManager->GetWindowSize();
		}
	}
	// UIを非表示にする
	{
		imgMyInfoBack->SetEnable(false);
		inMyMsHp->SetEnable(false);
		imgBoostBarBack->SetEnable(false);
		imgBoostBar->SetEnable(false);
		imgBoostBarOverHeat->SetEnable(false);
		imgBurstBarBack->SetEnable(false);
		imgBurstBar->SetEnable(false);
		for (auto x : imgWeaponBacks)
		{
			x->SetEnable(false);
		}
		for (auto x : inWeaponAmos)
		{
			x->SetEnable(false);
		}
		for (auto x : imgWeaponBars)
		{
			x->SetEnable(false);
		}
		for (auto x : imgWeapnIcons)
		{
			x->SetEnable(false);
		}
		imgTargetMark->SetEnable(false);
		imgTargetInfo->SetEnable(false);
		imgTargetHPBar->SetEnable(false);
		imgTeumHpFrame->SetEnable(false);
		imgMyTeumHpBar->SetEnable(false);
		imgOtherTeumHpBar->SetEnable(false);
		imgTimer->SetEnable(false);
		imgWin->SetEnable(false);
		imgLose->SetEnable(false);
	}
}

/**
* 毎フレーム実行
*/
void HumanControl::Update()
{
	// スタート呼び出されていなければ何もしない
	if (!isStart)
	{
		return;
	}
	else
	{
		// UIを表示
		imgMyInfoBack->SetEnable(true);
		inMyMsHp->SetEnable(true);
		imgBoostBarBack->SetEnable(true);
		imgBoostBar->SetEnable(true);
		imgBurstBarBack->SetEnable(true);
		imgBurstBar->SetEnable(true);
		for (auto x : imgWeaponBacks)
		{
			x->SetEnable(true);
		}
		for (auto x : inWeaponAmos)
		{
			x->SetEnable(true);
		}
		for (auto x : imgWeaponBars)
		{
			x->SetEnable(true);
		}
		for (auto x : imgWeapnIcons)
		{
			x->SetEnable(true);
		}
		imgTargetMark->SetEnable(true);
		imgTargetInfo->SetEnable(true);
		imgTargetHPBar->SetEnable(true);
		imgTeumHpFrame->SetEnable(true);
		imgMyTeumHpBar->SetEnable(true);;
		imgOtherTeumHpBar->SetEnable(true);
		imgTimer->SetEnable(true);
	}

	// 自身の機体が死んだら
	if (myMs->IsDeath())
	{
		if (!isMsDeath)
		{
			// 自チームのHpを減らす
			TeumHpSud();
			// Msの操作をできないようにする
			isMsControl = false;
			isMsDeath = true;
			responTimer = 0;
		}
		// チーム体力が0以上だったら復活させる
		if (MyTeumHp() > 0)
		{
			responTimer += Time::DeltaTime();
			if (responTimer > responTime)
			{
				int index = Random::Range(0, (int)responPoss.size() - 1);
				// 自チームの体力がコスト以上あればそのままの体力で復活
				if (MyTeumHp() >= myMs->GetCost())
				{
					myMs->Respon(responPoss[index], 1);
				}
				// 自チームの体力がコスト以下ならば体力カットして復活
				else if (MyTeumHp() < myMs->GetCost())
				{
					float hp = static_cast<float>(MyTeumHp());
					float cost = static_cast<float>(myMs->GetCost());
					float hpCut = ((cost - hp) / cost);
					myMs->Respon(responPoss[index], hpCut);
				}
				// MSの操作を許可
				isMsControl = true;
				isMsDeath = false;
			}
		}
	}

	// ゲーム入力
	GameInputUpdate();

	// テストターゲットを変更
	if (gameInput->targetChange1Btn && otherTeumOwner[0] != nullptr)
	{
		targetOwner = otherTeumOwner[0];
		// カメラと機体にターゲットを持たせる
		myMs->SetTargetMS(targetOwner->myMs.get());
		myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
	}
	else if(gameInput->targetChange2Btn && otherTeumOwner[1] != nullptr)
	{
		targetOwner = otherTeumOwner[1];
		// カメラと機体にターゲットを持たせる
		myMs->SetTargetMS(targetOwner->myMs.get());
		myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
	}


	// UI更新
	UIUpdate();
}

/**
* ゲーム入力を更新
*/
void HumanControl::GameInputUpdate()
{
	// MSが死んでいれか、操作が許可されていなければ何もしない
	if (myMs->IsDeath() || !isMsControl)
	{
		return;
	}

	// ゲーム入力
	gameInput->moveAxis = Vector2(InputManager::GetAxis(Axis::Horizontal), InputManager::GetAxis(Axis::Vertical));
	gameInput->jumpBtn = InputKey::GetKey(KeyCode::Space);
	gameInput->dashBtn = InputKey::GetKey(KeyCode::LeftShift);
	gameInput->action1Btn = InputMouse::GetMouseButton(MouseButton::LeftButton);
	gameInput->action2Btn = InputKey::GetKey(KeyCode::E);
	gameInput->targetChange1Btn = InputKey::GetKey(KeyCode::Alpha1);
	gameInput->targetChange2Btn = InputKey::GetKey(KeyCode::Alpha2);
}

/**
* UIの更新
*/
void HumanControl::UIUpdate()
{
	// 自チーム体力の設定
	if (imgMyTeumHpBar)
	{
		float max = static_cast<float>(teumMaxHp);
		float hp = static_cast<float>(MyTeumHp());
		imgMyTeumHpBar->fillAmout = (max - (max - hp)) / max;
	}
	// 相手チームの体力の設定
	if (imgOtherTeumHpBar)
	{
		float max = static_cast<float>(teumMaxHp);
		float hp = static_cast<float>(OtherTeumHp());
		imgOtherTeumHpBar->fillAmout = (max - (max - hp)) / max;
	}


	// 自分の機体の体力を設定
	if (inMyMsHp)
	{
		inMyMsHp->num = myMs->GetHP();
	}
	// ブーストゲージを設定
	if (imgBoostBar && imgBoostBarOverHeat)
	{
		if (myMs->GetBoostEnergy() > 0)
		{
			imgBoostBar->fillAmout = myMs->GetBoostEnergy();
			imgBoostBarOverHeat->SetEnable(false);
		}
		else if (myMs->GetBoostEnergy() <= 0)
		{
			imgBoostBarOverHeat->SetEnable(true);
		}
	}
	// 武装の残弾を設定
	for (int i = 0; i < inWeaponAmos.size(); ++i)
	{
		inWeaponAmos[i]->num = static_cast<int>(myMs->numWeapons[i]->amo);
	}
	// 武装の残弾ゲージを設定
	for (int i = 0; i < imgWeaponBars.size(); ++i)
	{
		float amo = (myMs->numWeapons[i]->amo);
		float amoMax = (myMs->numWeapons[i]->amoMax);
		imgWeaponBars[i]->fillAmout = Mathf::Clamp01((amoMax - (amoMax - amo)) / amoMax);
	}

	if (targetOwner)
	{
		auto targetMs = targetOwner->myMs;
		if (!targetMs->IsDeath())
		{
			// ターゲットマークの処理
			if (imgTargetMark)
			{
				// 近ければ小さくし、遠ければ大きくする
				imgTargetMark->size = Vector2(Mathf::Clamp(GetDistance(), 100.0f, 200.0f));

				// 距離によってテクスチャを変える
				if (GetDistance() <= myMs->proximityDistance)
				{
					imgTargetMark->texture = texTargetMark03;
				}
				else if (GetDistance() <= myMs->redLookDistace)
				{
					imgTargetMark->texture = texTargetMark02;
				}
				else
				{
					imgTargetMark->texture = texTargetMark01;
				}
			}
			// ターゲットHPの処理
			if (imgTargetHPBar)
			{
				imgTargetHPBar->fillAmout = targetMs->GetHP01();
			}

		}
	}
}


/**
* 終了処理
*/
void HumanControl::Finish(VictoryState victoryState)
{
	// UIを非表示にする
	{
		imgMyInfoBack->SetEnable(false);
		inMyMsHp->Stop();
		imgBoostBarBack->SetEnable(false);
		imgBoostBar->SetEnable(false);
		imgBoostBarOverHeat->SetEnable(false);
		imgBurstBarBack->SetEnable(false);
		imgBurstBar->SetEnable(false);
		for (auto x : imgWeaponBacks)
		{
			x->SetEnable(false);
		}
		for (auto x : inWeaponAmos)
		{
			x->Stop();
		}
		for (auto x : imgWeaponBars)
		{
			x->SetEnable(false);
		}
		for (auto x : imgWeapnIcons)
		{
			x->SetEnable(false);
		}
		imgTargetMark->SetEnable(false);
		imgTargetInfo->SetEnable(false);
		imgTargetHPBar->SetEnable(false);
		imgTeumHpFrame->SetEnable(false);
		imgMyTeumHpBar->SetEnable(false);
		imgOtherTeumHpBar->SetEnable(false);
		imgTimer->SetEnable(false);
	}

	// 勝敗によってUIを表示する
	switch (victoryState)
	{
	case VictoryState::None:
		break;
	case VictoryState::Win:
		imgWin->SetEnable(true);
		break;
	case VictoryState::Lose:
		imgLose->SetEnable(true);
		break;
	case VictoryState::Drow:
		break;
	}
}