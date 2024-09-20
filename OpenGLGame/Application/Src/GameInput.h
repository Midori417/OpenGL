/**
* @file GameInput.h
*/
#ifndef GAMEINPUT_H_INCLUDED
#define GAMEINPUT_H_INCLUDED
#include "FGEngine/Math/Vector2.h"
using namespace FGEngine;

/**
* �Q�[���̓���
*/
struct GameInput
{
	// �ړ���
	Vector2 moveAxis = Vector2::zero;

	// �W�����v�{�^��
	bool jumpBtn = false;

	// �_�b�V���{�^��
	bool dashBtn = false;

	bool stepBtn = false;

	// �s��1�{�^��
	bool action1Btn = false;

	// �s��2�{�^��
	bool action2Btn = false;

	// �s��3�{�^��
	bool action3Btn = false;

	// �^�[�Q�b�g�؂�ւ��{�^��
	bool targetChangeBtn = false;

	/**
	* ���͂�������Ԃɂ���
	*/
	void Initialize()
	{
		moveAxis = Vector2::zero;
		jumpBtn = false;
		dashBtn = false;
		stepBtn = false;
		action1Btn = false;
		action2Btn = false;
		action3Btn = false;
		targetChangeBtn = false;
	}
};
using GameInputPtr = std::shared_ptr<GameInput>;

#endif // !MSCONTROL_H_INCLUDED
