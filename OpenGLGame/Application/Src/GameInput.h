/**
* @file GameInput.h
*/
#ifndef GAMEINPUT_H_INCLUDED
#define GAMEINPUT_H_INCLUDED
#include "FGEngine/Math/Vector2.h"
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

	/**
	* 入力を初期状態にする
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
