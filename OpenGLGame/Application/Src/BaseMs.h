/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine.h"
#include "GameInput.h"
using namespace FGEngine;

// ��s�錾
struct DamageInfo;
struct GameInput;

/**
* UI�ɕ\�L���镐��
*/
struct NumWeapon
{
	// ���O
	std::string name;

	// �c�e�}�b�N�X
	float amoMax = 0;

	// �c�e
	float amo = 0;

	// �����[�h�^�C�}�[
	float reloadTimer = 0;

	// �����[�h�^�C��
	float reloadTime = 0;

	// ����A�C�R��
	TexturePtr iconTexture;

	virtual void Initialize(){}
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
	* Hp���擾
	*/
	int GetHP() const;
	float GetHP01();

	/**
	* �G�l���M�[�c�ʂ̎擾(0�`1)
	*/
	float GetBoostEnergy() const;

	/**
	* �@�̃R�X�g���擾
	*/
	int GetCost() const;

	/**
	* ���S��Ԃ��擾
	* 
	* @retval true	���S
	* @retval false ����
	*/
	bool IsDeath() const;

	/**
	* �G�Ƃ̋�����ݒ�
	* 
	* @param distance �G�Ƃ̋���
	*/
	void SetDistance(float distance);

	/**
	* �����Ԃ�
	* 
	* @param removePos	�����Ԃ�ʒu
	* @param hpCut		�̗͂̃J�b�g��
	*/
	virtual void Respon(const Vector3& removePos, float hpCut){}

	/**
	* �_���[�W��^����
	*
	* @param damageInfo �_���[�W���
	*/
	virtual void Damage(const DamageInfo& damgeInfo) {}

	/**
	* �J�����g�����X�t�H�[���̐ݒ�
	*/
	void SetCamera(Transform* camera);

	/**
	* �^�[�Q�b�gMS�̐ݒ�
	*/
	void SetTargetMS(BaseMs* baseMS);

	/**
	* �Q�[�����͂�ݒ�
	*/
	void SetGameInput(GameInput* gameInput);

protected:

	/**
	* ���S�`�F�b�N
	* 
	* @retval true	���S
	* @retval false ����
	*/
	bool DeadChaeck();

	/**
	* �u�[�X�g�G�l���M�[�̍X�V
	*/
	void BoostEnergyUpdate();

	/**
	* �J�����̃g�����X�t�H�[�����擾
	*/
	Transform* GetCameraTransform() const;

	/**
	* �^�[�Q�b�gMS�̎擾
	*/
	BaseMs* GetTargetMs() const;

	/**
	* �G�Ƃ̋������擾
	*/
	float GetDistance() const;


public:

	// ���������镐��̔z��
	std::vector<NumWeaponPtr> numWeapons;

	// �ߐڋ���
	float proximityDistance = 0;

	// �ԃ��b�N����
	float redLookDistace = 0;

protected:

	// ���M�{
	RigidbodyPtr rb;

	// �A�j���[�^
	AnimatorPtr anim;

	// �����_���[
	GltfMeshRendererPtr renderer;

	// ����
	GameInput* gameInput = nullptr;

	/**
	* ��b�p�����[�^
	*/
	struct BaseParamater
	{
		// MS�̖��O
		std::string name;

		// �@�̂̃R�X�g
		int cost = 0;

		// �@�̂�HP�̍ő�l
		float hpMax = 0;

		// �@�̂�HP
		float hp = 0;

	};
	BaseParamater baseParamater;

	/**
	* �u�[�X�g�p�����[�^
	*/
	struct BoostParamater
	{
		// �G�l���M�[�̍ő��
		const float max = 100;

		// ���݂̃G�l���M�[
		float current = 100;

		// �񕜑��x
		float chageSpeed = 500;

		// �`���[�W�J�n�^�C�}�[
		float chageStartTimer = 0;

		// �`���[�W�̊J�n���x
		const float chageStartTime = 0.2f;

		// �`���[�W�J�n���x(OVERHEAT�̏ꍇ)
		const float overHeatChageStartTime = 0.5f;

		// �G�l���M�[���񕜂��邩
		bool chageLock = false;
	};
	BoostParamater boostParamater;

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

		// �_�b�V���p�����[�^
		DashParamater dash;

		// �W�����v�p�����[�^
		JumpPramter jump;
	};
	MoveParamater moveParamater;

	// ���S���
	bool isDeath = false;

	// �_�E���l
	float downValue = 0;

	// ������я�Ԃ̗L��
	bool isBlowAway = false;

	float blowAwayTimer = 0;

	float blowAwayTime = 1;

	float blowPower = 30.0f;

	bool isDown = false;

	// �_���[�W��Ԃ̗L��
	bool isDamage = false;

private:

	// �G�Ƃ̋���
	float distance = 0;

	// �J�����̈ʒu
	Transform* cameraTrasform;

	// �^�[�Q�b�g��MS
	BaseMs* targetMs;

};

#endif // !BASEMS_H_INCLUDED
