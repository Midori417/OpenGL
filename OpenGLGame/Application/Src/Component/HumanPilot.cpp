/**
* @file HumanPilot.cpp
*/
#include "HumanPilot.h"

#include "CameraManager.h"

#include "BaseMs.h"
#include "ImageBlinking.h"
#include "ImageNum.h"
#include "BaseWeapon.h"

#include "../Global.h"

/**
* 最初に実行
*/
void HumanPilot::Start()
{
	// 必要なマネージャーを取得
	auto resManager = AssetManager::GetInstance();

	// 初期する
	Initialize();

	// UIの作成
	{
		// 自身の情報背景を作成
		{
			auto myInfoBack = Instantate(CreateObjectType::Empty, Vector3(-725, 330, 0), Quaternion::identity);
			myInfoBack->name = "MysInfo";
			imgMyInfoBack = myInfoBack->AddComponent<Image>();
			imgMyInfoBack->texture = resManager->GetTexture("PlayerInfo");
			imgMyInfoBack->size = Vector2(imgMyInfoBack->texture->GetWidth() * 1.4f,
				imgMyInfoBack->texture->GetHeight() * 1.1f);
		}
		// 自身の機体の体力を作成
		{
			auto myMsHp = Instantate(CreateObjectType::Empty, Vector3(-670, 280, 0), Quaternion::identity);
			myMsHp->name = "MyMsHp";
			inMyMsHp = myMsHp->AddComponent<ImageNum>();
			inMyMsHp->space = -70;
			inMyMsHp->scale = 1.35f;
		}
		// ブーストバーの背景を作成
		{
			auto boostBarBack = Instantate(CreateObjectType::Empty, Vector3(250, 450, 0), Quaternion::identity);
			boostBarBack->name = "BoostBarBack";
			imgBoostBarBack = boostBarBack->AddComponent<Image>();
			imgBoostBarBack->texture = resManager->GetTexture("BoostBarBack");
			imgBoostBarBack->size = imgBoostBarBack->texture->GetSize() * 1.2f;
		}
		// ブーストバーのオーバーヒートを作成
		{
			auto boostBarOverHeat = Instantate(CreateObjectType::Empty, Vector3(245, 435, 0), Quaternion::identity);
			boostBarOverHeat->name = "BoosetBarOverHeat";
			imgBoostBarOverHeat = boostBarOverHeat->AddComponent<Image>();
			imgBoostBarOverHeat->texture = resManager->GetTexture("BoostBarOVERHEAT");
			imgBoostBarOverHeat->size = imgBoostBarOverHeat->texture->GetSize() * 1.2f;
			// 点滅コンポーネント
			ibBoostBarOverHeat = boostBarOverHeat->AddComponent<ImageBlinking>();
			ibBoostBarOverHeat->speed = 5.0f;
		}
		// ブーストバーを作成
		{
			auto boostBar = Instantate(CreateObjectType::Empty, Vector3(245, 435, 0), Quaternion::identity);
			boostBar->name = "BoostBar";
			imgBoostBar = boostBar->AddComponent<Image>();
			imgBoostBar->texture = resManager->GetTexture("BoostBar");
			imgBoostBar->size = imgBoostBar->texture->GetSize() * 1.2f;
			imgBoostBar->fillAmout = 0.5f;
		}
		// 武器UI
		{
			// 自身のMSの武器が空なら何もしない
			if (!myMs->uiWeapons.empty())
			{
				// サイズを予約
				imgWeaponBacks.reserve(myMs->uiWeapons.size());
				int i = 0;
				for (auto x : myMs->uiWeapons)
				{
					// 武器アイコンの背景
					{
						auto weaponBack = Instantate(CreateObjectType::Empty, Vector3(765.0f, 400.0f + (-160.0f * i), 0), Quaternion::identity);
						weaponBack->name = "WeaponBack" + std::to_string(i);
						auto image = weaponBack->AddComponent<Image>();
						image->texture = resManager->GetTexture("WeaponBack");
						image->size = image->texture->GetSize() * 1.3f;
						imgWeaponBacks.push_back(image);
					}
					// 武器の残弾
					{
						auto weaponAmo = Instantate(CreateObjectType::Empty, Vector3(715.0f, 410.0f + (-160.0f * i), 0), Quaternion::identity);
						weaponAmo->name = "WeapnAmo" + std::to_string(i);
						auto imageNum = weaponAmo->AddComponent<ImageNum>();
						imageNum->scale = 0.8f;
						imageNum->space = -45;
						inWeaponAmos.push_back(imageNum);
					}
					// 武器の残弾バー
					{
						auto weaponAmoBar = Instantate(CreateObjectType::Empty, Vector3(665.0f, 448.0f + (-160 * i), 0), Quaternion::identity);
						weaponAmoBar->name = "WeapnAmoBar" + std::to_string(i);
						auto image = weaponAmoBar->AddComponent<Image>();
						image->texture = resManager->GetTexture("WeaponBar");
						image->size = image->texture->GetSize() * 1.3f;
						imgWeaponBars.push_back(image);
					}
					// 武器のアイコン
					{
						auto weaponIcon = Instantate(CreateObjectType::Empty, Vector3(830, 410 + (-160.0f * i), 0), Quaternion::identity);
						weaponIcon->name = x->name;
						auto image = weaponIcon->AddComponent<Image>();
						image->texture = x->iconTexture;
						image->size = image->texture->GetSize() * 1.3f;
						imgWeapnIcons.push_back(image);
					}
					i++;
				}
			}
		}
		// 自チームの味方体力
		if (myTeamOtherOwner)
		{
			// パートナー機体体力背景
			{
				auto myPartnerMsHp = Instantate(CreateObjectType::Empty, Vector3(-820, 110, 0), Quaternion::identity);
				myPartnerMsHp->name = "PartnerMsHp";
				imgPartnerHpBack = myPartnerMsHp->AddComponent<Image>();
				imgPartnerHpBack->texture = resManager->GetTexture("PartnerHpBack");
				imgPartnerHpBack->size = imgPartnerHpBack->texture->GetSize() * 1.2f;
			}

			// 味方体力
			{
				auto myTeumOtherMsHp = Instantate(CreateObjectType::Empty, Vector3(-770, 100, 0), Quaternion::identity);
				myTeumOtherMsHp->name = "PartnerMsHp";
				inPartnerMsHp = myTeumOtherMsHp->AddComponent<ImageNum>();
				inPartnerMsHp->space = -40;
				inPartnerMsHp->scale = 0.7f;
				inPartnerMsHp->num = 888;
			}

			// 味方機体の情報を作成
			{
				auto myTeumOtherMsInfo = Instantate(CreateObjectType::Empty, Vector3(120, -70, 0), Quaternion::identity);
				myTeumOtherMsInfo->name = "MyTeumOtherMsInfo";
				imgMyTeumOtherMsInfo = myTeumOtherMsInfo->AddComponent<Image>();
				imgMyTeumOtherMsInfo->texture = resManager->GetTexture("MyTeumOtherMsInfo");
				imgMyTeumOtherMsInfo->size = imgMyTeumOtherMsInfo->texture->GetSize();
			}
			// 味方機体の体力バーを作成
			{
				auto myTeumOtherMsHpBar = Instantate(CreateObjectType::Empty, Vector3(162, -75, 0), Quaternion::identity);
				myTeumOtherMsHpBar->name = "MyTeumOtherMsHpBar";
				imgMyTeumOtherMsHpBar = myTeumOtherMsHpBar->AddComponent<Image>();
				imgMyTeumOtherMsHpBar->texture = resManager->GetTexture("MyTeumOtherMsHpBar");
				imgMyTeumOtherMsHpBar->size = imgMyTeumOtherMsHpBar->texture->GetSize();
			}
		}

		// ターゲットマークを作成
		{
			// ターゲットマークのテクスチャを取得
			texTargetMarkGreen = resManager->GetTexture("TargetMarkGreen");
			texTargetMarkRed = resManager->GetTexture("TargetMarkRed");
			texTargetMarkLock = resManager->GetTexture("TargetMarkLock");
			texTargetMarkYellow = resManager->GetTexture("TargetMarkYellow");

			auto targetMark = Instantate(CreateObjectType::Empty);
			targetMark->name = "TargetMark";
			imgTargetMark = targetMark->AddComponent<Image>();
			imgTargetMark->texture = texTargetMarkGreen;
			imgTargetMark->size = imgTargetMark->texture->GetSize();
		}
		for (int i = 0; i < otherTeamOwner.size(); ++i)
		{
			// ターゲットの情報を作成
			{
				auto targetMark = Instantate(CreateObjectType::Empty, Vector3(120, -70, 0), Quaternion::identity);
				targetMark->name = "OtherTeumMsInfo" + std::to_string(i);
				auto imgOtherTeumMsInfo = targetMark->AddComponent<Image>();
				imgOtherTeumMsInfo->texture = resManager->GetTexture("OtherTeumMsInfo");
				imgOtherTeumMsInfo->size = imgOtherTeumMsInfo->texture->GetSize();
				imgOtherTeumMsInfoBacks.push_back(imgOtherTeumMsInfo);
			}
			// ターゲットの体力バーを作成
			{
				auto otherMsHpBar = Instantate(CreateObjectType::Empty, Vector3(162, -75, 0), Quaternion::identity);
				otherMsHpBar->name = "OtherTeumMsHpBar" + std::to_string(i);
				auto imgOtherMsHpBar = otherMsHpBar->AddComponent<Image>();
				imgOtherMsHpBar->texture = resManager->GetTexture("OtherTeumMsHpBar");
				imgOtherMsHpBar->size = imgOtherMsHpBar->texture->GetSize();
				imgOtherTeumMsHpBars.push_back(imgOtherMsHpBar);
			}
		}

		// チーム体力
		{
			// 自チームの体力バーを作成
			{
				auto myTeamHpBar = Instantate(CreateObjectType::Empty); 
				myTeamHpBar->name = "MyTeamHpBar";
				myTeamHpBar->GetTransform()->position = Vector3(-640, -465, 0);
				imgMyTeamHpBar = myTeamHpBar->AddComponent<Image>();
				imgMyTeamHpBar->texture = resManager->GetTexture("MyTeamHpBar");
				imgMyTeamHpBar->size = imgMyTeamHpBar->texture->GetSize() * 1.2f;

				float max = static_cast<float>(teamMaxHp);
				float hp = static_cast<float>(MyTeamHp());
				imgMyTeamHpBar->fillAmout = (max - (max - hp)) / max;
			}
			// 相手チームの体力バーを作成
			{
				auto otherTeamHpBar = Instantate(CreateObjectType::Empty);
				otherTeamHpBar->name = "OtherTeamHpBar";
				otherTeamHpBar->GetTransform()->position = Vector3(-620, -420, 0);
				imgOtherTeamHpBar = otherTeamHpBar->AddComponent<Image>();
				imgOtherTeamHpBar->texture = resManager->GetTexture("OtherTeamHpBar");
				imgOtherTeamHpBar->size = imgOtherTeamHpBar->texture->GetSize() * 1.2f;

				float max = static_cast<float>(teamMaxHp);
				float hp = static_cast<float>(OtherTeamHp());
				imgOtherTeamHpBar->fillAmout = (max - (max - hp)) / max;
			}
			// チーム体力フレームを作成
			{
				auto teamHpFrame = Instantate(CreateObjectType::Empty);
				teamHpFrame->name = "TeamHpFrame";
				teamHpFrame->GetTransform()->position = Vector3(-635, -430, 0);
				imgTeamHpFrame = teamHpFrame->AddComponent<Image>();
				imgTeamHpFrame->texture = resManager->GetTexture("TeamHpFrame");
				imgTeamHpFrame->size = imgTeamHpFrame->texture->GetSize() * 1.2f;
			}
		}
		// WINを作成
		{
			auto win = Instantate(CreateObjectType::Empty);
			win->name = "Win";
			imgWin = win->AddComponent<Image>();
			imgWin->texture = resManager->GetTexture("Win");
			imgWin->SetWindowSize();
		}
		// Loseを作成
		{
			auto lose = Instantate(CreateObjectType::Empty);
			lose->name = "Lose";
			imgLose = lose->AddComponent<Image>();
			imgLose->texture = resManager->GetTexture("Lose");
			imgLose->SetWindowSize();
		}
	}

	// UIを非表示にする
	{
		imgMyInfoBack->isActive = (false);
		inMyMsHp->isActive = (false);
		imgBoostBarBack->isActive = (false);
		imgBoostBar->isActive = (false);
		imgBoostBarOverHeat->isActive =(false);
		for (auto x : imgWeaponBacks)
		{
			x->isActive = false;
		}
		for (auto x : inWeaponAmos)
		{
			x->isActive = false;
		}
		for (auto x : imgWeaponBars)
		{
			x->isActive = false;
		}
		for (auto x : imgWeapnIcons)
		{
			x->isActive = false;
		}
		if (myTeamOtherOwner)
		{
			imgPartnerHpBack->isActive = (false);
			inPartnerMsHp->isActive = (false);
			imgMyTeumOtherMsHpBar->isActive =(false);
			imgMyTeumOtherMsInfo->isActive =false;
		}
		imgTargetMark->isActive =(false);
		for (int i = 0; i < otherTeamOwner.size(); ++i)
		{
			imgOtherTeumMsInfoBacks[i]->isActive =(false);
			imgOtherTeumMsHpBars[i]->isActive =(false);
		}
		imgTeamHpFrame->isActive = (false);
		imgMyTeamHpBar->isActive = (false);
		imgOtherTeamHpBar->isActive =(false);
		imgWin->isActive = (false);
		imgLose->isActive = (false);
	}

	// 初期する
	Initialize();
}

