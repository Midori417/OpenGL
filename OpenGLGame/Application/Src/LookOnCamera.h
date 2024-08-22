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
class LookOnCamera : public GameEvent
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	LookOnCamera() = default;
	virtual ~LookOnCamera() = default;

	/**
	* �^�[�Q�b�g��ݒ�
	* 
	* @param target �^�[�Q�b�g��Trs
	*/
	void SelectTarget(Transform* targetMs);

	/**
	* �Ƃ��MS�̃g�����X�t�H�[����ݒ�
	* 
	* @param msTrs �Ƃ��Ms��Trss
	*/
	void SetMsTransform(Transform* myMs);

	void StartOk();

private:


	/**
	* ���t���[�����s(Update��肠��)
	*/
	virtual void LateUpdate() override;

	/**
	* �J�����̈ʒu�𒲐�
	*/
	void PositionCamera();

public:


	// �J�����̃I�t�Z�b�g�ʒu
	Vector3 offsetMinPos = Vector3(0, 4, -12);
	Vector3 offsetMaxPos = Vector3(0, 10, -15);

private:

	// �v���C���[Ms�̃g�����X�t�H�[��
	Transform* myMs;

	// �^�[�Q�b�g�̃g�����X�t�H�[��
	Transform* targetMs;

	// �J�����̐��񑬓x
	float rotationSpeed = 0.5f;

	bool isStart = false;

};


#endif // !LOOKONCAMERA_H_INCLUDED
