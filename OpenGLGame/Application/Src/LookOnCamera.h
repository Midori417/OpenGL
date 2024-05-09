/**
* @file LookOnCamera.h
*/
#ifndef LOOKONCAMERA_H_INCLUDED
#define LOOKONCAMERA_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

/**
* ロックオンカメラ
*/
class LookOnCamera : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	LookOnCamera() = default;
	virtual ~LookOnCamera() = default;

	/**
	* ターゲットを設定
	*/
	void SelectTarget(Transform* target);

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行(Updateよりあと)
	*/
	virtual void LateUpdate() override;

	/**
	* カメラの位置を調整
	*/
	void PositionCamera();

public:

	// プレイヤーMsのトランスフォーム
	Transform* playerMs;

	// カメラのオフセット位置
	Vector3 offsetMinPos = Vector3(0, 5, -10);
	Vector3 offsetMaxPos = Vector3(0, 13, -15);

private:

	// ターゲットのトランスフォーム
	Transform* currentTarget;

	// カメラの旋回速度
	float rotationSpeed = 0.5f;
};


#endif // !LOOKONCAMERA_H_INCLUDED
