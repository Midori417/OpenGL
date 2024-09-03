/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "HumanControl.h"
#include "CpuControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "Gundam.h"
#include "Global.h"
#include "BgmList.h"
using namespace FGEngine::SoundSystem;

// スタティック変数を初期化
BattleInfoPtr BattleManager::battleInfo = nullptr;

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
* @param pos リスポーン位置
*/
void BattleManager::SetResponPos(const Vector3& pos)
{
	responPoses.push_back(pos);
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
* 生成時に実行
*/
void BattleManager::Awake()
{
	// 各マネージャを取得
	auto resManager = AssetManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// バトル情報を設定
	if (battleInfo->teum1Hp > 0)
	{
		teum1Hp = std::make_shared<int>(battleInfo->teum1Hp);
	}
	if (battleInfo->teum1Hp > 0)
	{
		teum2Hp = std::make_shared<int>(battleInfo->teum2Hp);
	}

	battleTimer = battleInfo->time;

	// コントロールの作成
	int i = 0;
	for (auto x : battleInfo->controlInfo)
	{
		// チームIDが0なら出場なし
		if (x->teumId == 0)
		{
			i++;
			continue;
		}
		// プレイヤーを作成
		auto player = Instantate("Player" + std::to_string(i));

		// 誰が操作するかを設定
		if (x->playerId == 0)
		{
			auto hyumanControl = player->AddComponent<HumanControl>();
			controlOwners.push_back(hyumanControl);

			// 機体を設定
			auto ms = Instantate("MS" + std::to_string(i));

			// 対応するMsコンポーネントを追加
			hyumanControl->myMs = SetMs(ms, x->ms);

			// カメラを設定
			auto camera = OwnerObject()->GetScene()->GetMainCameraInfo()->OwnerObject();
			hyumanControl->myCamera = camera->AddComponent<LookOnCamera>();
			auto linstner = camera->AddComponent<AudioListner>();
			SoundManager::GetInstance()->SetListner(linstner);
			// チームを設定
			if (x->teumId == 1)
			{
				teum1ControlOwners.push_back(hyumanControl);
				// チーム人数が1以上なら自チームのオーナを設定
				if (teum1ControlOwners.size() > 1)
				{
					hyumanControl->myTeamOtherOwner = teum1ControlOwners.begin()->get();
					teum1ControlOwners.begin()->get()->myTeamOtherOwner = hyumanControl.get();
				}
			}
			else if (x->teumId == 2)
			{
				teum2ControlOwners.push_back(hyumanControl);
				// チーム人数が1以上なら自チームのオーナを設定
				if (teum2ControlOwners.size() > 1)
				{
					hyumanControl->myTeamOtherOwner = teum2ControlOwners.begin()->get();
					teum2ControlOwners.begin()->get()->myTeamOtherOwner = hyumanControl.get();
				}
			}
		}
		else if (x->playerId == 1)
		{
			auto cpuControl = player->AddComponent<CpuControl>();
			controlOwners.push_back(cpuControl);

			// 機体を設定
			auto ms = Instantate("MS" + std::to_string(i));

			// 対応するMsコンポーネントを追加
			cpuControl->myMs = SetMs(ms, x->ms);

			// 仮想カメラを設定
			auto camera = Instantate("virtualCamera");
			cpuControl->myCamera = camera->AddComponent<LookOnCamera>();

			// チームを設定
			if (x->teumId == 1)
			{
				teum1ControlOwners.push_back(cpuControl);
				// チーム人数が1以上なら自チームのオーナを設定
				if (teum1ControlOwners.size() > 1)
				{
					cpuControl->myTeamOtherOwner = teum1ControlOwners.begin()->get();
					teum1ControlOwners.begin()->get()->myTeamOtherOwner = cpuControl.get();
				}
			}
			else if (x->teumId == 2)
			{
				teum2ControlOwners.push_back(cpuControl);
				// チーム人数が1以上なら自チームのオーナを設定
				if (teum2ControlOwners.size() > 1)
				{
					cpuControl->myTeamOtherOwner = teum2ControlOwners.begin()->get();
					teum2ControlOwners.begin()->get()->myTeamOtherOwner = cpuControl.get();
				}
			}
		}

		i++;
	}

	// 相手チームのオーナを設定
	{
		for (auto teum1 : teum1ControlOwners)
		{
			for (auto teum2 : teum2ControlOwners)
			{
				teum1->otherTeamOwner.push_back(teum2.get());
			}
		}
		for (auto teum2 : teum2ControlOwners)
		{
			for (auto teum1 : teum1ControlOwners)
			{
				teum2->otherTeamOwner.push_back(teum1.get());
			}
		}
	}

	// 自チーム体力を設定
	{
		for (auto teum1 : teum1ControlOwners)
		{
			teum1->SetTeamHP(teum1Hp.get(), teum2Hp.get());
		}
		for (auto teum2 : teum2ControlOwners)
		{
			teum2->SetTeamHP(teum2Hp.get(), teum1Hp.get());
		}
	}

	// UI
	{
		// STANBAYを作成
		{
			auto standbay = Instantate("Standbay");
			imgStandbay = standbay->AddComponent<Image>();
			imgStandbay->texture = resManager->GetTexture("STANDBAY");
			imgStandbay->size = winManager->GetWindowSize();
		}
		// GOの背景を作成
		{
			auto goBack = Instantate("GoBack");
			imgGoBack = goBack->AddComponent<Image>();
			imgGoBack->texture = resManager->GetTexture("GoBack");
			imgGoBack->size = winManager->GetWindowSize();
		}
		// GOを作成
		{
			auto go = Instantate("Go");
			imgGo = go->AddComponent<Image>();
			imgGo->texture = resManager->GetTexture("GO");
			imgGo->size = winManager->GetWindowSize() * 0.9f;
		}
	}

	audioSource = OwnerObject()->AddComponent<AudioSource>();
	audioSource->SetSoundFilename(BGM::bgm01);
	audioSource->SetVolume(0.05f);
	audioSource->isLooop = true;
}

/**
* 最初に実行
*/
void BattleManager::Start()
{
	// MSの出撃位置を設定
	for (int i = 0; i < teum1ControlOwners.size(); ++i)
	{
		auto teum1 = teum1ControlOwners[i];

		teum1->myMs->GetTransform()->position = responPoses[0] + Vector3(10.0f * i, 0, 0);
		teum1->responPoss = responPoses;

		Vector3 toTargetVector = Vector3::Normalize(responPoses[1] - responPoses[0]);
		teum1->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}
	for (int i = 0; i < teum2ControlOwners.size(); ++i)
	{
		auto teum2 = teum2ControlOwners[i];

		teum2->myMs->GetTransform()->position = responPoses[1] + Vector3(10.0f * i, 0, 0);

		// リスポーン位置を設定
		teum2->responPoss = responPoses;

		Vector3 toTargetVector = Vector3::Normalize(responPoses[0] - responPoses[1]);
		teum2->myMs->GetTransform()->rotation = Quaternion::LookRotation(toTargetVector * Vector3(0, 0, 1));
	}

	// UIを非表示
	imgStandbay->SetEnable(false);
	imgGoBack->SetEnable(false);
	imgGo->SetEnable(false);

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
			imgStandbay->SetEnable(true);

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
			imgStandbay->SetEnable(false);
			// GOを表示
			imgGo->SetEnable(true);

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

			audioSource->Play();

			// GOを非表示に
			imgGo->SetEnable(false);

			// コントロールの処理を開始させる
			for (auto teum1 : teum1ControlOwners)
			{
				teum1->ControlStart();
			}
			for (auto teum2 : teum2ControlOwners)
			{
				teum2->ControlStart();
			}
		}
	}
	break;
	case BattleManager::BattleState::Battle:

		// バトル中
	{
		// バトル時間を減らす
		battleTimer -= Time::DeltaTime();

		if (*teum1Hp <= 0 || *teum2Hp <= 0)
		{
			audioSource->Stop();
			VictoryState teum1Victory = VictoryState::None;
			VictoryState teum2Victory = VictoryState::None;
			// どちらのチームHpも0ならば引き分け
			if (*teum1Hp <= 0 && *teum2Hp <= 0)
			{
				teum1Victory = VictoryState::Drow;
				teum2Victory = VictoryState::Drow;
			}
			else if (*teum1Hp <= 0)
			{
				teum1Victory = VictoryState::Lose;
				teum2Victory = VictoryState::Win;
			}
			else if (*teum2Hp <= 0)
			{
				teum1Victory = VictoryState::Win;
				teum2Victory = VictoryState::Lose;
			}

			// 終了処理させる
			for (auto teum1 : teum1ControlOwners)
			{
				teum1->Finish(teum1Victory);
				teum1->isActive = false;
			}
			for (auto teum2 : teum2ControlOwners)
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
			SceneManager::LoadScene("バトル設定シーン");
		}
	}

	break;
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
