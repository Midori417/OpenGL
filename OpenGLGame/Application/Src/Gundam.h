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
	* CPU�ړ�
	*/
	virtual void CpuMove(const Vector2& moveAxis) override;

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
	* �_���[�W
	* 
	* @param damage �^����_���[�W
	*/
	virtual void Damage(float damage) override;

	/**
	* �����Ԃ�
	*/
	virtual void Remove(const Vector3& removePos, float hp) override;

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

		virtual void Initialize() override
		{
			amo = amoMax;
			isNow = false;
			isShot = false;
		}
	};
	std::shared_ptr<Rifle> rifle;

	// ���M�{
	RigidbodyPtr rb;

	// �A�j���[�^
	AnimatorPtr anim;
};

#endif // !GUNDAM_H_INCLUDED
