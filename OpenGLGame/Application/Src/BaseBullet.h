/**
* @file BaseBullet.h
*/
#ifndef BASEBULLET_H_INCLUDED
#define BASEBULLET_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* �e�̊��N���X
*/
class BaseBullet : public MonoBehaviour
{
public:

	// �R���X�g���N�^�E�f�X�g���N�^
	BaseBullet() = default;
	virtual ~BaseBullet() = default;

public:

	// �e�̑��x
	float speed = 0;

	// �^����_���[�W
	float damage = 0;

	// �^����_�E���l
	float downPower = 0;

	// �����Ă��������܂ł̎���
	float destroyTime = 5;
};


#endif // !BASEBULLET_H_INCLUDED
