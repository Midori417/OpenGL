/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
#include "../GameInput.h"

// ��s�錾
struct DamageInfo;
struct GameInput;
class UIWeapon;
using UIWeaponPtr = std::shared_ptr<UIWeapon>;

/**
* MS�̊��N���X
*/
class BaseMs : public GameEvent
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

	/**
	* ��~������
	*/
	void Stop();

	/**
	* �U���\���`�F�b�N
	*
	* @retval true  �U���\
	* @retval false �U���s��
	*/
	bool HomingCheck() const;

	bool GetHoimngCancel() const;

	virtual ComponentPtr Clone() const override
	{
		return nullptr;

	}

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

	/**
	* �u�[�X�g�G�l���M�[���I�[�o�[�q�[�g���Ă邩
	*/
	void BoostCheck();


public:

	// UI�ɕ\�����镐��
	std::vector<UIWeaponPtr> uiWeapons;

	// �ߐڋ���
	float proximityDistance = 0;

	// �ԃ��b�N����(���s)
	float redLookDistaceXZ = 0;

	// �ԃ��b�N����(+Y)
	float redLookDistanceMaxY = 0;

	// �ԃ��b�N����(-Y)
	float redLookDistanceMinY = 0;

protected:

	// ���M�{
	RigidbodyPtr rb;

	// �A�j���[�^
	AnimatorPtr anim;

	// �����_���[
	GltfMeshRendererPtr renderer;

	// ����
	GameInput* gameInput = nullptr;

	// ���\�[�X�ǂݍ���
	static bool isResoueLoad;

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

		struct Step
		{
			Vector3 direction = Vector3::zero;

			float useEnergy = 0.0f;
			
			bool isNow = false;

			float speed = 0.0f;
		};

	public:

		// �ʏ푬�x
		float speed = 0;

		// �ʏ펞�̐��񑬓x
		float rotationSpeed = 0;

		float moveTimer = 0;

		const float moveTime = 0.3f;

		// �_�b�V���p�����[�^
		DashParamater dash;

		// �W�����v�p�����[�^
		JumpPramter jump;

		// �X�e�b�v�p�����[�^
		Step step;
	};
	MoveParamater moveParamater;

	// ���S���
	bool isDeath = false;

	// �_�E���l
	float downValue = 0;

	/**
	* ������э\����
	*/
	struct BlowAway
	{
		// ������я�Ԃ�
		bool isNow = false;

		// ������Ԏ���
		float timer = 0;

		float time = 0.5f;

		float power = 70.0f;
	};
	BlowAway blowAway;

	bool isDownCancel = false;

	bool isDown = false;

	// �_�E�����Ă���̎���
	float downTimer = 0;
	
	// �_�E�����Ă��狭�������オ��̎���
	const float downStandUpTime = 3;

	// �_���[�W��Ԃ̗L��
	bool isDamage = false;

	float responTimer = 0;
	float responTime = 0.5f;

	// ���X�|�[�����
	bool isRespon = false;

	// �X�g�b�v������
	bool isStop = false;

private:

	// �G�Ƃ̋���
	float distance = 0;

	// �J�����̈ʒu
	Transform* cameraTrasform;

	// �^�[�Q�b�g��MS
	BaseMs* targetMs;

};

#endif // !BASEMS_H_INCLUDED
