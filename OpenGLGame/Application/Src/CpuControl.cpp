/**
* @file CpuControl.cpp
*/
#include "CpuControl.h"
#include "BaseMs.h"
#include "Global.h"

void CpuControl::Start()
{
	cpuTime = 2;
	moveTime = 5;
}

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
			TeumHpSud();
			isMsDeath = true;
			
			if (*myTeumHp > 0)
			{
				// 自チームの体力が自身の機体のコストより高ければそのままの体力で復活
				if (*myTeumHp > myMs->GetCost())
				{
					myMs->Remove(Vector3(0, 6, -50), 1);		
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
		return;
	}

	MsUpdate();
}

/**
* 機体の更新
*/
void CpuControl::MsUpdate()
{
	auto targetMs = otherOwner->myMs;

	// 自身のMSに相手のMsの情報を伝える
	myMs->SetTargetMS(targetMs.get());

	cpuTimer -= Time::DeltaTime();
	if (cpuTimer <= 0)
	{
		cpuState = (int)Random::Range(CpuState::None, CpuState::Attack);
		cpuTimer = cpuTime;
		LOG("%d", cpuState);
	}
	moveTimer -= Time::DeltaTime();
	if (moveTimer <= 0)
	{
		cpuMoveAxis.x = Random::Range(-1.0f, 1.0f);
		cpuMoveAxis.y = Random::Range(-1.0f, 1.0f);
		moveTimer = moveTime;
	}
	// Cpuの移動処理
	myMs->CpuMove(cpuMoveAxis);

	bool attack = cpuState == CpuState::Attack ? true : false;
	myMs->Attack1(attack);
	if (attack)
	{
		cpuState = 0;
	}

}

void CpuControl::Finish()
{
}
