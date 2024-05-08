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

private:

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

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
	virtual void Move(const Vector2& moveAxis);

private:

	float angle = 180;

	// ���M�{
	RigidbodyPtr rb;

	// �A�j���[�^
	AnimatorPtr anim;
};

#endif // !GUNDAM_H_INCLUDED
