/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

// ��s�錾
struct GameInput;

/**
* MS�̊��R���|�[�l���g
*/
class BaseMs : public GameEvent
{
protected: // ���̃R���|�[�l���g�p����Ŏ��̉�����

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BaseMs() = default;

public:

	/**
	* �U�����󂯂��Ƃ��ɑ���ɌĂяo���Ă��炤
	* 
	* @parama damage �^����_���[�W
	*/
	virtual void Damage(float damage){}

	/**
	* �G�Ƃ̋�����ݒ�
	*
	* @param distance �G�Ƃ̋���
	*/
	void SetDistance(float distance);

	/**
	* �J�����g�����X�t�H�[���̐ݒ�
	*/
	void SetCamera(Transform* camera);

	/**
	* �^�[�Q�b�gMS�̐ݒ�
	*/
	void SetTargetMS(BaseMs* baseMS);

	/**
	* �@�̓��͂�ݒ肷��
	*/
	void SetGameInput(GameInput* gameInput);

	/**
	* �@�̂��j�󂳂�Ă��邩�擾
	*/
	bool IsDestroy() const;

protected:

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

	/**
	* �j��`�F�b�N
	*/
	bool DestroyCheck() const;

	/**
	* �j�󂷂�
	*/
	void Destroy();

protected:

	// �@�̖̂��O
	std::string name = "MS";

	GameInput* gameInput = nullptr;

	// �R���|�[�l���g
	RigidbodyPtr rb = nullptr;
	GltfMeshRendererPtr meshRender = nullptr;
	AnimatorPtr anim = nullptr;
	std::vector<AudioSourcePtr> audioSource;

private:

	//true���Ɣj�󂳂�Ă���
	bool isDestroy = false;

	// �^�[�Q�b�g�Ƃ̋���
	float distance = 0;

	// �J�����̃g�����X�t�H�[��
	Transform* trsCamera;

	// �^�[�Q�b�gMS
	BaseMs* targetMs;

protected:

	/**
	* ��b�p�����[�^
	*/
	struct Paramater
	{
		// �@�̂̃R�X�g
		int cost = 0;

		// �@�̂̍ő�ϋv�l
		float hpMax = 0;

		// �@�̑ϋv�l
		float hp = 0;
	};
	Paramater paramater;

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
	BoostParamater boost;

protected: // �ړ�

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

	/**
	* �W�����v�p�����[�^
	*/
	struct JumpParamater
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
	JumpParamater jump;

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
	DashParamater dash;
};

#endif // !BASEMS_H_INCLUDED
