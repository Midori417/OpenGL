/**
* @file LookOnCamera.h
*/
#ifndef LOOKONCAMERA_H_INCLUDED
#define LOOKONCAMERA_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Math/Vector3.h"
using namespace FGEngine;

/**
* ロックオンカメラ
*/
class LookOnCamera : public GameEvent
{
public:

	// コンストラクタ・デストラクタ
	LookOnCamera() = default;

public:

	virtual void Start() override;

	/**
	* ロックオンカメラの挙動
	* 
	* @param target ターゲットのトランスフォーム
	* @param myMs	自身の機体
	*/
	void LookCamera(Transform* target, Transform* myMs);

private:

	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

private:

	// カメラのオフセット位置最小
	Vector3 offsetMinPos = Vector3(0, 4, -12);

	// カメラのオフセット位置最大
	Vector3 offsetMaxPos = Vector3(0, 10, -15);

	// カメラの旋回速度
	float rotationSpeed = 0.5f;
};

#endif // !LOOKONCAMERA_H_INCLUDED
