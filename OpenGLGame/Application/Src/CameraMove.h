/**
* @file CameraMove.h
*/
#ifndef CAMERAMOVE_H_INCLUDED
#define CAMERAMOVE_H_INCLUDED

#include "FGEngineSub.h"
using namespace FGEngine;

/**
* カメラの動き
*/
class CameraMove : public Component
{
public:

	// コンストラクタ
	CameraMove() = default;

	// デストラクタ
	virtual ~CameraMove() = default;

	virtual void LateUpdate();

public:

	// とりつくTrs
	Transform* myMsTrs;

	// ターゲットTrs
	Transform* targetTrs;

private:

	// myMSTrsからカメラのオフセット位置
	Vector3 offsetNearPos = Vector3(0, 13, 10);	// 一番近い
	Vector3 offsetFarPos = Vector3(0, 5, 15);	// 一番近い

	float rotationSpeed = 0.5f;
};

#endif // !CAMERAMOVE_H_INCLUDED