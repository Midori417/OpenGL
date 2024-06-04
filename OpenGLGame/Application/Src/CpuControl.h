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
	* �R���g���[�����X�^�[�g������
	*/
	virtual void ControlStart() override;

	/**
	* �Q�[�����͂��X�V
	*/
	virtual void GameInputUpdate() override;

	/**
	* �I������
	*/
	virtual void Finish(VictoryState victoryState) override;

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

		// �U��
		Attack,

		// �U��2
		Attack2,

		// �U��3
		Attack3,

		// �_�b�V�����C�t��
		DashAttack,

		Max,
	};
	int cpuState = 0;

	// CPU�p�̉��z��
	Vector2 cpuMoveAxis = Vector2::zero;

	// ���z��
	std::vector<Vector2> moveAxiss;

	// �^�[�Q�b�g�i���o�[
	int targetNum = 0;

	// ���̈ړ�������ύX�^�C�}�[
	float moveTimer = 0;

	// ���̈ړ�������ύX����܂ł̎���
	float moveTime = 0;

	// ���̍s����ύX�^�C�}�[
	float cpuTimer = 0;

	// ���̍s����ύX����܂ł̎���
	float cpuTime = 0;
};

#endif // !CPU_H_INCLUDED
