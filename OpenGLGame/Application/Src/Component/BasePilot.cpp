/**
* @file BasePilot.cpp
*/
#include "BasePilot.h"

#include "BaseMs.h"
#include "CameraManager.h"

/**
* ������
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
	myMs->SetTrsCamera(myCamera->GetTransform());
	myMs->SetTargetMs(targetPilot->myMs);

	// �Q�[�����͂��쐬
	gameInput = std::make_shared<GameInput>();

	// �Q�[�����͂�ݒ�
	myMs->SetMsInput(gameInput);
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