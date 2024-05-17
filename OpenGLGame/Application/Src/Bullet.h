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

	float rotationSpeed = 0;

	// �z�[�~���O�̗L��
	bool isHoming = true;

	// �e�̑��x
	float speed = 0;

	// �^����_���[�W
	float damage = 0;
};


#endif // !RIFLEBULLET_H_INCLUDED
