/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "PlayerControl.h"
#include "CpuControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "Gundam.h"
#include "Global.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::WindowSystem;
using namespace FGEngine::InputSystem;
using namespace FGEngine::SceneSystem;

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
* 生成時に実行
*/
void BattleManager::Awake()
{
	// 各マネージャを取得
	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// バトル情報を設定
	teum1Hp = std::make_shared<int>(battleInfo->teum1Hp);
	teum2Hp = std::make_shared<int>(battleInfo->teum2Hp);
	battleTime = battleInfo->time;

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
			auto hyumanControl = player->AddComponent<PlayerControl>();

			// 機体を設定
			auto ms = Instantate("MS" + std::to_string(i), Vector3(0, 6, 50));

			// 対応するMsコンポーネントを追加
			hyumanControl->myMs = SetMs(ms, x->ms);

			// カメラを設定
			auto camera = ObjectManager::GetInstance()->GetMainCamera();
			hyumanControl->lookOnCamera = camera->AddComponent<LookOnCamera>();

			// チームを設定
			if (x->teumId == 1)
			{
				teum1ControlOwners.push_back(hyumanControl);
				// チーム人数が1以上なら自チームのオーナを設定
				if (teum1ControlOwners.size() > 1)
				{
					hyumanControl->myTeumOtherOwner = teum1ControlOwners.begin()->get();
					teum1ControlOwners.begin()->get()->myTeumOtherOwner = hyumanControl.get();
				}
			}
			else if (x->teumId == 2)
			{
				teum2ControlOwners.push_back(hyumanControl);
				// チーム人数が1以上なら自チームのオーナを設定
				if (teum2ControlOwners.size() > 1)
				{
					hyumanControl->myTeumOtherOwner = teum2ControlOwners.begin()->get();
					teum2ControlOwners.begin()->get()->myTeumOtherOwner = hyumanControl.get();
				}
			}
		}
		else if (x->playerId == 1)
		{
			auto cpuControl = player->AddComponent<CpuControl>();

			// 機体を設定
			auto ms = Instantate("MS" + std::to_string(i), Vector3(0, 6, -50));

			// 対応するMsコンポーネントを追加
			cpuControl->myMs = SetMs(ms, x->ms);

			// 仮想カメラを設定
			auto camera = Instantate("virtualCamera");
			cpuControl->lookOnCamera = camera->AddComponent<LookOnCamera>();

			// チームを設定
			if (x->teumId == 1)
			{
				teum1ControlOwners.push_back(cpuControl);
				// チーム人数が1以上なら自チームのオーナを設定
				if (teum1ControlOwners.size() > 1)
				{
					cpuControl->myTeumOtherOwner = teum1ControlOwners.begin()->get();
					teum1ControlOwners.begin()->get()->myTeumOtherOwner = cpuControl.get();
				}
			}
			else if (x->teumId == 2)
			{
				teum2ControlOwners.push_back(cpuControl);
				// チーム人数が1以上なら自チームのオーナを設定
				if (teum2ControlOwners.size() > 1)
				{
					cpuControl->myTeumOtherOwner = teum2ControlOwners.begin()->get();
					teum2ControlOwners.begin()->get()->myTeumOtherOwner = cpuControl.get();
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
				teum1->otherTeumOwner.push_back(teum2.get());
			}
		}
		for (auto teum2 : teum2ControlOwners)
		{
			for (auto teum1 : teum1ControlOwners)
			{
				teum2->otherTeumOwner.push_back(teum1.get());
			}
		}}

	// 自チーム体力を設定
	{
		for (auto teum1 : teum1ControlOwners)
		{
			teum1->SetMyTeumHP(teum1Hp.get());
		}
		for (auto teum2 : teum2ControlOwners)
		{
			teum2->SetMyTeumHP(teum2Hp.get());
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
}

/**
* 最初に実行
*/
void BattleManager::Start()
{
	// UIを非表示
	imgStandbay->SetEnable(false);
	imgGoBack->SetEnable(false);
	imgGo->SetEnable(false);
	imgWin->SetEnable(false);
	imgLose->SetEnable(false);
}

/**
* 毎フレーム実行
*/
void BattleManager::Update()
{
	switch (state)
	{
	case BattleManager::GameState::Ready:
		timer += Time::DeltaTime();
		if (timer > readyTime)
		{
			imgStandbay->SetEnable(true);
			state = GameState::Standbay;
			timer = 0;
		}
		break;
	case BattleManager::GameState::Standbay:

	{
		timer += Time::DeltaTime();
		if (timer > standbayTime)
		{
			imgStandbay->SetEnable(false);
			imgGoBack->SetEnable(true);
			imgGo->SetEnable(true);
			state = GameState::GO;
			timer = 0;
		}
	}

	break;
	case BattleManager::GameState::GO:
	{
		timer += Time::DeltaTime();;
		if (timer > goTime)
		{
			imgGo->SetEnable(false);
			imgGoBack->SetEnable(false);

			// オーナにスタートを伝える
			for (auto teum1 : teum1ControlOwners)
			{
				teum1->isStart = true;
			}
			for (auto teum2 : teum2ControlOwners)
			{
				teum2->isStart = true;
			}

			state = GameState::Battle;
		}
	}
	break;
	case BattleManager::GameState::Battle:

		if (*teum1Hp <= 0)
		{
			imgLose->SetEnable(true);
			state = GameState::Victory;
		}
		else if (*teum2Hp <= 0)
		{
			imgWin->SetEnable(true);
			state = GameState::Victory;
		}
		break;
	case BattleManager::GameState::Victory:

		// オーナに終了処理をさせる
		for (auto teum1 : teum1ControlOwners)
		{
			teum1->Finish();
			teum1->SetEnable(false);
		}
		for (auto teum2 : teum2ControlOwners)
		{
			teum2->Finish();
			teum2->SetEnable(false);
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
