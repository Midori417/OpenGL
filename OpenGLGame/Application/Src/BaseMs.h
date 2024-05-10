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
	virtual void Move(const Vector2& moveAxis) {}

	/**
	* CPU�ړ�
	*/
	virtual void CpuMove(){}

	/**
	* �W�����v
	*/
	virtual void Jump(bool isJump){}

	/**
	* �_�b�V��
	*/
	virtual void Dash(bool isDash, const Vector2& mvoeAxis){}

	// �U��
	virtual void Attack1() {}
	virtual void Attack2() {}

	/**
	* �_���[�W��^����
	*
	* @param damage �^����_���[�W
	*/
	virtual void Damage(float damage) {}

	/**
	* �J�����g�����X�t�H�[���̐ݒ�
	*/
	void SetCamera(Transform* camera);

	/**
	* �J�����̃g�����X�t�H�[�����擾
	*/
	Transform* GetCameraTransform() const;

	/**
	* �^�[�Q�b�gMS�̐ݒ�
	*/
	void SetTargetMS(BaseMs* baseMS);

	/**
	* �^�[�Q�b�gMS�̎擾
	*/
	BaseMs* GetTargetMs() const;

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
	private:

		/**
		* �_�b�V���p�����[�^
		*/
		struct DashParamater
		{
			// �ړ����x
			float speed = 0;

			// ���񑬓x
			float rotationSpeed = 0;

			// �_�b�V������
			bool isNow = false;
		};

		/**
		* �W�����v�p�����[�^
		*/
		struct JumpPramter
		{
			// �W�����v��
			float power = 0;

			// �W�����v����
			bool isNow = false;
		};

	public:

		// �ʏ푬�x
		float speed = 0;

		// �ʏ펞�̐��񑬓x
		float rotationSpeed = 0;

		DashParamater dash;

		JumpPramter jump;
	};
	MoveParamater moveParamater;

private:

	// �G�Ƃ̋���
	float distance = 0;

	// �J�����̈ʒu
	Transform* cameraTrasform;

	// �^�[�Q�b�g��MS
	BaseMs* targetMs;

};

#endif // !BASEMS_H_INCLUDED
