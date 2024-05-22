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
	// CPUの行動切り替え時間を設定
	cpuTime = 1;
	moveTime = 2;

	moveAxiss.push_back(Vector2::right);
	moveAxiss.push_back(Vector2::left);
	moveAxiss.push_back(Vector2::up);
	moveAxiss.push_back(Vector2::down);
	moveAxiss.push_back(Vector2(1, 1));
	moveAxiss.push_back(Vector2(-1, 1));
	moveAxiss.push_back(Vector2(-1, -1));
	moveAxiss.push_back(Vector2(1, -1));

	// 初期ターゲットを設定
	targetOwner = otherTeumOwner[0];

	// カメラに自身のMSを設定
	lookOnCamera->SetMsTransform(myMs->GetTransform().get());

	// カメラにターゲットを設定
	lookOnCamera->SelectTarget(targetOwner->myMs->GetTransform().get());

	// プレイヤーにカメラ設定
	myMs->SetCamera(lookOnCamera->GetTransform().get());
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

	// HPがゼロになったら機能停止
	if (myMs->IsDeath())
	{
		if (!isMsDeath)
		{
			// 自チームのHpを減らす
			TeumHpSud();
			isMsDeath = true;

			if (*myTeumHp > 0)
			{
				// 自チームの体力が自身の機体のコストより高ければそのままの体力で復活
				if (*myTeumHp > myMs->GetCost())
				{
					myMs->Remove(Vector3(0, 10, -50), 1);
				}
				// 自チームの体力が自身の機体のコストより低ければコストに対して
				else
				{
					float hp = static_cast<float>(*myTeumHp);
					float cost = static_cast<float>(myMs->GetCost());
					float hpCut = (cost - (cost - hp)) / cost;
					myMs->Remove(Vector3(0, 6, -50), hpCut);
				}
				isMsDeath = false;
			}
		}
	}

	if (!myMs->IsDeath())
	{
		MsUpdate();
	}
}

/**
* 機体の更新
*/
void CpuControl::MsUpdate()
{
	auto targetMs = targetOwner->myMs;

	// 自身のMSに相手のMsの情報を伝える
	myMs->SetTargetMS(targetMs.get());

	cpuTimer -= Time::DeltaTime();
	if (cpuTimer <= 0)
	{
		cpuState = (int)Random::Range(CpuState::None, CpuState::Max - 1);
		cpuTimer = cpuTime;
		LOG("%d", cpuState);
	}
	moveTimer -= Time::DeltaTime();
	if (moveTimer <= 0)
	{
		int index = Random::Range(0, (int)moveAxiss.size() - 1);
		cpuMoveAxis = moveAxiss[index];
		moveTimer = moveTime;
	}
	// Cpuの移動処理
	myMs->Move(cpuMoveAxis);

	// ジャンプ
	bool jumpBtn = false;
	if (cpuState == CpuState::Jump)
	{
		jumpBtn = true;
	}
	myMs->Jump(jumpBtn, cpuMoveAxis);

	// ダッシュ
	bool dashBtn = false;
	if (cpuState == CpuState::Dash || cpuState == CpuState::DashAttack)
	{
		dashBtn = true;
	}
	myMs->Dash(dashBtn, cpuMoveAxis);

	// 攻撃1
	bool attackBtn = false;
	if (cpuState == CpuState::Attack || cpuState == CpuState::DashAttack)
	{
		attackBtn = true;
	}
	myMs->Attack1(attackBtn);

	// 攻撃2
	bool attackBtn2 = false;
	if (cpuState == CpuState::Attack2)
	{
		attackBtn2 = true;
	}
	myMs->Attack2(attackBtn);
}

void CpuControl::Finish()
{
}
