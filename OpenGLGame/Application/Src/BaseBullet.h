/**
* @file BaseBullet.h
*/
#ifndef BASEBULLET_H_INCLUDED
#define BASEBULLET_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

// ��s�錾
class BaseMs;

/**
* �e�̊��N���X
*/
class BaseBullet : public GameEvent
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BaseBullet() = default;
	virtual ~BaseBullet() = default;

private:

	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

	/**
	* �������Ɏ��s
	*/
	virtual void Awake() override;

	/**
	* ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
	*/
	virtual void OnCollisionEnter(const CollisionPtr other) override;

public:

	// �e�̑��x
	float speed = 0;

	// �^����_���[�W
	float damage = 0;

	// �^����_�E���l
	float downPower = 0;

	// �����Ă��������܂ł̎���
	float destroyTime = 5;

	struct Col
	{
		float radius = 1;
		Vector3 ceneter = Vector3::zero;
	};
	Col colllider;

};
#endif // !BASEBULLET_H_INCLUDED
