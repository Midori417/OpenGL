/**
* @file GameInput.h
*/
#ifndef GAMEINPUT_H_INCLUDED
#define GAMEINPUT_H_INCLUDED
#include "FGEngine.h"
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
};

#endif // !MSCONTROL_H_INCLUDED
