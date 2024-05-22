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

	/**
	* �����[�h�X�V
	*/
	void ReloadUpdate();

public:

	/**
	* �ړ�
	* 
	* @param moveAxis ���͎�
	*/
	virtual void Move(const Vector2& moveAxis) override;

	/**
	* �W�����v
	*/
	virtual void Jump(bool isJump, const Vector2& moveAxis) override;

	/**
	* �_�b�V��
	*/
	virtual void Dash(bool isDash, const Vector2& moveAxis) override;

	/**
	* �U��(�r�[�����C�t��)
	*/
	virtual void Attack1(bool attackKey) override;

	/**
	* �U��2(�o�Y�[�J)
	*/
	virtual void Attack2(bool attackKey) override;

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
	virtual void Remove(const Vector3& removePos, float hpCut) override;

private:

	/**
	* ���C�t���\����
	*/
	struct Rifle : NumWeapon
	{
		// �^����_���[�W
		float damage = 0;

		// �U����
		float homingPower = 0;

		float downPower = 0;

		// ���x
		float speed = 0;

		// �ˌ���Ԃ�
		bool isNow = false;

		// ��������
		bool isShot = false;

		// ��~���đł�
		bool isStopShot = false;

		// ���b�V��
		StaticMeshPtr mesh;

		//�V�F�[�_
		ShaderPtr shader;

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
	std::shared_ptr<Rifle> rifle;

	/**
	* �o�Y�[�J�\����
	*/
	struct Bazooka : NumWeapon
	{
		// �^����_���[�W
		float damage = 0;

		float downPower = 0;

		// �U����
		float homingPower = 0;

		// ���x
		float speed = 0;

		// �ˌ���Ԃ�
		bool isNow = false;

		// ��������
		bool isShot = false;

		// ���b�V��
		StaticMeshPtr mesh;

		//�V�F�[�_
		ShaderPtr shader;

		// �e�V�F�[�_
		ShaderPtr shadowShader;

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
	std::shared_ptr<Bazooka> bazooka;

	// ���M�{
	RigidbodyPtr rb;

	// �A�j���[�^
	AnimatorPtr anim;
};

#endif // !GUNDAM_H_INCLUDED