/**
* 毎フレーム実行
*/
void HumanPilot::Update()
{
	// スタート呼び出されていなければ何もしない
	if (!isStart)
	{
		return;
	}

	// ゲーム入力の更新
	if (isInputUpdate)
	{
		GameInputUpdate();
	}

	// 自身の機体が死んでいた時の処理
	if (myMs->IsDeath())
	{
		MyMsDeadUpdate();
	}
	else
	{
		myMs->SetDistance(GetDistance());

		// ターゲットの更新処理
		TargetUpdate();
	}

	// UI更新
	UIUpdate();
}

/**
* コントロールをスタートする
*/
void HumanPilot::ControlStart()
{
	// UIを表示
	imgMyInfoBack->isActive =(true);
	inMyMsHp->isActive = (true);
	imgBoostBarBack->isActive = (true);
	imgBoostBar->isActive =(true);
	for (auto x : imgWeaponBacks)
	{
		x->isActive = (true);
	}
	for (auto x : inWeaponAmos)
	{
		x->isActive = (true);
	}
	for (auto x : imgWeaponBars)
	{
		x->isActive = (true);
	}
	for (auto x : imgWeapnIcons)
	{
		x->isActive = (true);
	}
	if (inPartnerMsHp)
	{
		imgPartnerHpBack->isActive = true;
		inPartnerMsHp->isActive = (true);
	}
	imgTargetMark->isActive = (true);
	imgTeamHpFrame->isActive = (true);
	imgMyTeamHpBar->isActive = (true);;
	imgOtherTeamHpBar->isActive = (true);

	isStart = true;
}

