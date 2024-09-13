/**
* @file CpuControl.cpp
*/
#include "CpuControl.h"
#include "FGEngine/Other/Time.h"
#include "FGEngine/Other/Random.h"

#include "BaseMs.h"

/**
* Update���n�܂�O�Ɉ�x���s
*/
void CpuControl::Start()
{
	Initialize();

	// CPU�̍s���؂�ւ����Ԃ�ݒ�
	cpuTime = 1;
	moveTime = 2;

	// ���z���͎����쐬
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
* ���t���[�����s
*/
void CpuControl::Update()
{
	// �X�^�[�g���}���o�Ă�����Ή������Ȃ�
	if (!IsStart())
	{
		return;
	}

	GameInputUpdate();

	// �j�󂳂�Ă��Ȃ����
	if (!myMs->IsDestroy())
	{
		myMs->SetDistance(GetDistance());
		TargetUpdate();
	}
}

/**
* �@�̂̑�����X�V
*/
void CpuControl::GameInputUpdate()
{
	// �ړ������𗐐��Ō��߂�
	moveTimer -= Time::DeltaTime();
	if (moveTimer <= 0)
	{
		int index = Random::Range(0, (int)moveAxiss.size() - 1);
		cpuMoveAxis = moveAxiss[index];
		moveTimer = moveTime;
	}
	gameInput->moveAxis = cpuMoveAxis;

	// �s���𗐐��Ō��߂�
	cpuTimer -= Time::DeltaTime();
	if (cpuTimer <= 0)
	{
		cpuState = (int)Random::Range(CpuState::None, CpuState::Max - 1);
		cpuTimer = cpuTime;
		targetNum = (int)Random::Range(0, static_cast<int>(otherTeamControls.size() - 1));
	}


	// �W�����v
	gameInput->jumpBtn = false;
	if (cpuState == CpuState::Jump)
	{
		gameInput->jumpBtn = true;
	}

	// �_�b�V��
	gameInput->dashBtn = false;
	if (cpuState == CpuState::Dash || cpuState == CpuState::DashAttack)
	{
		gameInput->dashBtn = true;
	}

	// �U��1
	gameInput->action1Btn = false;
	if (cpuState == CpuState::Attack || cpuState == CpuState::DashAttack)
	{
		gameInput->action1Btn = true;
	}

	// �U��2
	gameInput->action2Btn = false;
	if (cpuState == CpuState::Attack2)
	{
		gameInput->action2Btn = true;
	}
	// �U��3
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
