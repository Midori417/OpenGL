/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "BaseMs.h"

/**
* �K���_��
*/
class Gundam : public BaseMs
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	Gundam() = default;
	virtual ~Gundam() = default;

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Awake() override;

private:


	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

public:

	/**
	* �ړ�
	* 
	* @param moveAxis ���͎�
	*/
	virtual void Move(const Vector2& moveAxis) override;

	virtual void CpuMove() override;

	/**
	* �W�����v
	*/
	virtual void Jump(bool isJump) override;

	/**
	* �_�b�V��
	*/
	virtual void Dash(bool isDash, const Vector2& moveAxis) override;

private:

	// ���M�{
	RigidbodyPtr rb;

	// �A�j���[�^
	AnimatorPtr anim;
};

#endif // !GUNDAM_H_INCLUDED
