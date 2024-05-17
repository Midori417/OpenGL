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

	// HP���[���ɂȂ�����@�\��~
	if (myMs->IsDeath())
	{
		if (!isMsDeath)
		{
			TeumHpSud();
			isMsDeath = true;
			
			if (*myTeumHp > 0)
			{
				// ���`�[���̗̑͂����g�̋@�̂̃R�X�g��荂����΂��̂܂܂̗̑͂ŕ���
				if (*myTeumHp > myMs->GetCost())
				{
					myMs->Remove(Vector3(0, 6, -50), 1);		
				}
				// ���`�[���̗̑͂����g�̋@�̂̃R�X�g���Ⴏ��΃R�X�g�ɑ΂���
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
* �@�̂̍X�V
*/
void CpuControl::MsUpdate()
{
	auto targetMs = otherOwner->myMs;

	// ���g��MS�ɑ����Ms�̏���`����
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
	// Cpu�̈ړ�����
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
