/**
* @file GameInput.h
*/
#ifndef GAMEINPUT_H_INCLUDED
#define GAMEINPUT_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* ゲームの入力
*/
struct GameInput
{
	// 移動軸
	Vector2 moveAxis = Vector2::zero;

	// ジャンプボタン
	bool jumpBtn = false;

	// ダッシュボタン
	bool dashBtn = false;

	bool stepBtn = false;

	// 行動1ボタン
	bool action1Btn = false;

	// 行動2ボタン
	bool action2Btn = false;

	// 行動3ボタン
	bool action3Btn = false;

	// ターゲット切り替えボタン
	bool targetChangeBtn = false;
};

#endif // !MSCONTROL_H_INCLUDED
