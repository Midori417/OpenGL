/**
* @file LookOnCamera.h
*/
#ifndef LOOKONCAMERA_H_INCLUDED
#define LOOKONCAMERA_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* ���b�N�I���J����
*/
class LookOnCamera : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	LookOnCamera() = default;
	virtual ~LookOnCamera() = default;

	/**
	* �^�[�Q�b�g��ݒ�
	*/
	void SelectTarget(Transform* target);

private:

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s(Update��肠��)
	*/
	virtual void LateUpdate() override;

	/**
	* �J�����̈ʒu�𒲐�
	*/
	void PositionCamera();

public:

	// �v���C���[Ms�̃g�����X�t�H�[��
	Transform* playerMs;

	// �J�����̃I�t�Z�b�g�ʒu
	Vector3 offsetMinPos = Vector3(0, 5, -10);
	Vector3 offsetMaxPos = Vector3(0, 13, -15);

private:

	// �^�[�Q�b�g�̃g�����X�t�H�[��
	Transform* currentTarget;

	// �J�����̐��񑬓x
	float rotationSpeed = 0.5f;
};


#endif // !LOOKONCAMERA_H_INCLUDED
