/**
* @file ControlOwner.h
*/
#ifndef CONTROLOWNER_H_INCLUDED
#define CONTROLOWNER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
#include "MsLilst.h"

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;

/**
* ����
*/
class ControlOwner : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	ControlOwner() = default;
	virtual ~ControlOwner() = default;

	/**
	* ���`�[����Hp���擾
	*/
	int& GetTeumHp() const
	{
		return *myTeumHp;
	}

	/**
	* ���`�[����Hp��ݒ�
	*/
	void SetTeumHP(int* teumHP)
	{
		myTeumHp = teumHP;
	}

	/**
	* �`�[���̗͂����炷
	*/
	void TeumHpSud();

	/**
	* �I��
	*/
	virtual void Finish(){}


protected:

	/**
	* �@�̂̍X�V
	*/
	virtual void MsUpdate() {}

public:

	// �J����
	LookOnCameraPtr lookOnCamera;

	// ����
	float distance = 0;

	// �������J�n���邩
	bool isStart = false;

	// �g���@��
	MsList ms = MsList::None;

	// �����ȊO�̃I�[�i�[
	ControlOwner* otherOwner;

	// �����̋@��
	BaseMsPtr myMs;

protected:

	// ������MS�̎��S�̗L��
	bool isMsDeath = false;

	// ���`�[���̗̑�
	int* myTeumHp;
};


#endif // !CONTROLOWNER_H_INCLUDED
