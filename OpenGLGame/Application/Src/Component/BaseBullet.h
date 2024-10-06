/**
* @file BaseBullet.h
*/
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

/**
* �e�̊��R���|�[�l���g
*/
class BaseBullet : public GameEvent
{
protected:

	/**
	* �f�t�H���g�R���X�g���N�^
	*/
	BaseBullet() = default;

protected:

	// �^����_���[�W
	float damage = 0;

	// ���x
	float speed = 0;

	// ��������Ă��������܂ł̎���
	float destroyTime = 0;
};