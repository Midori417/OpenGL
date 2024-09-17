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
	auto resManager = AssetManager::GetInstance();

	// フェードオブジェクトを作成
	{
		auto obj = Instantate(resManager->GetGameObject("FadeObject"));
		fadeOut = obj->GetComponent<FadeOut>();
	}

	// バトル情報を作成
	battleInfo = std::make_shared<BattleInfo>();
	{
		// 配列を予約
		battleInfo->controlInfo.reserve(playerMax);
		for (int i = 0; i < playerMax; ++i)
		{
			battleInfo->controlInfo.push_back(std::make_shared<ControlInfo>());
		}

		// テスト
		battleInfo->controlInfo[0]->teamId = 1;
		battleInfo->controlInfo[0]->playerId = 0;
		battleInfo->controlInfo[0]->ms = MsList::Gundam;

		battleInfo->controlInfo[1]->teamId = 2;
		battleInfo->controlInfo[1]->playerId = 1;
		battleInfo->controlInfo[1]->ms = MsList::Gundam;

		battleInfo->controlInfo[2]->teamId = 2;
		battleInfo->controlInfo[2]->playerId = 1;
		battleInfo->controlInfo[2]->ms = MsList::Gundam;

		battleInfo->controlInfo[3]->teamId = 1;
		battleInfo->controlInfo[3]->playerId = 1;
		battleInfo->controlInfo[3]->ms = MsList::Gundam;

		// バトル情報を設定
		if (battleInfo->team1Hp > 0)
		{
			team1Hp = std::make_shared<int>(battleInfo->team1Hp);
		}
		if (battleInfo->team1Hp > 0)
		{
			team2Hp = std::make_shared<int>(battleInfo->team2Hp);
		}
	}

	//// コントロールの作成
	//int i = 0;
	//for (auto x : battleInfo->controlInfo)
	//{
	//	// チームIDが0なら出場なし
	//	if (x->teamId == 0)
	//	{
	//		i++;
	//		continue;
	//	}
	//	// プレイヤーを作成
	//	auto player = Instantate(CreateObjectType::Empty);
	//	player->name = "Player" + std::to_string(i);
	//	// 誰が操作するかを設定
	//	if (x->playerId == 0)
	//	{
	//		auto hyumanControl = player->AddComponent<HumanPilot>();
	//		pilots.push_back(hyumanControl);
	//		// 機体を設定
	//		auto ms = Instantate(CreateObjectType::Empty);
	//		ms->name = "MS" + std::to_string(i);
	//		// 対応するMsコンポーネントを追加
	//		hyumanControl->myMs = SetMs(ms, x->ms);
	//		// カメラを設定
	//		auto camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
	//		camera->name = "PlayerCamera";
	//		hyumanControl->myCamera = camera->AddComponent<CameraManager>();
	//		// チームを設定
	//		if (x->teumId == 1)
	//		{
	//			team1Pilots.push_back(hyumanControl);
	//			// チーム人数が1以上なら自チームのオーナを設定
	//			if (team1Pilots.size() > 1)
	//			{
	//				hyumanControl->myTeamOtherOwner = team1Pilots.begin()->get();
	//				team1Pilots.begin()->get()->myTeamOtherOwner = hyumanControl.get();
	//			}
	//		}
	//		else if (x->teumId == 2)
	//		{
	//			team2Pilots.push_back(hyumanControl);
	//			// チーム人数が1以上なら自チームのオーナを設定
	//			if (team2Pilots.size() > 1)
	//			{
	//				hyumanControl->myTeamOtherOwner = team2Pilots.begin()->get();
	//				team2Pilots.begin()->get()->myTeamOtherOwner = hyumanControl.get();
	//			}
	//		}
	//	}
	//	else if (x->playerId == 1)
	//	{
	//		auto cpuControl = player->AddComponent<CpuPilot>();
	//		pilots.push_back(cpuControl);
	//		// 機体を設定
	//		auto ms = Instantate(CreateObjectType::Empty);
	//		ms->name = "MS" + std::to_string(i);
	//		// 対応するMsコンポーネントを追加
	//		cpuControl->myMs = SetMs(ms, x->ms);
	//		// 仮想カメラを設定
	//		auto camera = Instantate(CreateObjectType::Empty);
	//		camera->name = "VitualCaemra";
	//		cpuControl->myCamera = camera->AddComponent<CameraManager>();
	//		// チームを設定
	//		if (x->teumId == 1)
	//		{
	//			team1Pilots.push_back(cpuControl);
	//			// チーム人数が1以上なら自チームのオーナを設定
	//			if (team1Pilots.size() > 1)
	//			{
	//				cpuControl->myTeamOtherOwner = team1Pilots.begin()->get();
	//				team1Pilots.begin()->get()->myTeamOtherOwner = cpuControl.get();
	//			}
	//		}
	//		else if (x->teumId == 2)
	//		{
	//			team2Pilots.push_back(cpuControl);
	//			// チーム人数が1以上なら自チームのオーナを設定
	//			if (team2Pilots.size() > 1)
	//			{
	//				cpuControl->myTeamOtherOwner = team2Pilots.begin()->get();
	//				team2Pilots.begin()->get()->myTeamOtherOwner = cpuControl.get();
	//			}
	//		}
	//	}
	//	i++;
	//}

	// 相手チームのオーナを設定
	{
		for (auto teum1 : team1Pilots)
		{
			for (auto teum2 : team2Pilots)
			{
				teum1->otherTeamOwner.push_back(teum2.get());
			}
		}
		for (auto teum2 : team2Pilots)
		{
			for (auto teum1 : team1Pilots)
			{
				teum2->otherTeamOwner.push_back(teum1.get());
			}
		}
	}

	// 自チーム体力を設定
	{
		for (auto teum1 : team1Pilots)
		{
			teum1->SetTeamHP(team1Hp.get(), team2Hp.get());
		}
		for (auto teum2 : team2Pilots)
		{
			teum2->SetTeamHP(team2Hp.get(), team1Hp.get());
		}
	}

	// UI
	{
		// STANBAYを作成
		{
			auto standbay = Instantate(CreateObjectType::Empty);
			standbay->name = "Standby";
			imgStandbay = standbay->AddComponent<Image>();
			imgStandbay->texture = resManager->GetTexture("Standby");
			imgStandbay->SetWindowSize();
		}
		// GOを作成
		{
			auto go = Instantate(CreateObjectType::Empty);
			go->name = "Go";
			imgGo = go->AddComponent<Image>();
			imgGo->texture = resManager->GetTexture("Go");
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
		auto controllInfos = battleInfo->controlInfo;
		for (int i = 0; i < controllInfos.size(); ++i)
		{
			auto info = controllInfos[i];

			// チームIDが0なら出場しない
			if (info->teamId == 0)
			{
				continue;
			}

			// プレイヤーを作成
			auto player = Instantate(CreateObjectType::Empty);
			player->name = "Player" + std::to_string(i);

			// 人間が操作
			if (info->playerId == 0)
			{
				auto control = player->AddComponent<HumanPilot>();

				// コントロール配列に追加
				pilots.push_back(control);

				// 機体を作成
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);

				// msにMSListに対応するコンポーネントを追加
				control->myMs = SetMs(ms, info->ms);

				// カメラを取得して設定
				auto camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
				control->myCamera = camera->AddComponent<CameraManager>();

				// チームを設定
				//SetTeum(control, info->teamId);
			}
			// CPUが操作
			else
			{
				auto control = player->AddComponent<CpuPilot>();

				// コントロール配列に追加
				pilots.push_back(control);

				// 機体を作成
				GameObjectPtr ms = Instantate(CreateObjectType::Empty);

				// msにMSListに対応するコンポーネントを追加
				control->myMs = SetMs(ms, info->ms);

				// 仮想カメラを作成
				auto camera = Instantate(CreateObjectType::Empty);
				control->myCamera = camera->AddComponent<CameraManager>();

				// チームを設定
				//SetTeum(control, info->teamId);
			}
		}
	}
	// コントロールに相手にチームのコントロールを設定
	{
		for (auto teum1 : team1Pilots)
		{
			for (auto teum2 : team2Pilots)
			{
				//teum1->otherTeamControls.push_back(teum2.get());
			}
		}
		for (auto teum2 : team2Pilots)
		{
			for (auto teum1 : team2Pilots)
			{
				//teum2->otherTeamControls.push_back(teum1.get());
			}
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
