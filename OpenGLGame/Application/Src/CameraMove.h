/**
* @file CameraMove.h
*/
#ifndef CAMERAMOVE_H_INCLUDED
#define CAMERAMOVE_H_INCLUDED

#include "FGEngineSub.h"
using namespace FGEngine;

/**
* �J�����̓���
*/
class CameraMove : public Component
{
public:

	// �R���X�g���N�^
	CameraMove() = default;

	// �f�X�g���N�^
	virtual ~CameraMove() = default;

	virtual void LateUpdate();

public:

	// �Ƃ��Trs
	Transform* myMsTrs;

	// �^�[�Q�b�gTrs
	Transform* targetTrs;

private:

	// myMSTrs����J�����̃I�t�Z�b�g�ʒu
	Vector3 offsetNearPos = Vector3(0, 13, 10);	// ��ԋ߂�
	Vector3 offsetFarPos = Vector3(0, 5, 15);	// ��ԋ߂�

	float rotationSpeed = 0.5f;
};

#endif // !CAMERAMOVE_H_INCLUDED