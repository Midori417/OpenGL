/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Animator.h"

/**
* �@�̓��͂�ݒ�
*/
void BaseMs::SetMsInput(const GameInputPtr& gameInput)
{
	msInput = gameInput;
}

/**
* �J�����̃g�����X�t�H�[����ݒ肷��
*/
void BaseMs::SetTrsCamera(const TransformPtr& camera)
{
	trsCamera = camera.get();
}

/**
* �^�[�Q�b�g�@�̂�ݒ�
*/
void BaseMs::SetTargetMs(const BaseMsPtr& targetMs)
{
	this->targetMs = targetMs.get();
}

/**
* �J�������ʂ���Ɉړ��������v�Z����
*/
Vector3 BaseMs::MoveForward(const Vector2& moveAxis)
{
	// �J�����̕�������AX-Z�P�ʃx�N�g��(���K��)���擾
	Vector3 cameraForward = Vector3::Normalize(GetTrsCamera()->Forward() * Vector3(1, 0, 1));
	Vector3 moveForward = cameraForward * moveAxis.y + GetTrsCamera()->Right() * moveAxis.x;

	return moveForward;
}

/**
* ���ʃR���|�[�l���g�̎擾
*/
void BaseMs::ComponentGet()
{
	rb = OwnerObject()->AddComponent<Rigidbody>();
	renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	anim = OwnerObject()->AddComponent<Animator>();
}

/**
* �J�����̃g�����X�t�H�[�����擾����
*/
Transform* BaseMs::GetTrsCamera() const
{
	return trsCamera;
}

/**
* �^�[�Q�b�g�@�̂��擾
*/
BaseMs* BaseMs::GetTarget() const
{
	return targetMs;
}
