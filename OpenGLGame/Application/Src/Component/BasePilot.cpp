/**
* @file BasePilot.cpp
*/
#include "BasePilot.h"

#include "BaseMs.h"
#include "CameraManager.h"

/**
* ���`�[���Ƒ���`�[���̗̑͂�ݒ�
*
* @param myTeamHp		���`�[���̗̑̓|�C���^�[
* @param otherTeamHp	����`�[���̗̑̓|�C���^�[
*/
void BasePilot::SetTeamHP(int* myTeamHp, int* otherTeamHp)
{
	this->myTeamHp = myTeamHp;
	this->otherTeamHp = otherTeamHp;
}

/**
* �`�[���̗͂𖳌��ɂ���
*/
void BasePilot::TeamHPInivinit()
{
	isTeamHpInfinit = true;
}

/**
* �R���g���[���̏�����
*/
void BasePilot::Initialize()
{
	// �����^�[�Q�b�g��ݒ�
	targetOwner = otherTeamOwner[0];

	// �J�����Ɏ��g��MS��ݒ�
	myCamera->SetMyMs(myMs->GetTransform());

	// �J�����Ƀ^�[�Q�b�g��ݒ�
	myCamera->SetTarget(targetOwner->myMs->GetTransform());

	// �v���C���[�ɃJ�����ݒ�
	myMs->SetCamera(myCamera->GetTransform().get());
	myMs->SetTargetMS(targetOwner->myMs.get());

	// �Q�[�����͂��쐬
	gameInput = std::make_shared<GameInput>();

	// �Q�[�����͂�ݒ�
	myMs->SetGameInput(gameInput.get());
}

/**
* ���g�̋@�̂����S�����Ƃ��̏���
*/
void BasePilot::MyMsDeadUpdate()
{
	if (!isMsDeath)
	{
		if (!GetTeumHPInifinit())
		{
			// ���`�[����Hp�����炷
			TeumHpSud();
		}
		isMsDeath = true;
		responTimer = 0;
	}
	// �`�[���̗͂�0�ȏゾ�����畜��������
	if (MyTeamHp() > 0)
	{
		responTimer += Time::DeltaTime();
		if (responTimer > responTime)
		{
			int index = Random::Range(0, (int)responPoss.size() - 1);
			// ���`�[���̗̑͂��R�X�g�ȏ゠��΂��̂܂܂̗̑͂ŕ���
			if (MyTeamHp() >= myMs->GetCost())
			{
				myMs->Respon(responPoss[index], 1);
			}
			// ���`�[���̗̑͂��R�X�g�ȉ��Ȃ�Ἀ̗J�b�g���ĕ���
			else if (MyTeamHp() < myMs->GetCost())
			{
				float hp = static_cast<float>(MyTeamHp());
				float cost = static_cast<float>(myMs->GetCost());
				float hpCut = ((cost - hp) / cost);
				myMs->Respon(responPoss[index], hpCut);
			}
			isMsDeath = false;
		}
	}
}

/**
* �^�[�Q�b�g�̏���
*/
void BasePilot::TargetUpdate()
{
	// �^�[�Q�b�g�؂�ւ�
	if (gameInput->targetChangeBtn && otherTeamOwner.size() > 1)
	{
		if (targetOwner == otherTeamOwner[0])
		{
			targetOwner = otherTeamOwner[1];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SetTarget(targetOwner->myMs->GetTransform());
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			targetOwner = otherTeamOwner[0];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SetTarget(targetOwner->myMs->GetTransform());
		}
	}
	// �^�[�Q�b�g�̋@�̂����񂾂�
	if (targetOwner->myMs->IsDeath() && otherTeamOwner.size() > 1)
	{
		if (targetOwner == otherTeamOwner[0])
		{
			targetOwner = otherTeamOwner[1];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SetTarget(targetOwner->myMs->GetTransform());
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			targetOwner = otherTeamOwner[0];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SetTarget(targetOwner->myMs->GetTransform());
		}
	}
}

/**
* ���`�[���̗̑͂��擾
*/
int& BasePilot::MyTeamHp() const
{
	return *myTeamHp;
}

/**
* ����`�[���̗̑͂��擾
*/
int& BasePilot::OtherTeamHp() const
{
	return *otherTeamHp;
}

/**
* �����̋@�̂̃R�X�g�Ń`�[���̗͂����炷
*/
void BasePilot::TeumHpSud()
{
	*myTeamHp -= myMs->GetCost();
}

/**
* �������擾����
*/
float BasePilot::GetDistance()
{
	if (targetOwner)
	{
		auto targetMs = targetOwner->myMs;
		if (targetMs)
		{
			return Vector3::Distance(targetMs->GetTransform()->position, myMs->GetTransform()->position);
		}
	}

	return 0.0f;
}

/**
* �`�[���̗͂��������ǂ���
*/
bool BasePilot::GetTeumHPInifinit() const
{
	return isTeamHpInfinit;
}
