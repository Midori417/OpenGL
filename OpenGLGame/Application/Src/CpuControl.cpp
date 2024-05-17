/**
* @file CpuControl.cpp
*/
#include "CpuControl.h"
#include "BaseMs.h"
#include "Global.h"
#include "LookOnCamera.h"

void CpuControl::Start()
{
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

	// �J�����Ɏ��g��MS��ݒ�
	lookOnCamera->SetMsTransform(myMs->GetTransform().get());

	// �J�����Ƀ^�[�Q�b�g��ݒ�
	lookOnCamera->SelectTarget(otherOwner->myMs->GetTransform().get());

	// �v���C���[�ɃJ�����ݒ�
	myMs->SetCamera(lookOnCamera->GetTransform().get());
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
	// Cpu�̈ړ�����
	myMs->CpuMove(cpuMoveAxis);

	// �W�����v
	bool jumpBtn = false;
	if (cpuState == CpuState::Jump)
	{
		jumpBtn = true;
	}
	myMs->Jump(jumpBtn, cpuMoveAxis);

	// �_�b�V��
	bool dashBtn = false;
	if (cpuState == CpuState::Dash || cpuState == CpuState::DashAttack)
	{
		dashBtn = true;
	}
	myMs->Dash(dashBtn, cpuMoveAxis);

	// �U��1
	bool attackBtn = false;
	if (cpuState == CpuState::Attack || cpuState == CpuState::DashAttack)
	{
		attackBtn = true;
	}
	myMs->Attack1(attackBtn);
	if (attackBtn)
	{
		myMs->Attack1(false);
	}
}

void CpuControl::Finish()
{
}
