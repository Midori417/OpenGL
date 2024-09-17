/**
* @file CpuControl.cpp
*/
#include "CpuControl.h"
#include "BaseMs.h"
#include "Global.h"

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

}

/**
* コントロールをスタートする
*/
void CpuControl::ControlStart()
{
	isStart = true;
}

/**
* ゲーム入力を更新
*/
void CpuControl::GameInputUpdate()
{
	//return;
	auto targetMs = targetOwner->myMs;

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
	gameInput->action1Btn = false;
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
	// 攻撃3
	gameInput->action3Btn = false;
	if (cpuState == CpuState::Attack3)
	{
		if (!targetMs->IsDeath())
		{
			gameInput->action3Btn = true;
		}
	}

	if (targetNum == 0)
	{
		gameInput->targetChangeBtn = true;
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