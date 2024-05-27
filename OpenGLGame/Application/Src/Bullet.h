/**
* @file Bullet.h
*/
#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

class BaseMs;

// �e�̊��N���X
class Bullet : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	Bullet() = default;
	virtual ~Bullet() = default;

private:

	/**
	* �������Ɏ��s
	*/
	virtual void Awake() override;

	/**
	* �ŏ��Ɏ��s
	*/
	virtual void Start() override;

	/**
	* ���t���[�����s
	*/
	virtual void Update()override;

	// ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
	virtual void OnTriggerEnter(const CollisionPtr other) override;

public:

	// �^�[�Q�b�gMs
	BaseMs* targetMS = nullptr;

	float rotationSpeed = 0;

	// �z�[�~���O�̗L��
	bool isHoming = true;

	// �e�̑��x
	float speed = 0;

	// �^����_���[�W
	float damage = 0;

	// �^����_�E���l
	float downPower = 0;

	Vector3 basePos = Vector3::zero;
};


#endif // !RIFLEBULLET_H_INCLUDED
