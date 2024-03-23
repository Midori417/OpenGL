/**
* @file BaseMS.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngineSub.h"
using namespace FGEngine;


// ��s�錾
class PlayerManager;

/**
* �������̂��镐��
*/
struct NumArmer
{
	float maxAmo = 0;
	float amo = 0;
	float amoReloadtimer = 0;
	float amoReloadSpeed = 3.0f;
	std::string iconfileName;

public:

	void AmoReloadUpdate()
	{
		if (amo < maxAmo)
		{
			amoReloadtimer += Time::deltaTime();
			if (amoReloadtimer > amoReloadSpeed)
			{
				amo += 1;
				amoReloadtimer = 0;
			}
		}
	}

};

/**
* ���ׂĂ�MS�̊��R���|�[�l���g
*/
class BaseMS : public Component
{
public:

	BaseMS() = default;
	virtual ~BaseMS() = default;


public:

	virtual void Damage(float damage){}

protected:

	/**
	* �n�ʂɂ��Ă���`�F�b�N(�Փˏ������Â����߂̉��}���u)
	*/
	void GroundCheck()
	{
		groundTimer += Time::deltaTime();
		// �n�ʂɂ����Ƃ�
		if (GetGameObject()->isGrounded)
		{
			groundTimer = 0;
			isGrond = true;
		}
		// �n�ʂɂ��ĂȂ����Ԃ�groundTime�𒴂�����n�ʂ��痣��Ă���
		if (groundTimer > groundTime)
		{
			isGrond = false;
		}
	}


private:

	// ��b�p�����[�^
	struct Parameter
	{
		float hp = 0;		// �̗�
		float hpMax = 0;	// �̗̓}�b�N�X
		const float boostPowerMax = 100;	// �G�l���M�[�}�b�N�X��
		float boostPower = 0;				// �G�l���M�[��
		int weaponMax = 1;					// ����̐�
		unsigned short teum = -1;			// �`�[���i���o�[
	};

	// �U���p�����[�^
	struct AttackParameter
	{
		float clossRangeDistance = 30;		// �ߐڍU���L������
		float shotDistance = 60;			// �������L������
	};

	float groundTimer = 0;
	const float groundTime = 0.2f;

protected:

	// �v���C���[�}�l�[�W���[
	PlayerManager* playerManager;

	// �J����
	Transform* cameraTrs;

	// ��b�p�����[�^
	Parameter parameter;

	// �U���̃p�����[�^
	AttackParameter attackParameter;

	float powerHealSpeed = 20.0f;		// �G�l���M�[�񕜑��x

	std::vector<NumArmer*> numArmer;	// �����z��

	// �n�ʔ���
	bool isGrond = true;				// �n�ʔ���

public:

	/**
	* �v���C���[�}�l�[�W���[��ݒ�
	*/
	void SetPlayerManager(PlayerManager* playerManager)
	{
		this->playerManager = playerManager;
	}

	/**
	* �J�����̈ʒu��ݒ�
	*/
	void SetCameraTrs(Transform* cameraTrs)
	{
		this->cameraTrs = cameraTrs;
	}

	/**
	* ��b�p�����[�^���擾
	*/
	Parameter GetParameter() const
	{
		return parameter;
	}

	/**
	* �U���p�����[�^���擾
	*/
	AttackParameter AttackDistance()
	{
		return attackParameter;
	}

	/**
	* �����z����擾
	*/
	NumArmer* GetNumArmer(int i)
	{
		return numArmer[i];
	}

};

#endif // !BASEMS_H_INCLUDED
