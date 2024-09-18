/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "FadeOut.h"

#include "CameraManager.h"

#include "BaseMs.h"
#include "Gundam.h"

#include "HumanPilot.h"
#include "CpuPilot.h"

#include "../Global.h"

// スタティック変数を初期化
BattleInfoPtr BattleManager::battleInfo = nullptr;

/**
* 生成時に実行
*/
void BattleManager::Awake()
{
	// 各マネージャを取得
	auto assetManager = AssetManager::GetInstance();

	// フェードオブジェクトを作成
	{
		auto obj = Instantate(assetManager->GetGameObject("FadeObject"));
		fadeOut = obj->GetComponent<FadeOut>();
	}

	// バトル情報を作成
	// 後々バトル設定シーンでする
	battleInfo = std::make_shared<BattleInfo>();
	{
		// 配列を予約
		battleInfo->pilotInfos.reserve(playerMax);
		for (int i = 0; i < playerMax; ++i)
		{
			PilotInfo pilotInfo;
			battleInfo->pilotInfos.push_back(pilotInfo);
		}

		// テスト
		battleInfo->pilotInfos[0].teamId = 1;
		battleInfo->pilotInfos[0].playerId = 0;
		battleInfo->pilotInfos[0].ms = MsList::Gundam;

		battleInfo->pilotInfos[1].teamId = 2;
		battleInfo->pilotInfos[1].playerId = 1;
		battleInfo->pilotInfos[1].ms = MsList::Gundam;

		// バトル情報を設定

		// チーム体力を設定
		if (battleInfo->team1Hp > 0)
		{
			team1Hp = std::make_shared<int>(battleInfo->team1Hp);
		}
		if (battleInfo->team1Hp > 0)
		{
			team2Hp = std::make_shared<int>(battleInfo->team2Hp);
		}

		// 時間を設定
	}

	BattleSetting();

	// UI
	{
		// STANBAYを作成
		{
			auto standbay = Instantate(CreateObjectType::Empty);
			standbay->name = "Standby";
			imgStandbay = standbay->AddComponent<Image>();
			imgStandbay->texture = assetManager->GetTexture("Standby");
			imgStandbay->SetWindowSize();
		}
		// GOを作成
		{
			auto go = Instantate(CreateObjectType::Empty);
			go->name = "Go";
			imgGo = go->AddComponent<Image>();
			imgGo->texture = assetManager->GetTexture("Go");
			imgGo->SetWindowSize();
		}
	}
}

/**
* 最初に実行
*/
void BattleManager::Start()
{
	// MSの出撃位置を設定
	for (int i = 0; i < team1Pilots.size(); ++i)
	{
		auto teum1 = team1Pilots[i];

		teum1->myMs->GetTransform()->position = responPoses[0] + Vector3(10.0f * i, 0, 0);
		teum1->responPoss = responPoses;

		Vector3 toTargetVector = Vector3::Normalize(responPoses[1] - responPoses[0]);
		teum1->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}
	for (int i = 0; i < team2Pilots.size(); ++i)
	{
		auto teum2 = team2Pilots[i];

		teum2->myMs->GetTransform()->position = responPoses[1] + Vector3(10.0f * i, 0, 0);

		// リスポーン位置を設定
		teum2->responPoss = responPoses;

		Vector3 toTargetVector = Vector3::Normalize(responPoses[0] - responPoses[1]);
		teum2->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}

	// UIを非表示
	imgStandbay->isActive = false;
	imgGo->isActive = false;
}

