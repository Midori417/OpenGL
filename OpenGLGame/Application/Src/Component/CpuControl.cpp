/**
* @file CpuControl.cpp
*/
#include "CpuControl.h"
#include "FGEngine/Other/Time.h"
#include "FGEngine/Other/Random.h"

#include "BaseMs.h"

/**
* Updateが始まる前に一度実行
*/
void CpuControl::Start()
{
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
	// スタート合図が出ていければ何もしない
	if (!IsStart())
	{
		return;
	}

	GameInputUpdate();

	// 破壊されていなければ
	if (!myMs->IsDestroy())
	{
		myMs->SetDistance(GetDistance());
		TargetUpdate();
	}
}

/**
* 機体の操作を更新
*/
void CpuControl::GameInputUpdate()
{
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
		targetNum = (int)Random::Range(0, static_cast<int>(otherTeamControls.size() - 1));
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
		gameInput->action1Btn = true;
	}

	// 攻撃2
	gameInput->action2Btn = false;
	if (cpuState == CpuState::Attack2)
	{
		gameInput->action2Btn = true;
	}
	// 攻撃3
	gameInput->action3Btn = false;
	if (cpuState == CpuState::Attack3)
	{
		gameInput->action3Btn = true;
	}

	if (targetNum == 0)
	{
		gameInput->targetChangeBtn = true;
	}
}
