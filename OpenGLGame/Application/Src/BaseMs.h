/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

enum class Teum
{
	// �`�[������
	None,

	// �ԃ`�[��
	Red,

	// �`�[��
	Blue,
};

/**
* MS�̊��N���X
*/
class BaseMs : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BaseMs() = default;
	virtual ~BaseMs() = default;

	/**
	* �`�[�����擾
	*/
	Teum GetTeum() const;

	/**
	* Hp���擾
	*/
	int GetHP() const;

	/**
	* �G�l���M�[�̎c��(0�`1)���擾
	*/
	float GetBoostPower() const;

	/**
	* �G�Ƃ̋�����ݒ�
	* 
	* @param distance �G�Ƃ̋���
	*/
	void SetDistance(float distance);

	/**
	* �G�Ƃ̋������擾
	*/
	float GetDistance() const;

	/**
	* �ړ�
	*
	* @param moveAxis ���͎�
	*/
	virtual void Move(const Vector2&) {}

	// �U��
	virtual void Attack1() {}
	virtual void Attack2() {}

	/**
	* �_���[�W��^����
	*
	* @param damage �^����_���[�W
	*/
	virtual void Damage(float damage) {}

public:

	// MS�̖��O
	std::string name;

protected:

	Teum teum = Teum::None;

	// �@�̂̃R�X�g
	int cost = 0;

	// �@�̂�HP�̍ő�l
	int hpMax = 0;

	// �@�̂�HP
	int hp = 0;

	// �G�l���M�[�ő��
	const float boostPowerMax = 100;

	// �G�l���M�[�g�p��
	float boostPower = 0;

	/**
	* �ړ��p�����[�^
	*/
	struct MoveParamater
	{
		// �n��ł̑��x
		float groundSpeed = 0;

		// �_�b�V���̑��x
		float dashSpeed = 0;

		// �W�����v��
		float jumpPower = 0;
	};
	MoveParamater moveParamater;

private:

	// �G�Ƃ̋���
	float distance = 0;

};

#endif // !BASEMS_H_INCLUDED
