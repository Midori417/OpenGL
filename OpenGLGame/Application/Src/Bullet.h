/**
* @file Bullet.h
*/
#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

class BaseMs;

class Bullet : public MonoBehaviour
{
public:

	Bullet() = default;
	virtual ~Bullet() = default;

	virtual void Awake() override;

private:

	virtual void Start() override;

	virtual void Update()override;

	// ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
	virtual void OnTriggerEnter(const CollisionPtr other) override;

public:

	// �^�[�Q�b�gMs
	BaseMs* targetMS;

	// �z�[�~���O�̋���
	float homingPower = 1;

	float rotationSpeed = 0.5f;

	// �z�[�~���O�̗L��
	bool isHoming = true;

	// �e�̑��x
	float speed = 100.0f;

	// �^����_���[�W
	float damage = 100;
};


#endif // !RIFLEBULLET_H_INCLUDED
