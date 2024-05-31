/**
* @file CpuControl.cpp
*/
#include "CpuControl.h"
#include "BaseMs.h"
#include "Global.h"
#include "LookOnCamera.h"

/**
* �ŏ��Ɏ��s
*/
void CpuControl::Start()
{
	// ��������
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
	if (!isStart)
	{
		return;
	}

	// ���g�̋@�̂����񂾂�
	if (myMs->IsDeath())
	{
		if (!isMsDeath)
		{
			if (!GetTeumHPInifinit())
			{
				// ���`�[����Hp�����炷
				TeumHpSud();
			}
			// Ms�̑�����ł��Ȃ��悤�ɂ���
			isMsControl = false;
			isMsDeath = true;
			responTimer = 0;
		}
		// �`�[���̗͂�0�ȏゾ�����畜��������
		if (MyTeumHp() > 0)
		{
			responTimer += Time::DeltaTime();
			if (responTimer > responTime)
			{
				int index = Random::Range(0, (int)responPoss.size() - 1);
				// ���`�[���̗̑͂��R�X�g�ȏ゠��΂��̂܂܂̗̑͂ŕ���
				if (MyTeumHp() >= myMs->GetCost())
				{
					myMs->Respon(responPoss[index], 1);
				}
				// ���`�[���̗̑͂��R�X�g�ȉ��Ȃ�Ἀ̗J�b�g���ĕ���
				else if (MyTeumHp() < myMs->GetCost())
				{
					float hp = static_cast<float>(MyTeumHp());
					float cost = static_cast<float>(myMs->GetCost());
					float hpCut = ((cost - hp) / cost);
					myMs->Respon(responPoss[index], hpCut);
				}
				// MS�̑��������
				isMsControl = true;
				isMsDeath = false;
			}
		}
	}
	GameInputUpdate();

	// �^�[�Q�b�g�؂�ւ�
	if (gameInput->targetChangeBtn && otherTeamOwner.size() > 0)
	{
		if (targetOwner == otherTeamOwner[0])
		{
			if (!otherTeamOwner[1]->myMs->IsDeath())
			{
				targetOwner = otherTeamOwner[1];
				// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
				myMs->SetTargetMS(targetOwner->myMs.get());
				myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
			}
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			if (!otherTeamOwner[0]->myMs->IsDeath())
			{
				targetOwner = otherTeamOwner[0];
				// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
				myMs->SetTargetMS(targetOwner->myMs.get());
				myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
			}
		}
		gameInput->targetChangeBtn = false;
	}
	// �^�[�Q�b�g�̋@�̂����񂾂�
	if (targetOwner->myMs->IsDeath() && otherTeamOwner.size() > 0)
	{
		if (targetOwner == otherTeamOwner[0])
		{
			if (!otherTeamOwner[1]->myMs->IsDeath())
			{
				targetOwner = otherTeamOwner[1];
				// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
				myMs->SetTargetMS(targetOwner->myMs.get());
				myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
			}
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			if (!otherTeamOwner[0]->myMs->IsDeath())
			{
				targetOwner = otherTeamOwner[0];
				// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
				myMs->SetTargetMS(targetOwner->myMs.get());
				myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
			}
		}
	}
}

/**
* �I������
*/
void CpuControl::Finish(VictoryState victoryState)
{
	// �����~
	myMs->Stop();
}

/**
* �Q�[�����͂��X�V
*/
void CpuControl::GameInputUpdate()
{
	// MS������ł��ꂩ�A���삪������Ă��Ȃ���Ή������Ȃ�
	if (myMs->IsDeath() || !isMsControl)
	{
		return;
	}

	auto targetMs = targetOwner->myMs;

	// ���g��MS�ɑ����Ms�̏���`����
	myMs->SetTargetMS(targetMs.get());

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
		targetNum = (int)Random::Range(0, static_cast<int>(otherTeamOwner.size() - 1));
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
	gameInput->action1Btn= false;
	if (cpuState == CpuState::Attack || cpuState == CpuState::DashAttack)
	{
		if (!targetMs->IsDeath())
		{
			gameInput->action1Btn = true;
		}
	}

	// �U��2
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