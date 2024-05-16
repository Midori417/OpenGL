/**
* @file Player.cpp
*/
#include "PlayerControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "ImageBlinking.h"
#include "ImageNum.h"
using namespace FGEngine::InputSystem;
using namespace FGEngine::ResouceSystem;

/**
* 最初に実行
*/
void PlayerControl::Start()
{
	// リソースマネージャーを取得
	auto resManager = ResouceManager::GetInstance();

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
						auto weaponIcon = Instantate(x->name, Vector3(830, 410, 0));
						auto image= weaponIcon->AddComponent<Image>();
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
		}
		// 相手チームの体力バーを作成
		{
			auto teumEnemyBar = Instantate("TeumEnemyBar", Vector3(-620, -420, 0));
			imgEnemyTeumHpBar = teumEnemyBar->AddComponent<Image>();
			imgEnemyTeumHpBar->texture = resManager->GetTexture("TeumEnemyHpBar");
			imgEnemyTeumHpBar->size = imgEnemyTeumHpBar->texture->GetSize() * 1.2f;

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
		imgEnemyTeumHpBar->SetEnable(false);
		imgTimer->SetEnable(false);
	}

	// カメラに自身のMSを設定
	lookOnCamera->SetMsTransform(myMs->GetTransform().get());

	// カメラにターゲットを設定
	lookOnCamera->SelectTarget(otherOwner->myMs->GetTransform().get());

	// プレイヤーにカメラ設定
	myMs->SetCamera(lookOnCamera->GetTransform().get());
}

/**
* 毎フレーム実行
*/
void PlayerControl::Update()
{
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
		imgEnemyTeumHpBar->SetEnable(true);
		imgTimer->SetEnable(true);
	}

	// ターゲットのMSを取得
	auto targetMs = otherOwner->myMs;
	myMs->SetTargetMS(targetMs.get());

	// 距離を求める
	if (targetMs)
	{
		distance = Vector3::Distance(targetMs->GetTransform()->position, myMs->GetTransform()->position);
	}
	// Ms更新
	MsUpdate();

	// UI更新
	UIUpdate();
}

void PlayerControl::LateUpdate()
{

}

/**
* MSの更新
*/
void PlayerControl::MsUpdate()
{
	if (!myMs)
	{
		return;
	}
	// 移動
	Vector2 moveAxis = Vector2(InputManager::GetAxis(Axis::Horizontal), InputManager::GetAxis(Axis::Vertical));
	myMs->Move(moveAxis);

	// ジャンプ
	bool jumpKey = InputKey::GetKey(KeyCode::Space);
	myMs->Jump(jumpKey, moveAxis);

	// ダッシュ
	bool dashKey = InputKey::GetKey(KeyCode::LeftShift);
	myMs->Dash(dashKey, moveAxis);

	// 攻撃1
	bool attackKey = InputMouse::GetMouseButton(MouseButton::LeftButton);
	myMs->Attack1(attackKey);
}

/**
* UIの更新
*/
void PlayerControl::UIUpdate()
{
	// MyMs
	{
		if (myMs)
		{
			// Hp
			if (inMyMsHp)
			{
				inMyMsHp->num = myMs->GetHP();
			}

			// BoostBar
			if (myMs->GetBoostEnergy() > 0)
			{
				imgBoostBar->fillAmout = myMs->GetBoostEnergy();
				imgBoostBarOverHeat->SetEnable(false);
			}
			else if (myMs->GetBoostEnergy() <= 0)
			{
				imgBoostBarOverHeat->SetEnable(true);
			}

			// WeponAmo
			for (int i = 0; i < inWeaponAmos.size(); ++i)
			{
				inWeaponAmos[i]->num = myMs->numWeapons[i]->amo;
			}
			// WeaponBar
			for (int i = 0; i < imgWeaponBars.size(); ++i)
			{
				float amo = static_cast<float>(myMs->numWeapons[i]->amo);
				float amoMax = static_cast<float>(myMs->numWeapons[i]->amoMax);
				imgWeaponBars[i]->fillAmout = Mathf::Clamp01((amoMax - (amoMax - amo)) / amoMax);
			}
		}

	}

	auto targetMs = otherOwner->myMs;
	if (myMs && targetMs)
	{
		// ターゲットマークの処理
		if (imgTargetMark)
		{
			// 近ければ小さくし、遠ければ大きくする
			imgTargetMark->size = Vector2(Mathf::Clamp(distance, 100.0f, 200.0f));

			// 距離によってテクスチャを変える
			if (distance <= myMs->proximityDistance)
			{
				imgTargetMark->texture = texTargetMark03;
			}
			else if (distance <= myMs->redLookDistace)
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
