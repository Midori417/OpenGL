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
	auto resManager = ResouceManager::GetInstance();

	// UIの作成
	{
		auto playerInfo = Instantate("PlayerInfo", Vector3(-725, 330, 0));
		imgPlayerInfo = playerInfo->AddComponent<Image>();
		imgPlayerInfo->texture = resManager->GetTexture("PlayerInfo");
		imgPlayerInfo->size = Vector2(imgPlayerInfo->texture->GetWidth() * 1.4f, imgPlayerInfo->texture->GetHeight() * 1.1f);
	}
	// MyMSHP
	{
		auto playerHp = Instantate("PlayerHP", Vector3(-700, 280, 0));
		numPlayerImage = playerHp->AddComponent<ImageNum>();
		numPlayerImage->scale = 1.2f;
	}
	// BoostBarBack
	{
		auto boostBarBack = Instantate("BoostBarBack", Vector3(250, 450, 0));
		imgBoostBarBack = boostBarBack->AddComponent<Image>();
		imgBoostBarBack->texture = resManager->GetTexture("BoostBarBack");
		imgBoostBarBack->size = imgBoostBarBack->texture->GetSize() * 1.2f;
	}
	// BoostBarOverHeat
	{
		auto boostBarOverHeat = Instantate("BoosetBarOverHeat", Vector3(245, 435, 0));
		imgBoostBarOverHeat = boostBarOverHeat->AddComponent<Image>();
		imgBoostBarOverHeat->texture = resManager->GetTexture("BoostBarOVERHEAT");
		imgBoostBarOverHeat->size = imgBoostBarOverHeat->texture->GetSize() * 1.2f;
		ibBoostBarOverHeat = boostBarOverHeat->AddComponent<ImageBlinking>();
		ibBoostBarOverHeat->image = imgBoostBarOverHeat;
		ibBoostBarOverHeat->speed = 5.0f;
	}
	// BoostBar
	{
		auto boostBar = Instantate("BoostBar", Vector3(245, 435, 0));
		imgBoostBar = boostBar->AddComponent<Image>();
		imgBoostBar->texture = resManager->GetTexture("BoostBar");
		imgBoostBar->size = imgBoostBar->texture->GetSize() * 1.2f;
		imgBoostBar->fillAmout = 0.5f;
	}
	// BurstBarBack
	{
		auto burstBarBack = Instantate("burstBarBack", Vector3(-250, 450, 0));
		imgBurstBarBack = burstBarBack->AddComponent<Image>();
		imgBurstBarBack->texture = resManager->GetTexture("BurstBarBack");
		imgBurstBarBack->size = imgBurstBarBack->texture->GetSize() * 1.2f;
	}
	// BurstBar
	{
		auto burstBar = Instantate("burstBar", Vector3(-253, 428, 0));
		imgBurstBar = burstBar->AddComponent<Image>();
		imgBurstBar->texture = resManager->GetTexture("BurstBar");
		imgBurstBar->size = imgBurstBar->texture->GetSize() * 1.2f;
		imgBurstBar->fillType = Image::FillType::HorizontalInverse;
		imgBurstBar->fillAmout = 0.5f;
	}
	// WeaponBack
	{
		if (!myMs->numWeapons.empty())
		{
			// サイズを予約
			imgWeaponBack.reserve(myMs->numWeapons.size());
			int i = 0;
			for (auto x : myMs->numWeapons)
			{
				auto weaponBack = Instantate("WeaponBack" + std::to_string(i), Vector3(765.0f, 400.0f + (-160.0f * i), 0));
				auto image = weaponBack->AddComponent<Image>();
				image->texture = resManager->GetTexture("WeaponBack");
				image->size = image->texture->GetSize() * 1.3f;

				// 配列に追加
				imgWeaponBack.push_back(image);
				i++;
			}
		}
	}
	// TargetMark
	{
		// リソースを保存
		texTargetMark01 = resManager->GetTexture("TargetMark01");
		texTargetMark02 = resManager->GetTexture("TargetMark02");
		texTargetMark03 = resManager->GetTexture("TargetMark03");

		auto targetMark = Instantate("TargetMark");
		imgTargetMark = targetMark->AddComponent<Image>();
		imgTargetMark->texture = texTargetMark01;
		imgTargetMark->size = imgTargetMark->texture->GetSize();
	}
	// TargetInfo
	{
		auto targetMark = Instantate("TargetMsInfo", Vector3(120, -70, 0));
		imgTargetInfo = targetMark->AddComponent<Image>();
		imgTargetInfo->texture = resManager->GetTexture("TargetMsInfo");
		imgTargetInfo->size = imgTargetInfo->texture->GetSize();
	}
	// TargetHp
	{
		auto targetHP = Instantate("TargetMsHpBar", Vector3(162, -75, 0));
		imgTargetHPBar = targetHP->AddComponent<Image>();
		imgTargetHPBar->texture = resManager->GetTexture("TargetMsHpBar");
		imgTargetHPBar->size = imgTargetHPBar->texture->GetSize();

	}

	// TeumHPBar
	{
		auto teumHpBar = Instantate("TeumHpBar", Vector3(-640, -465, 0));
		imgTeumHpBar = teumHpBar->AddComponent<Image>();
		imgTeumHpBar->texture = resManager->GetTexture("TeumHpBar");
		imgTeumHpBar->size = imgTeumHpBar->texture->GetSize() * 1.2f;
		imgTeumHpBar->fillAmout = 0.4f;
	}
	// TeumEnemyBar
	{
		auto teumEnemyBar = Instantate("TeumEnemyBar", Vector3(-620, -420, 0));
		imgTeumEnemyBar = teumEnemyBar->AddComponent<Image>();
		imgTeumEnemyBar->texture = resManager->GetTexture("TeumEnemyHpBar");
		imgTeumEnemyBar->size = imgTeumEnemyBar->texture->GetSize() * 1.2f;
		imgTeumEnemyBar->fillAmout = 0.8f;

	}
	// TeumFrame
	{
		auto teumHp = Instantate("TeumFrame", Vector3(-635, -430, 0));
		imgTeumFrame = teumHp->AddComponent<Image>();
		imgTeumFrame->texture = resManager->GetTexture("TeumFrame");
		imgTeumFrame->size = imgTeumFrame->texture->GetSize() * 1.2f;
	}
	// Timer
	{
		auto timer = Instantate("Timer", Vector3(800, -450, 0));
		imgTimer = timer->AddComponent<Image>();
		imgTimer->texture = resManager->GetTexture("Timer");
		imgTimer->size = imgTimer->texture->GetSize() * 1.2f;
	}

	// UIを全てひひょうじにする
	imgPlayerInfo->SetEnable(false);
	numPlayerImage->SetEnable(false);
	imgBoostBarBack->SetEnable(false);
	imgBoostBar->SetEnable(false);
	imgBoostBarOverHeat->SetEnable(false);
	imgBurstBarBack->SetEnable(false);
	imgBurstBar->SetEnable(false);
	for (auto x : imgWeaponBack)
	{
		x->SetEnable(false);
	}
	imgTargetMark->SetEnable(false);
	imgTargetInfo->SetEnable(false);
	imgTargetHPBar->SetEnable(false);
	imgTeumFrame->SetEnable(false);
	imgTeumHpBar->SetEnable(false);
	imgTeumEnemyBar->SetEnable(false);
	imgTimer->SetEnable(false);


	// カメラに自身のMSを設定
	lookOnCamera->SetMsTransform(myMs->GetTransform().get());

	// カメラにターゲットを設定
	lookOnCamera->SelectTarget(otherOwner->myMs->GetTransform().get());

	// プレイヤーにカメラ設定
	myMs->SetCamera(lookOnCamera->GetTransform().get());
}