/**
* ゲーム入力を更新
*/
void HumanPilot::GameInputUpdate()
{
	// ゲーム入力
	gameInput->moveAxis = Vector2(InputManager::GetAxis(Axis::Horizontal), InputManager::GetAxis(Axis::Vertical));
	gameInput->jumpBtn = InputKey::GetKey(KeyCode::Space);
	gameInput->dashBtn = InputKey::GetKey(KeyCode::LeftShift);
	gameInput->stepBtn = InputKey::GetKey(KeyCode::LeftControl);
	gameInput->action1Btn = InputMouse::GetMouseButton(MouseButton::LeftButton);
	gameInput->action2Btn = InputKey::GetKey(KeyCode::E);
	gameInput->action3Btn = InputMouse::GetMouseButton(MouseButton::RightButton);
	gameInput->targetChangeBtn = InputMouse::GetMouseButtonDown(MouseButton::CenterButton);
}

/**
* UIの更新
*/
void HumanPilot::UIUpdate()
{
	// 自チーム体力の設定
	if (imgMyTeamHpBar)
	{
		float max = static_cast<float>(teamMaxHp);
		float hp = static_cast<float>(MyTeamHp());
		imgMyTeamHpBar->fillAmout = (max - (max - hp)) / max;
	}
	// 相手チームの体力の設定
	if (imgOtherTeamHpBar)
	{
		float max = static_cast<float>(teamMaxHp);
		float hp = static_cast<float>(OtherTeamHp());
		imgOtherTeamHpBar->fillAmout = (max - (max - hp)) / max;
	}

	// 味方の体力
	if (myTeamOtherOwner)
	{
		if (inPartnerMsHp)
		{
			inPartnerMsHp->num = myTeamOtherOwner->myMs->GetHP();
		}

		auto otherMs = myTeamOtherOwner->myMs;
		if (!otherMs->IsDeath())
		{
			// MSの方向を調べる
			Vector3 directionToTarget = Vector3::Normalize(otherMs->GetTransform()->position - myCamera->GetTransform()->position);
			float dot = Vector3::Dot(directionToTarget, myCamera->GetTransform()->Forward());
			if (dot > 0.4f)
			{
				imgMyTeumOtherMsInfo->isActive = (true);
				imgMyTeumOtherMsHpBar->isActive =(true);
				auto camera = myCamera->GetComponent<Camera>();
				if (camera)
				{
					auto winManager = WindowManager::GetInstance();
					auto size = winManager->GetWindowSize();
					Vector2 screenPos = Camera::WorldPointToScreenPoint(otherMs->GetTransform()->position,
						camera, size.x, size.y);
					imgMyTeumOtherMsInfo->GetTransform()->position = Vector3(screenPos, 1) + Vector3(120, -50, 0);
					imgMyTeumOtherMsHpBar->GetTransform()->position = Vector3(screenPos, 1) + Vector3(170, -55, 0);
				}
				imgMyTeumOtherMsHpBar->fillAmout = otherMs->GetHP01();
			}
			else
			{
				imgMyTeumOtherMsInfo->isActive = (false);
				imgMyTeumOtherMsHpBar->isActive =(false);
			}
		}
		else if (otherMs->IsDeath())
		{
			imgMyTeumOtherMsInfo->isActive = (false);
			imgMyTeumOtherMsHpBar->isActive = (false);
		}

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
			imgBoostBarOverHeat->isActive =(false);
		}
		else if (myMs->GetBoostEnergy() <= 0)
		{
			imgBoostBarOverHeat->isActive = (true);
		}
	}
	// 武装の残弾を設定
	for (int i = 0; i < inWeaponAmos.size(); ++i)
	{
		inWeaponAmos[i]->num = static_cast<int>(myMs->uiWeapons[i]->amo);
	}
	// 武装の残弾ゲージを設定
	for (int i = 0; i < imgWeaponBars.size(); ++i)
	{
		float amo = (myMs->uiWeapons[i]->amo);
		float amoMax = (myMs->uiWeapons[i]->amoMax);
		imgWeaponBars[i]->fillAmout = Mathf::Clamp01((amoMax - (amoMax - amo)) / amoMax);
	}

	if (targetOwner)
	{
		// ターゲットマークの処理
		if (imgTargetMark)
		{
			auto targetMs = targetOwner->myMs;

			if (!targetMs->IsDeath())
			{
				if (!imgTargetMark->isActive)
				{
					imgTargetMark->isActive = (true);
				}
				auto camera = myCamera->GetComponent<Camera>();
				if (camera)
				{
					auto winManager = WindowManager::GetInstance();
					auto size = winManager->GetWindowSize();
					Vector2 screenPos = Camera::WorldPointToScreenPoint(targetMs->GetTransform()->position,
						camera, size.x, size.y);
					imgTargetMark->GetTransform()->position = Vector3(screenPos, 1);
				}
				// 近ければ小さくし、遠ければ大きくする
				imgTargetMark->size = Vector2(Mathf::Clamp(GetDistance(), 100.0f, 200.0f));

				if (myMs->HomingCheck())
				{
					// 距離によってテクスチャを変える
					float dis = Vector3::Distance(
						myMs->GetTransform()->position * Vector3(1, 0, 1), 
						targetMs->GetTransform()->position * Vector3(1, 0, 1));
					if (dis <= myMs->proximityDistance)
					{
						imgTargetMark->texture = texTargetMarkLock;
					}
					else
					{
						imgTargetMark->texture = texTargetMarkRed;
					}
				}
				else
				{
					imgTargetMark->texture = texTargetMarkGreen;
				}
			}
			else
			{
				if (imgTargetMark->isActive)
				{
					imgTargetMark->isActive = (false);
				}

			}
		}

	}
	// 相手チームの機体体力
	for (int i = 0; i < otherTeamOwner.size(); ++i)
	{
		auto otherMs = otherTeamOwner[i]->myMs;

		if (!otherMs->IsDeath())
		{
			// MSの方向を調べる
			Vector3 directionToTarget = Vector3::Normalize(otherMs->GetTransform()->position - myCamera->GetTransform()->position);
			float dot = Vector3::Dot(directionToTarget, myCamera->GetTransform()->Forward());
			if (dot > 0.4f)
			{
				if (!imgOtherTeumMsInfoBacks[i]->isActive)
				{
					imgOtherTeumMsInfoBacks[i]->isActive = (true);
				}
				if (!imgOtherTeumMsHpBars[i]->isActive)
				{
					imgOtherTeumMsHpBars[i]->isActive = (true);
				}
				auto camera = myCamera->GetComponent<Camera>();
				if (camera)
				{
					auto winManager = WindowManager::GetInstance();
					auto size = winManager->GetWindowSize();
					Vector2 screenPos = Camera::WorldPointToScreenPoint(otherMs->GetTransform()->position,
						camera, size.x, size.y);
					imgOtherTeumMsInfoBacks[i]->GetTransform()->position = Vector3(screenPos, 1) + Vector3(120, -50, 0);
					imgOtherTeumMsHpBars[i]->GetTransform()->position = Vector3(screenPos, 1) + Vector3(170, -55, 0);
				}
				imgOtherTeumMsHpBars[i]->fillAmout = otherMs->GetHP01();
			}
			else
			{
				if (imgOtherTeumMsInfoBacks[i]->isActive)
				{
					imgOtherTeumMsInfoBacks[i]->isActive = false;
				}
				if (imgOtherTeumMsHpBars[i]->isActive)
				{
					imgOtherTeumMsHpBars[i]->isActive = false;
				}
			}
		}
		else if (otherMs->IsDeath())
		{
			if (imgOtherTeumMsInfoBacks[i]->isActive)
			{
				imgOtherTeumMsInfoBacks[i]->isActive = false;
			}
			if (imgOtherTeumMsHpBars[i]->isActive)
			{
				imgOtherTeumMsHpBars[i]->isActive = (false);
			}
		}
	}

}


