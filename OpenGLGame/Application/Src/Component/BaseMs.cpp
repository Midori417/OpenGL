/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Rigidbody.h"

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
	this->trsCamera = camera;
}

/**
* �^�[�Q�b�gMS�̐ݒ�
*/
void BaseMs::SetTargetMS(BaseMs* baseMS)
{
	this->targetMs = baseMS;
}

/**
* �@�̓��͂�ݒ肷��
*/
void BaseMs::SetGameInput(GameInput* gameInput)
{
	this->gameInput = gameInput;
}

/**
* �@�̂��j�󂳂�Ă��邩�擾
*/
bool BaseMs::IsDestroy() const
{
	// ���łɎ��S���Ă����牽�����Ȃ�
	if (isDestroy)
	{
		return true;
	}

	// HP���Ȃ���Ύ��S��Ԃɂ���
	if (paramater.hp <= 0 || GetTransform()->position.y < -10)
	{
		// �`�悵�Ȃ�
		meshRender->enabled = false;
		rb->velocity = Vector3::zero;
		return true;
	}
	return false;
}

/**
* �J�����̃g�����X�t�H�[�����擾
*/
Transform* BaseMs::GetCameraTransform() const
{
	return trsCamera;
}

/**
* �j��`�F�b�N
*/
bool BaseMs::DestroyCheck() const
{
	return false;
}

/**
* �j�󂷂�
*/
void BaseMs::Destroy()
{
	isDestroy = true;
}
