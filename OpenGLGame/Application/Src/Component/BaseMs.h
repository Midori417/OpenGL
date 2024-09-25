/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;
#include "../GameInput.h"

// ��s�錾
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class UIWeapon;
using UIWeaponPtr = std::shared_ptr<UIWeapon>;

/**
* MS�̊��N���X
*/
class BaseMs : public GameEvent
{
protected: // �h����Ő�������

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BaseMs() = default;

public:

	/**
	* �@�̓��͂�ݒ�
	*/
	void SetMsInput(const GameInputPtr& gameInput);

	/**
	* �J�����̃g�����X�t�H�[����ݒ肷��
	*/
	void SetTrsCamera(const TransformPtr& camera);

	/**
	* �^�[�Q�b�g�@�̂�ݒ�
	*/
	void SetTargetMs(const BaseMsPtr& targetMs);

protected:

	/**
	* �K�v�ȃR���|�[�l���g�A�ϐ����擾�ł��Ă��邩�`�F�b�N
	*/
	virtual bool Check() { return false; }

	/**
	* �J�������ʂ���Ɉړ��������v�Z����
	*/
	Vector3 MoveForward(const Vector2& moveAxis);

	/**
	* ���ʃR���|�[�l���g�̎擾
	*/
	void ComponentGet();

	/**
	* �J�����̃g�����X�t�H�[�����擾����
	*/
	Transform* GetTrsCamera() const;

	/**
	* �^�[�Q�b�g�@�̂��擾
	*/
	BaseMs* GetTarget() const;

private:

	// �J�����g�����X�t�H�[��
	Transform* trsCamera = nullptr;

	// �^�[�Q�b�g�@��
	BaseMs* targetMs = nullptr;

protected:

	// �@�̓���
	GameInputPtr msInput = nullptr;

	// ���W�b�h�{�f�B
	RigidbodyPtr rb = nullptr;

	// �����_���[
	GltfMeshRendererPtr renderer = nullptr;

	// �A�j���[�^
	AnimatorPtr anim = nullptr;

protected:

	/**
	* ��b�p�����[�^
	*/
	struct Paramater
	{
		// �ϋv�͂̍ő�l
		int durabilityMax = 0;

		// ���݂̑ϋv��
		int durability = 0;

		// ��͒l
		int strengthValue = 0;
	};
	Paramater paramater;

	/**
	* �u�[�X�g�p�����[�^
	*/
	struct BoostParamater
	{
		// �u�[�X�g�̃G�l���M�[�ő�l
		const float max = 100;

		// ���݂̃u�[�X�g
		float current = 100;

		// �u�[�X�g�̉񕜑��x
		float chargeSpeed = 500;

		// �`���[�W�J�n�^�C�}�[
		float chageStartTimer = 0;

		// �`���[�W�̊J�n���x
		const float chageStartTime = 0.2f;

		// �`���[�W�J�n���x(OVERHEAT�̏ꍇ)
		const float overHeatChageStartTime = 0.5f;

		// �u�[�X�g���񕜂��邩
		bool chageLock = false;
	};
	BoostParamater boost;

	/**
	* �ړ��p�����[�^
	*/
	struct MoveParamater
	{
		// �ړ����x
		float speed = 0;

		// ���񑬓x
		float rotationSpeed = 0;
	};
	MoveParamater move;

	struct DashParamater
	{

	};

	/**
	* �W�����v�p�����[�^
	*/
	struct JumpParamater
	{
		// �W�����v��
		float power = 0;

		// ���ړ����x
		float speed = 0;

		// ���񑬓x
		float rotationSpeed = 0;

		// �u�[�X�g�̏����
		float useBoost = 0;

		// �W�����v����
		bool isNow = false;
	};
	JumpParamater jump;
};

#endif // !BASEMS_H_INCLUDED
