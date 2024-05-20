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
	* 
	* @param target ターゲットのTrs
	*/
	void SelectTarget(Transform* targetMs);

	/**
	* とりつくMSのトランスフォームを設定
	* 
	* @param msTrs とりつくMsのTrs
	*/
	void SetMsTransform(Transform* myMs);

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


	// カメラのオフセット位置
	Vector3 offsetMinPos = Vector3(0, 4, -12);
	Vector3 offsetMaxPos = Vector3(0, 10, -15);

private:

	// プレイヤーMsのトランスフォーム
	Transform* myMs;

	// ターゲットのトランスフォーム
	Transform* targetMs;

	// カメラの旋回速度
	float rotationSpeed = 0.5f;
};


#endif // !LOOKONCAMERA_H_INCLUDED
