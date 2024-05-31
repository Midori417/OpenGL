/**
* @file ControlOwner.cpp
*/
#include "ControlOwner.h"
#include "BaseMs.h"
#include "LookOnCamera.h"

/**
* �R���g���[�����X�^�[�g
*/
void ControlOwner::StartOk()
{
	isStart = true;
}

/**
* ���`�[���Ƒ���`�[���̗̑͂�ݒ�
*
* @param myTeumHp		���`�[���̗̑̓|�C���^�[
* @param otherTeumHp	����`�[���̗̑̓|�C���^�[
*/
void ControlOwner::SetTeumHP(int* myTeumHp, int* otherTeumHp)
{
	this->myTeumHp = myTeumHp;
	this->otherTeumHp = otherTeumHp;
}

/**
* �`�[���̗͂𖳌��ɂ���
*/
void ControlOwner::TeumHPInivinit()
{
	isTeamHpInfinit = true;
}

/**
* �R���g���[���̏�����
*/
void ControlOwner::Initialize()
{
	// �����^�[�Q�b�g��ݒ�
	targetOwner = otherTeamOwner[0];

	// �J�����Ɏ��g��MS��ݒ�
	myCamera->SetMsTransform(myMs->GetTransform().get());

	// �J�����Ƀ^�[�Q�b�g��ݒ�
	myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());

	// �v���C���[�ɃJ�����ݒ�
	myMs->SetCamera(myCamera->GetTransform().get());
	myMs->SetTargetMS(targetOwner->myMs.get());

	// �Q�[�����͂��쐬
	gameInput = std::make_shared<GameInput>();

	// �Q�[�����͂�ݒ�
	myMs->SetGameInput(gameInput.get());
}

/**
* ���`�[���̗̑͂��擾
*/
int& ControlOwner::MyTeumHp() const
{
	return *myTeumHp;
}

/**
* ����`�[���̗̑͂��擾
*/
int& ControlOwner::OtherTeumHp() const
{
	return *otherTeumHp;
}

/**
* �����̋@�̂̃R�X�g�Ń`�[���̗͂����炷
*/
void ControlOwner::TeumHpSud()
{
	*myTeumHp -= myMs->GetCost();
}

/**
* �������擾����
*/
float ControlOwner::GetDistance()
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
bool ControlOwner::GetTeumHPInifinit() const
{
	return isTeamHpInfinit;
}