/**
* 終了処理
*/
void HumanPilot::Finish(VictoryState victoryState)
{
	// 機体の挙動を止める
	myMs->Stop();

	// UIを非表示にする
	{
		imgMyInfoBack->isActive = (false);
		inMyMsHp->Stop();
		imgBoostBarBack->isActive = (false);
		imgBoostBar->isActive =(false);
		imgBoostBarOverHeat->isActive =(false);
		if (myTeamOtherOwner)
		{
			imgPartnerHpBack->isActive =(false);
			imgMyTeumOtherMsHpBar->isActive =(false);
			imgMyTeumOtherMsInfo->isActive =(false);
			inPartnerMsHp->Stop();
		}
		for (auto x : imgWeaponBacks)
		{
			x->isActive =(false);
		}
		for (auto x : inWeaponAmos)
		{
			x->Stop();
		}
		for (auto x : imgWeaponBars)
		{
			x->isActive = (false);
		}
		for (auto x : imgWeapnIcons)
		{
			x->isActive = (false);
		}
		imgTargetMark->isActive = (false);
		for (int i = 0; i < otherTeamOwner.size(); ++i)
		{
			imgOtherTeumMsInfoBacks[i]->isActive =(false);
			imgOtherTeumMsHpBars[i]->isActive =(false);
		}
		imgTeamHpFrame->isActive =(false);
		imgMyTeamHpBar->isActive =(false);
		imgOtherTeamHpBar->isActive = (false);
	}

	// 勝敗によってUIを表示する
	switch (victoryState)
	{
	case VictoryState::None:
		break;
	case VictoryState::Win:
		imgWin->isActive =(true);
		break;
	case VictoryState::Lose:
		imgLose->isActive =(true);
		break;
	case VictoryState::Drow:
		break;
	}
}