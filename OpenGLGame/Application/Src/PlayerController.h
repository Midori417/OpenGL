/**
* @file PlayerController.h
*/
#ifndef PLAYERCONTROLLER_H_INCLUDED
#define PLAYERCONTROLLER_H_INCLUDED
#include "MyEngine.h"

/**
* プレイヤーコントローラ入力
*/
class PlayerController : public Component
{
public:

	PlayerController() = default;
	virtual ~PlayerController() = default;

private:

	virtual void Update() override;

public:

	Vector2 inputAxis = Vector2::zero;
	bool jumpBtn = false;
	bool jumpBtnDown = false;
	bool jumpBtnPush = false;
	float jumpBtnTimer = 0;
	bool shotBtn = false;
	bool fightBtn = false;

};

#endif // !PLAYERCONTROLLER_H_INCLUDED
