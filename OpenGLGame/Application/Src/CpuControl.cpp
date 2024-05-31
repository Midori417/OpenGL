/**
* @file CpuControl.cpp
*/
#include "CpuControl.h"
#include "BaseMs.h"
#include "Global.h"
#include "LookOnCamera.h"

/**
* 最初に実行
*/
void CpuControl::Start()
{
	// 初期する
	Initialize();

	// CPUの行動切り替え時間を設定
	cpuTime = 1;
	moveTime = 2;

	// 仮想入力軸を作成
	moveAxiss.push_back(Vector2::right);
	moveAxiss.push_back(Vector2::left);
	moveAxiss.push_back(Vector2::up);
	moveAxiss.push_back(Vector2::down);
	moveAxiss.push_back(Vector2(1, 1));
	moveAxiss.push_back(Vector2(-1, 1));
	moveAxiss.push_back(Vector2(-1, -1));
	moveAxiss.push_back(Vector2(1, -1));
}

/**
* 毎フレーム実行
*/
void CpuControl::Update()
{
	if (!isStart)
	{
		return;
	}

	// 自身の機体が死んだら
	if (myMs->IsDeath())
	{
		if (!isMsDeath)
		{
			if (!GetTeumHPInifinit())
			{
				// 自チームのHpを減らす
				TeumHpSud();
			}
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
	GameInputUpdate();

	// ターゲット切り替え
	if (gameInput->targetChangeBtn && otherTeamOwner.size() > 0)
	{
		if (targetOwner == otherTeamOwner[0])
		{
			if (!otherTeamOwner[1]->myMs->IsDeath())
			{
				targetOwner = otherTeamOwner[1];
				// カメラと機体にターゲットを持たせる
				myMs->SetTargetMS(targetOwner->myMs.get());
				myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
			}
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			if (!otherTeamOwner[0]->myMs->IsDeath())
			{
				targetOwner = otherTeamOwner[0];
				// カメラと機体にターゲットを持たせる
				myMs->SetTargetMS(targetOwner->myMs.get());
				myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
			}
		}
		gameInput->targetChangeBtn = false;
	}
	// ターゲットの機体が死んだら
	if (targetOwner->myMs->IsDeath() && otherTeamOwner.size() > 0)
	{
		if (targetOwner == otherTeamOwner[0])
		{
			if (!otherTeamOwner[1]->myMs->IsDeath())
			{
				targetOwner = otherTeamOwner[1];
				// カメラと機体にターゲットを持たせる
				myMs->SetTargetMS(targetOwner->myMs.get());
				myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
			}
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			if (!otherTeamOwner[0]->myMs->IsDeath())
			{
				targetOwner = otherTeamOwner[0];
				// カメラと機体にターゲットを持たせる
				myMs->SetTargetMS(targetOwner->myMs.get());
				myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
			}
		}
	}
}

/**
* 終了処理
*/
void CpuControl::Finish(VictoryState victoryState)
{
	// 基底を停止
	myMs->Stop();
}

/**
* ゲーム入力を更新
*/
void CpuControl::GameInputUpdate()
{
	// MSが死んでいれか、操作が許可されていなければ何もしない
	if (myMs->IsDeath() || !isMsControl)
	{
		return;
	}

	auto targetMs = targetOwner->myMs;

	// 自身のMSに相手のMsの情報を伝える
	myMs->SetTargetMS(targetMs.get());

	// 移動方向を乱数で決める
	moveTimer -= Time::DeltaTime();
	if (moveTimer <= 0)
	{
		int index = Random::Range(0, (int)moveAxiss.size() - 1);
		cpuMoveAxis = moveAxiss[index];
		moveTimer = moveTime;
	}
	gameInput->moveAxis = cpuMoveAxis;

	// 行動を乱数で決める
	cpuTimer -= Time::DeltaTime();
	if (cpuTimer <= 0)
	{
		cpuState = (int)Random::Range(CpuState::None, CpuState::Max - 1);
		cpuTimer = cpuTime;
		targetNum = (int)Random::Range(0, static_cast<int>(otherTeamOwner.size() - 1));
	}


	// ジャンプ
	gameInput->jumpBtn = false;
	if (cpuState == CpuState::Jump)
	{
		gameInput->jumpBtn = true;
	}

	// ダッシュ
	gameInput->dashBtn = false;
	if (cpuState == CpuState::Dash || cpuState == CpuState::DashAttack)
	{
		gameInput->dashBtn = true;
	}

	// 攻撃1
	gameInput->action1Btn= false;
	if (cpuState == CpuState::Attack || cpuState == CpuState::DashAttack)
	{
		if (!targetMs->IsDeath())
		{
			gameInput->action1Btn = true;
		}
	}

	// 攻撃2
	gameInput->action2Btn = false;
	if (cpuState == CpuState::Attack2)
	{
		if (!targetMs->IsDeath())
		{
			gameInput->action2Btn = true;
		}
	}

	if (targetNum == 0)
	{
		gameInput->targetChangeBtn = true;
	}
}