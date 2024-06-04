/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "BaseMs.h"
#include "BaseWeapon.h"

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

	// �����Ă��镐��
	enum class HandWeapon
	{
		// ���C�t��
		Rifle,

		// �T�[�x��
		Sable,
	};

	/**
	* ���C�t���\����
	*/
	struct Rifle : public ShotWeaponUI
	{

		// ��~���đł�
		bool isStopShot = false;

		/**
		* ������
		*/
		virtual void Initialize() override
		{
			amo = amoMax;
			isNow = false;
			isShot = false;
			isStopShot = false;
		}
	};

	/**
	* �o�Y�[�J�\����
	*/
	struct Bazooka : ShotWeaponUI
	{
		/**
		* ������
		*/
		virtual void Initialize() override
		{
			amo = amoMax;
			isNow = false;
			isShot = false;
		}
	};

	/**
	* �T�[�x���\����
	*/
	struct Sable : public BaseWeapon
	{
		// �T�[�x���s������
		bool isNow = false;

		// �U���������Ă��邩
		bool isHoming = false;

		// �T�[�x���擾��Ԃ�
		bool isGet = false;

		Vector3* targetPos;

		/**
		* �T�[�x���ړ��\����
		*/
		struct Move
		{
			// �T�[�x���ړ�����
			bool isNow = false;


			// �U���ړ����n�߂��ʒu
			Vector3 attackStartPos = Vector3::zero;

			// �T�[�x���ړ��ő勗��(�U������)
			const float useHomingDistanceMax = 30.0f;

			// �T�[�x���ړ��ő勗��(�U���Ȃ�)
			const float noHomingDistanceMax = 10.0f;

			// �U���J�n����
			const float attackDistance = 7.0f;

			float moveTimer = 0;

			const float moveTimeMax = 0;

			// �T�[�x���ړ����x
			float speed = 40.0f;

			// �G�l���M�[�̏���
			float useEnergy = 30.0f;
		};
		Move move;

		/**
		* �T�[�x���U���\����
		*/
		struct Attack
		{
			// �T�[�x���U������
			bool isNow = false;

			// �U�����ړ����x
			float speed = 15.0f;

			// �^����_���[�W
			float damage = 0;

			// �^����_�E���l
			float downPower = 0;

			// �U��������Ŏ���
			float destoryTime = 0.5f;

			// �U������𐶐�������
			bool isSlash = false;

			// �U�����萶������
			float slashTime = 0.2f;

			// �ړ�����
			float moveTime = 0.3f;

		};
		Attack attack1;
		Attack attack2;
		Attack attack3;
	};

	/**
	* ���t���[�����s
	*/
	virtual void Update() override;

	/**
	* �����[�h�X�V
	*/
	void ReloadUpdate();

	/**
	* �ړ�
	*
	* @param moveAxis ���͎�
	*/
	void Move(const Vector2& moveAxis);

	/**
	* �W�����v
	*
	* @param jumpBtn	�W�����v�{�^���̏��
	* @param moveAxis	���͎�
	*/
	void Jump(bool jumpBtn, const Vector2& moveAxis);

	/**
	* �_�b�V��
	*
	* @param dashBtn	�_�b�V���{�^���̏��
	* @param moveAxis	���͎�
	*/
	void Dash(bool dashBtn, const Vector2& moveAxis);

	/**
	* �U��(�r�[�����C�t��)
	*
	* @param acttion1Btn �A�N�V�����{�^��1�̏��
	*/
	void Action1(bool acttion1Btn);

	/**
	* �U��2(�o�Y�[�J)
	*
	* @param acttion2Btn �A�N�V�����{�^��2�̏��
	*/
	void Action2(bool acttion2Btn);

	/**
	* �U��3(�r�[���T�[�x��)
	*
	* @param acttion3Btn �A�N�V�����{�^��3�̏��
	*/
	void Action3(bool acttion3Btn);

	/*
	* �r�[���T�[�x���U���I��
	*/
	void SableAttackFailded(Sable::Attack& attack);

public:

	/**
	* �_���[�W��^����
	*
	* @param damageInfo �_���[�W���
	*/
	virtual void Damage(const DamageInfo& damgeInfo)override;

	/**
	* �����Ԃ�
	*
	* @param removePos	�����Ԃ�ʒu
	* @param hpCut		�̗͂̃J�b�g��
	*/
	virtual void Respon(const Vector3& removePos, float hpCut) override;

private:

	// �����Ă��镐��
	HandWeapon handWeapon = HandWeapon::Rifle;

	// ���C�t������
	std::shared_ptr<Rifle> rifle;

	// �o�Y�[�J����
	std::shared_ptr<Bazooka> bazooka;

	// �T�[�x������
	std::shared_ptr<Sable> sable;

};

#endif // !GUNDAM_H_INCLUDED