/**
* 毎フレーム実行
*/
void BattleManager::Update()
{
	// バトル状態
	switch (battleState)
	{
	case BattleManager::BattleState::Ready:

		// 準備
	{
		// タイマーを進める
		timer += Time::DeltaTime();
		if (timer > readyTime)
		{
			// バトル状態をスタンバイに
			battleState = BattleState::Standbay;

			// Stanbayを表示
			imgStandbay->isActive = true;

			// タイマーを0にする
			timer = 0;
		}
	}

	break;
	case BattleManager::BattleState::Standbay:

		// スタンバイ
	{
		// タイマーを進める
		timer += Time::DeltaTime();
		if (timer > standbayTime)
		{
			// バトル状態をゴーに
			battleState = BattleState::GO;

			// Stanbayを非表示に
			imgStandbay->isActive = false;
			// GOを表示
			imgGo->isActive = true;

			// タイマーを0にする
			timer = 0;
		}
	}
	break;
	case BattleManager::BattleState::GO:
		// ゴー
	{
		// タイマーを進める
		timer += Time::DeltaTime();
		if (timer > goTime)
		{
			// バトル状態をバトルに
			battleState = BattleState::Battle;

			// GOを非表示に
			imgGo->isActive = false;

			// コントロールの処理を開始させる
			for (auto teum1 : team1Pilots)
			{
				teum1->ControlStart();
			}
			for (auto teum2 : team2Pilots)
			{
				teum2->ControlStart();
			}
		}
	}
	break;
	case BattleManager::BattleState::Battle:
		// バトル中
	{
		if (*team1Hp <= 0 || *team2Hp <= 0)
		{
			VictoryState teum1Victory = VictoryState::None;
			VictoryState teum2Victory = VictoryState::None;
			// どちらのチームHpも0ならば引き分け
			if (*team1Hp <= 0 && *team2Hp <= 0)
			{
				teum1Victory = VictoryState::Drow;
				teum2Victory = VictoryState::Drow;
			}
			else if (*team1Hp <= 0)
			{
				teum1Victory = VictoryState::Lose;
				teum2Victory = VictoryState::Win;
			}
			else if (*team2Hp <= 0)
			{
				teum1Victory = VictoryState::Win;
				teum2Victory = VictoryState::Lose;
			}

			// 終了処理させる
			for (auto teum1 : team1Pilots)
			{
				teum1->Finish(teum1Victory);
				teum1->isActive = false;
			}
			for (auto teum2 : team2Pilots)
			{
				teum2->Finish(teum2Victory);
				teum2->isActive = false;
			}
			battleState = BattleState::Victory;
		}
	}
	break;
	case BattleManager::BattleState::Victory:

		// 勝敗
	{
		if (InputKey::GetKey(KeyCode::Enter))
		{
			fadeOut->FadeStart();
		}

		// フェードが終了したらシーンを移動する
		if (fadeOut->IsFadeOut())
		{
			SceneManager::LoadScene("BattleSettingScene");
		}
	}

	break;
	}
}

/**
* バトル情報を設定
*/
void BattleManager::SetBattleInfo(BattleInfoPtr _battleInfo)
{
	battleInfo.swap(_battleInfo);
}

/**
* リスポーン位置を設定
*
* @param posed リスポーン位置配列
*/
void BattleManager::SetResponPos(const std::vector<Vector3>& poses)
{
	responPoses.clear();
	responPoses = poses;
}

