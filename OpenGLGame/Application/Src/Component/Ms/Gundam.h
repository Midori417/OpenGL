/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "../BaseMs.h"

/**
* �K���_��
*/
class Gundam : public BaseMs
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	Gundam() = default;
	
private:	// �C�x���g

	/**
	* �������Ɏ��s
	*/
	virtual void Awake() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

private: // �֗�

	/**
	* �K�v�ȃR���|�[�l���g�A�ϐ����擾�ł��Ă��邩�`�F�b�N
	*/
	virtual bool Check();

private: // �A�C�h��

	/**
	* �A�C�h����Ԃɂ���
	*/
	void IdleAnimation();

private: // �ړ�

	/**
	* �ړ��ł��邩�`�F�b�N
	* 
	* @retval true	�\
	* @retval false	�s�\
	*/
	bool MoveCheck() const;

	/**
	* �ړ�����
	*/
	void Move(const Vector2& moveAxis);

	/**
	* �ړ��A�j���[�V�����̏���
	*/
	void MoveAnimation();

private: // �W�����v

	/**
	* �W�����v�\���`�F�b�N
	* 
	* @retval true	�\
	* @retval false	�s�\
	*/
	bool JumpCheck() const;

	/**
	* �W�����v����
	*/
	void Jump(const Vector2& moveAxis, bool isBtn);

	/**
	* �W�����v�A�j���[�V�����̏���
	*/
	void JumpAnimation();

private:

	/**
	* �����Ă��镐��
	*/
	enum class HandWeapon
	{
		Rifle,

		Sable
	};
	HandWeapon handWeapon = HandWeapon::Rifle;
};

#endif // !GUNDAM_H_INCLUDED
