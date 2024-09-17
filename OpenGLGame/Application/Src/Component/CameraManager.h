/**
* @file CameraManager.h
*/
#ifndef CAMERAMANAGER_H_INCLUDED
#define CAMERAMANAGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

// 先行宣言
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;

/**
* カメラ管理マネージャー
*/
class CameraManager : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	CameraManager() = default;

private:

	virtual void Awake() override;

	/**
	* Updateが始まる前に一度実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void LateUpdate() override;

	/**
	* コンポーネントをクローンする
	*/
	virtual ComponentPtr Clone() const override;

public:

	/**
	* 自身の機体を設定
	*/
	void SetMyMs(const TransformPtr& myMs);

	/**
	* ターゲット機体を設定
	*/
	void SetTarget(const TransformPtr& target);

private:

	// 自身の機体
	Transform* trsMyMs = nullptr;

	// ターゲットのトランスフォーム
	Transform* trsTarget = nullptr;

	// ロックオンカメラコンポーネント
	LookOnCameraPtr lookOnCamera = nullptr;
};

#endif // !CAMERAMANAGER_H_INCLUDED