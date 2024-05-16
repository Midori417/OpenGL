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
* UI�ɕ\�L���镐��
*/
struct NumWeapon
{
	// ���O
	std::string name;

	// �c�e�}�b�N�X
	int amoMax = 0;

	// �c�e
	int amo = 0;

	// �����[�h�^�C�}�[
	float reloadTimer = 0;

	// �����[�h�^�C��
	float reloadTime = 0;

	// ����A�C�R��
	TexturePtr iconTexture;
};
using NumWeaponPtr = std::shared_ptr<NumWeapon>;

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

	float GetHP01();

	/**
	* �G�l���M�[�c�ʂ̎擾(0�`1)
	*/
	float GetBoostEnergy() const;


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
	virtual void Jump(bool isJump, const Vector2& moveAxis){}

	/**
	* �_�b�V��
	*/
	virtual void Dash(bool isDash, const Vector2& mvoeAxis){}

	// �U��
	virtual void Attack1(bool attackKey) {}
	virtual void Attack2(bool attackKey2) {}

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

	// ���������镐��̔z��
	std::vector<NumWeaponPtr> numWeapons;

	// �ߐڋ���
	float proximityDistance = 0;

	// �ԃ��b�N����
	float redLookDistace = 0;

protected:

	// �`�[��
	Teum teum = Teum::None;

	// �@�̂̃R�X�g
	int cost = 0;

	// �@�̂�HP�̍ő�l
	float hpMax = 0;

	// �@�̂�HP
	float hp = 0;

	// ����ł邩�̗L��
	bool isDeath = false;

	// �G�l���M�[�ő��
	const float boostEnergyMax = 100;

	// �G�l���M�[
	float boostEnergy = 100;

	// �G�l���M�[�񕜑��x
	float boostEnergyChage = 500;

	// �n�ʂɂ��Ă���̃`���[�W���x
	float boostEnergyChageTimer = 0;

	// �n�ʂɂ��Ă���̃`���[�W�J�n�܂ł̑��x
	float boostEnergyChageStartTime = 0.3f;

	// �n�ʂɂ��Ă���̃`���[�W�J�n�܂ł̑��x(OVERHEAT�̏ꍇ)
	float boostEnergyChageOverHeatStartTime = 1;

	// �G�l���M�[�񕜂̃��b�N�̗L��
	bool boostEnergyChageLock = false;

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

			// �G�l���M�[�̏����
			float useEnergy = 0;

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

			// �ړ����x
			float speed = 0;

			// ���񑬓x
			float rotationSpeed = 0;

			// �G�l���M�[�̏����
			float useEnergy = 0;

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
