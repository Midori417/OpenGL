/**
* @file CpuControl.h
*/
#ifndef CPUCONTROL_H_INCLUDED
#define CPUCONTROL_H_INCLUDED
#include "ControlOwner.h"

/**
* �R���s���[�^����
*/
class CpuControl : public ControlOwner
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	CpuControl() = default;
	virtual ~CpuControl() = default;

private:

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* ���t���[�����s(Update����)
	*/
	virtual void LateUpdate() override;

};

#endif // !CPU_H_INCLUDED
