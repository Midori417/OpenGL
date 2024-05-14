/**
* @file BattleManager.cpp
*/
#include "BattleManager.h"
#include "PlayerControl.h"
#include "CpuControl.h"
#include "LookOnCamera.h"
#include "BaseMs.h"
#include "Gundam.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::WindowSystem;


/**
* 最初に実行
*/
void BattleManager::Start()
{
	// プレイヤーを作成
	{
		auto playerObj = Instantate("Player");
		playerControl = playerObj->AddComponent<PlayerControl>();

		// テスト(後で選択できるようにする)
		playerControl->ms = MsList::Gundam;

		// プレイヤーの機体を作成
		{
			auto playerMs = Instantate("MyMs", Vector3(0, 6, 50), Quaternion::AngleAxis(180, Vector3::up));;
			// 対応するコンポーネントを追加
			playerControl->myMs = SetMs(playerMs, playerControl->ms);
		}
		// カメラをロックオンカメラに変更
		{
			auto camera = ObjectManager::GetInstance()->GetMainCamera();
			playerControl->lookOnCamera = camera->AddComponent<LookOnCamera>();
		}
	}
	// CPUを作成
	{
		auto cpuObj = Instantate("CPU");
		cpuControl = cpuObj->AddComponent<CpuControl>();
		cpuControl->ms = MsList::Gundam;
		// CPUの機体を作成
		{
			auto cpuMs = Instantate("CpuMs", Vector3(0, 6, -50));
			cpuControl->myMs = SetMs(cpuMs, cpuControl->ms);
		}
	}

	// お互いのコントローラーの情報を設定
	playerControl->otherOwner = cpuControl.get();
	cpuControl->otherOwner = playerControl.get();

	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();
	// StadByUI
	{
		auto standbay = Instantate("Standbay");
		imgStandbay = standbay->AddComponent<Image>();
		imgStandbay->texture = resManager->GetTexture("STANDBAY");
		imgStandbay->size = winManager->GetWindowSize();
	}
	{
		auto goBack = Instantate("GoBack");
		imgGoBack = goBack->AddComponent<Image>();
		imgGoBack->texture = resManager->GetTexture("GoBack");
		imgGoBack->size = winManager->GetWindowSize();
	}
	{
		auto go = Instantate("Go");
		imgGo = go->AddComponent<Image>();
		imgGo->texture = resManager->GetTexture("GO");
		imgGo->size = winManager->GetWindowSize() * 0.9f;
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
		imgGo->size += 10000 * Time::DeltaTime();
		if (timer > goTime)
		{
			imgGo->SetEnable(false);
			imgGoBack->SetEnable(false);

			playerControl->isStart = true;
			cpuControl->isStart = true;

			state = GameState::Battle;
		}
	}
		break;
	case BattleManager::GameState::Battle:
		break;
	default:
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
