/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "FadeOut.h"

#include "CameraManager.h"

#include "BaseMs.h"
#include "Ms/Gundam.h"

#include "HumanPilot.h"
#include "CpuPilot.h"

#include "../Global.h"
#include "../GameSoundName.h"

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

		//battleInfo->pilotInfos[2].teamId = 2;
		//battleInfo->pilotInfos[2].playerId = 1;
		//battleInfo->pilotInfos[2].ms = MsList::Gundam;

		//battleInfo->pilotInfos[3].teamId = 1;
		//battleInfo->pilotInfos[3].playerId = 1;
		//battleInfo->pilotInfos[3].ms = MsList::Gundam;

		battleInfo->team1Hp = teamMaxHp;
		battleInfo->team2Hp = teamMaxHp;
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

	//audioBGM = OwnerObject()->AddComponent<AudioSource>();
	//audioBGM->SetSoundFilename(GameSound::BGM::battle01);
	//audioBGM->isLooop = true;
	//audioBGM->Play();
}

/**
* 最初に実行
*/
void BattleManager::Start()
{
	SetBattlePosition(team1Pilots, 0);
	SetBattlePosition(team2Pilots, 1);

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
	{
	}

	break;
	case BattleManager::BattleState::Standbay:
	{
	}
	break;
	case BattleManager::BattleState::GO:
	{
	}
	break;
	case BattleManager::BattleState::Battle:
	{

	}
	break;
	case BattleManager::BattleState::Victory:
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
			team1Hp = battleInfo->team1Hp;
		}

		// チーム2の体力を設定
		if (battleInfo->team1Hp > 0)
		{
			team2Hp = battleInfo->team2Hp;
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
				pilot->myMs = CreateMs(pilotInfo.ms);

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
				pilot->myMs = CreateMs(pilotInfo.ms);

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
	}
}

/**
* オブジェクトを生成しmsに対応したコンポーネントを追加する
*
* @param ms 追加したいコンポーネントに対応するMsList
*/
BaseMsPtr BattleManager::CreateMs(MsList ms)
{
	// 機体を生成
	GameObjectPtr obj = Instantate(CreateObjectType::Empty);
	obj->tag = "Ms";

	// msに対応したコンポーネントを追加する
	switch (ms)
	{
	case MsList::Gundam:
		return obj->AddComponent<Gundam>();
		break;
	}

	// 対応したコンポーネントがないのでオブジェクトを破壊する
	obj->Destroy();
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

/**
* バトルスタート位置を設定する
*
* @param pilots	配置するパイロット
* @param id		チームID
*/
void BattleManager::SetBattlePosition(const std::vector<BasePilotPtr>& pilots, int id)
{
	// リスポーン位置が２個以上なければ何もしない
	if (responPoses.size() < 2)
	{
		return;
	}

	// MSの出撃位置を設定
	for (int i = 0; i < pilots.size(); ++i)
	{
		BasePilotPtr pilot = pilots[i];

		pilot->myMs->GetTransform()->position = responPoses[id] + Vector3(10.0f * i, 0, 0);

		// リスポーン位置を設定
		pilot->responPoss = responPoses;

		Vector3 toTargetVector;
		if (id == 0)
		{
			toTargetVector = Vector3::Normalize(responPoses[1] - responPoses[0]);
		}
		else
		{
			toTargetVector = Vector3::Normalize(responPoses[0] - responPoses[1]);
		}
		pilot->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector);
	}
}
