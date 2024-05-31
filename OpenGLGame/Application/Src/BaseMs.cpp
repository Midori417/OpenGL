/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"

bool BaseMs::isResoueLoad = false;

/**
* HP���擾
*/
int BaseMs::GetHP() const
{
	return static_cast<int>(baseParamater.hp);
}

/**
* HP���擾(0�`1)
*/
float BaseMs::GetHP01()
{
	return Mathf::Clamp01((baseParamater.hpMax - (baseParamater.hpMax - baseParamater.hp)) / baseParamater.hpMax);
}

/**
* �G�l���M�[�c�ʂ̎擾(0�`1)
*/
float BaseMs::GetBoostEnergy() const
{
	return Mathf::Clamp01((boostParamater.max - (boostParamater.max - boostParamater.current)) / boostParamater.max);
}

/**
* �@�̃R�X�g���擾
*/
int BaseMs::GetCost() const
{
	return baseParamater.cost;
}

/**
* ���S���擾
*/
bool BaseMs::IsDeath() const
{
	return isDeath;
}

/**
* �G�Ƃ̋�����ݒ�
* 
* @param distance �G�Ƃ̋���
*/
void BaseMs::SetDistance(float distance)
{
	this->distance = distance;
}

/**
* �J�����̃g�����X�t�H�[����ݒ�
*/
void BaseMs::SetCamera(Transform* camera)
{
	this->cameraTrasform = camera;
}

/**
* �^�[�Q�b�gMS�̐ݒ�
*/
void BaseMs::SetTargetMS(BaseMs* baseMS)
{
	this->targetMs = baseMS;
}

/**
* �Q�[�����͂�ݒ�
*/
void BaseMs::SetGameInput(GameInput* gameInput)
{
	this->gameInput = gameInput;
}

/**
* ��~������
*/
void BaseMs::Stop()
{
	isStop = true;
}

/**
* ���S�`�F�b�N
*
* @retval true	���S
* @retval false ����
*/
bool BaseMs::DeadChaeck()
{
	// ���łɎ��S���Ă����牽�����Ȃ�
	if (isDeath)
	{
		return true;
	}

	// HP���Ȃ���Ύ��S��Ԃɂ���
	if (baseParamater.hp <= 0 || GetTransform()->position.y < -10)
	{
		// ���S��Ԃɂ���
		isDeath = true;
		// �`�悵�Ȃ�
		renderer->enabled = false;
		rb->velocity = Vector3::zero;
		return true;
	}
	return false;
}

/**
* �u�[�X�g�G�l���M�[�̍X�V
*/
void BaseMs::BoostEnergyUpdate()
{
	// �n�ʂɂ��Ă���Ƃ�
	if (rb->IsGround() && !boostParamater.chageLock)
	{
		// �G�l���M�[�̉񕜃X�^�[�g�^�C�}�[��0�ȉ��Ȃ�
		if (boostParamater.chageStartTimer <= 0)
		{
			// �u�[�X�g�G�l���M�[�������Ă�����
			if (boostParamater.current < boostParamater.max)
			{
				// �G�l���M�[����
				boostParamater.current += boostParamater.chageSpeed * Time::DeltaTime();
			}
		}
		else
		{
			// �G�l���M�[�`���[�W�J�n�^�C�}�[�����炷
			boostParamater.chageStartTimer -= Time::DeltaTime();
		}
		boostParamater.current = Mathf::Clamp(boostParamater.current, 0.0f, boostParamater.max);
	}
}

/**
* �G�Ƃ̋������擾
*/
float BaseMs::GetDistance() const
{
	return distance;
}

/**
* �J�����̃g�����X�t�H�[�����擾
*/
Transform* BaseMs::GetCameraTransform() const
{
	return cameraTrasform;
}

/**
* �^�[�Q�b�gMS���擾
*/
BaseMs* BaseMs::GetTargetMs() const
{
	return targetMs;
}

