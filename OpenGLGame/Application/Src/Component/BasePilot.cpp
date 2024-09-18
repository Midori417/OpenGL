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
* �p�[�g�i�[�p�C���b�g��ݒ�
*
* @param �ݒ肷��p�[�g�i�[�p�C���b�g
*/
void BasePilot::SetPartnerPilot(const BasePilotPtr& pilot)
{
	partnerPilot = pilot.get();
}

/**
* ����`�[���̃p�C���b�g��ݒ�
*
* @param �ݒ肷�鑊��`�[���̃p�C���b�g
*/
void BasePilot::SetOtherTeamPilot(const BasePilotPtr& pilot)
{
	otherTeamPilots.push_back(pilot.get());
}

/**
* �R���g���[���̏�����
*/
void BasePilot::Initialize()
{
	// �����^�[�Q�b�g��ݒ�
	targetPilot = otherTeamPilots[0];

	// �J�����Ɏ��g��MS��ݒ�
	myCamera->SetMyMs(myMs->GetTransform());

	// �J�����Ƀ^�[�Q�b�g��ݒ�
	myCamera->SetTarget(targetPilot->myMs->GetTransform());

	// �v���C���[�ɃJ�����ݒ�
	myMs->SetCamera(myCamera->GetTransform().get());
	myMs->SetTargetMS(targetPilot->myMs.get());

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
	if (gameInput->targetChangeBtn && otherTeamPilots.size() > 1)
	{
		if (targetPilot == otherTeamPilots[0])
		{
			targetPilot = otherTeamPilots[1];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetPilot->myMs.get());
			myCamera->SetTarget(targetPilot->myMs->GetTransform());
		}
		else if (targetPilot == otherTeamPilots[1])
		{
			targetPilot = otherTeamPilots[0];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetPilot->myMs.get());
			myCamera->SetTarget(targetPilot->myMs->GetTransform());
		}
	}
	// �^�[�Q�b�g�̋@�̂����񂾂�
	if (targetPilot->myMs->IsDeath() && otherTeamPilots.size() > 1)
	{
		if (targetPilot == otherTeamPilots[0])
		{
			targetPilot = otherTeamPilots[1];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetPilot->myMs.get());
			myCamera->SetTarget(targetPilot->myMs->GetTransform());
		}
		else if (targetPilot == otherTeamPilots[1])
		{
			targetPilot = otherTeamPilots[0];
			// �J�����Ƌ@�̂Ƀ^�[�Q�b�g����������
			myMs->SetTargetMS(targetPilot->myMs.get());
			myCamera->SetTarget(targetPilot->myMs->GetTransform());
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
* �p�[�g�i�[�p�C���b�g���擾
*/
BasePilot* BasePilot::GetPartnerPilot() const
{
	return partnerPilot;
}

/**
* �p�[�g�i�[�̋@�̂��擾
*/
BaseMsPtr BasePilot::GetPartnerMs() const
{
	if (!partnerPilot)
	{
		// �p�[�g�i�[�����Ȃ�
		return nullptr;
	}

	return partnerPilot->myMs;
}

/**
* ����`�[���̃p�C���b�g���擾
*
* @param index �p�C���b�g�ԍ�
*/
BasePilot* BasePilot::GetOtherTeamPilot(size_t index) const
{
	// ����`�[���̃p�C���b�g��葽���z��ԍ��̏ꍇ��nullptr��Ԃ�
	if (index > otherTeamPilots.size() - 1)
	{
		return nullptr;
	}

	return otherTeamPilots[index];
}

/**
* ����`�[���̋@�̂��擾
*
* @param index �p�C���b�g�ԍ�
*/
BaseMsPtr BasePilot::GetOtherTeamMs(size_t index) const
{
	// ����`�[���̃p�C���b�g��葽���z��ԍ��̏ꍇ��nullptr��Ԃ�
	if (index > otherTeamPilots.size() - 1)
	{
		return nullptr;
	}

	return otherTeamPilots[index]->myMs;
}

/**
* ����`�[���̃p�C���b�g�̐����擾
*/
size_t BasePilot::GetOtherTeamPilotSize() const
{
	return otherTeamPilots.size();
}

/**
* �^�[�Q�b�g�p�C���b�g���擾
*/
BasePilot* BasePilot::GetTargetPilot() const
{
	return targetPilot;
}

/**
* �^�[�Q�b�g�@�̂��擾
*/
BaseMsPtr BasePilot::GetTargetMs() const
{
	if (!targetPilot)
	{
		return nullptr;
	}

	return targetPilot->myMs;
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
	if (targetPilot)
	{
		auto targetMs = targetPilot->myMs;
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