void PlayerControl::Update()
{
	if (!isStart)
	{
		return;
	}
	else
	{
		// UIを表示
		imgPlayerInfo->SetEnable(true);
		numPlayerImage->SetEnable(true);
		imgBoostBarBack->SetEnable(true);
		imgBoostBar->SetEnable(true);
		imgBurstBarBack->SetEnable(true);
		imgBurstBar->SetEnable(true);
		for (auto x : imgWeaponBack)
		{
			x->SetEnable(true);
		}
		imgTargetMark->SetEnable(true);
		imgTargetInfo->SetEnable(true);
		imgTargetHPBar->SetEnable(true);
		imgTeumFrame->SetEnable(true);
		imgTeumHpBar->SetEnable(true);;
		imgTeumEnemyBar->SetEnable(true);
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

void PlayerControl::UIUpdate()
{
	// ターゲットマークの処理
	if (imgTargetMark)
	{
		// 近ければ小さくし、遠ければ大きくする
		imgTargetMark->size = Vector2(Mathf::Clamp(distance, 100.0f, 200.0f));
		if (myMs)
		{
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
	}

	// BoostBarの処理
	{
		if (myMs)
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
	}

	// TargetHPBar
	{
		auto targetMs = otherOwner->myMs;
		if (targetMs)
		{
			imgTargetHPBar->fillAmout = targetMs->GetHP01();
		}
	}
}
