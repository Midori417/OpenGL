/**
* @file CpuControl.h
*/
#ifndef CPUCONTROL_H_INCLUDED
#define CPUCONTROL_H_INCLUDED
#include "BaseControl.h"

/**
* CPU����R���|�[�l���g
*/
class CpuControl : public BaseControl
{
public:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	CpuControl() = default;

private:

	/**
	* Update���n�܂�O�Ɉ�x���s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* ���ɃN���[������\�肪�Ȃ��̂ŉ��������Ȃ�
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

private:

	/**
	* �@�̂̑�����X�V
	*/
	virtual void GameInputUpdate() override;

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

#endif // !CPUCONTROL_H_INCLUDED