/**
* バトル設定をする
*/
void BattleManager::BattleSetting()
{
	// チーム体力を設定
	{
		// チーム1の体力を設定
		if (battleInfo->team1Hp > 0)
		{
			team1Hp = std::make_shared<int>(battleInfo->team1Hp);
		}
		// teum1Hpが0以下なら体力をチーム体力を無限にする
		else
		{
			team1Hp = std::make_shared<int>(teamMaxHp);
			//isTeum1HpInfinity = true;
		}

		// チーム2の体力を設定
		if (battleInfo->team1Hp > 0)
		{
			team2Hp = std::make_shared<int>(battleInfo->team2Hp);
		}
		// teum2Hpが0以下なら体力をチーム体力を無限にする
		else
		{
			team2Hp = std::make_shared<int>(teamMaxHp);
			//isTeum2HpInfinity = true;
		}
	}

	// バトル時間を設定
	{
	}

	// コントロールを作成
	{
		std::vector<PilotInfo> pilotInfos = battleInfo->pilotInfos;
		for (int i = 0; i < pilotInfos.size(); ++i)
		{
			PilotInfo pilotInfo = pilotInfos[i];

			// チームIDが0なら出場しない
			if (pilotInfo.teamId == 0)
			{
				continue;
			}

			// パイロットを作成
			GameObjectPtr pilotObj = Instantate(CreateObjectType::Empty);
			pilotObj->name = "Pilot" + std::to_string(i);

			// 人間が操作
			if (pilotInfo.playerId == 0)
			{
				BasePilotPtr pilot = pilotObj->AddComponent<HumanPilot>();

				// コントロール配列に追加
				pilots.push_back(pilot);

				// 機体を作成
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);
				// msに対応する機体コンポーネントを追加してパイロットに設定
				pilot->myMs = SetMs(ms, pilotInfo.ms);

				// カメラを取得して設定
				GameObjectPtr camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
				camera->name = "Camera";
				pilot->myCamera = camera->AddComponent<CameraManager>();

				// チームを設定
				SetTeum(pilot, pilotInfo.teamId);
			}
			// CPUが操作
			else
			{
				BasePilotPtr pilot = pilotObj->AddComponent<CpuPilot>();

				// コントロール配列に追加
				pilots.push_back(pilot);

				// 機体を作成
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);
				// msに対応する機体コンポーネントを追加してパイロットに設定
				pilot->myMs = SetMs(ms, pilotInfo.ms);

				// 仮想カメラを作成
				GameObjectPtr camera = Instantate(CreateObjectType::Empty);
				camera->name = "VirtualCamera";
				pilot->myCamera = camera->AddComponent<CameraManager>();

				// チームを設定
				SetTeum(pilot, pilotInfo.teamId);
			}
		}
	}

	// パイロットに相手チームのパイロットを設定
	{
		for (BasePilotPtr& pilot1 : team1Pilots)
		{
			for (BasePilotPtr& pilot2 : team2Pilots)
			{
				pilot1->SetOtherTeamPilot(pilot2);
			}
		}
		for (BasePilotPtr& pilot2 : team2Pilots)
		{
			for (BasePilotPtr& pilot1 : team2Pilots)
			{
				pilot2->SetOtherTeamPilot(pilot1);
			}
		}
	}

	// 自チーム体力を設定
	{
		for (BasePilotPtr pilot : team1Pilots)
		{
			pilot->SetTeamHP(team1Hp.get(), team2Hp.get());
		}
		for (BasePilotPtr pilot : team1Pilots)
		{
			pilot->SetTeamHP(team2Hp.get(), team1Hp.get());
		}
	}
}

/**
* msに対応するコンポーネントをobjに追加する
*
* @param obj 追加するオブジェクト
* @param ms 追加したいコンポーネントに対応するMsList
*/
BaseMsPtr BattleManager::SetMs(GameObjectPtr obj, MsList ms)
{
	switch (ms)
	{
	case MsList::None:
		return nullptr;
		break;
	case MsList::Gundam:
		return obj->AddComponent<Gundam>();
		break;
	}

	return nullptr;
}


/**
* チームを設定する
*
* @param control	設定するコントロール
* @param id			チームID
*/
void BattleManager::SetTeum(const BasePilotPtr& control, int id)
{
	if (id == 1)
	{
		// チーム1に登録
		team1Pilots.push_back(control);

		// チーム人数が1以上なら自チームのコントロールを設定
		if (team1Pilots.size() > 1)
		{
			control->SetPartnerPilot(team1Pilots[0]);
			team1Pilots[0]->SetPartnerPilot(control);
		}
	}
	else
	{
		// チーム2に登録
		team2Pilots.push_back(control);

		// チーム人数が1以上なら自チームのコントロールを設定
		if (team2Pilots.size() > 1)
		{
			control->SetPartnerPilot(team2Pilots[0]);
			team2Pilots[0]->SetPartnerPilot(control);
		}
	}
}