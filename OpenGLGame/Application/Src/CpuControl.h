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
	* �@�̂̍X�V
	*/
	virtual void MsUpdate() override;

	/**
	* �I��
	*/
	virtual void Finish() override;

private:

	/**
	* CPU�̍s��
	*/
	enum CpuState
	{
		// �������Ȃ�
		None,

		// �_�b�V��
		Dash,

		// �W�����v
		Jump,

		// ���C�t��
		Attack,

		// �_�b�V�����C�t��
		DashAttack,

		Max,
	};
	int cpuState = 0;

	Vector2 cpuMoveAxis = Vector2::zero;

	std::vector<Vector2> moveAxiss;
	float moveTimer = 0;
	float moveTime = 0;

	float cpuTimer = 0;

	// ���̍s�������߂�܂ł̎���
	float cpuTime = 0;
};

#endif // !CPU_H_INCLUDED
