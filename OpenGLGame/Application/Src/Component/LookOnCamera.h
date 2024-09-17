/**
* @file LookOnCamera.h
*/
#ifndef LOOKONCAMERA_H_INCLUDED
#define LOOKONCAMERA_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Math/Vector3.h"
using namespace FGEngine;

/**
* ���b�N�I���J����
*/
class LookOnCamera : public GameEvent
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	LookOnCamera() = default;

public:

	virtual void Start() override;

	/**
	* ���b�N�I���J�����̋���
	* 
	* @param target �^�[�Q�b�g�̃g�����X�t�H�[��
	* @param myMs	���g�̋@��
	*/
	void LookCamera(Transform* target, Transform* myMs);

private:

	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

private:

	// �J�����̃I�t�Z�b�g�ʒu�ŏ�
	Vector3 offsetMinPos = Vector3(0, 4, -12);

	// �J�����̃I�t�Z�b�g�ʒu�ő�
	Vector3 offsetMaxPos = Vector3(0, 10, -15);

	// �J�����̐��񑬓x
	float rotationSpeed = 0.5f;
};

#endif // !LOOKONCAMERA_H_INCLUDED
