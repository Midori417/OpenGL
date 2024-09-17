/**
* @file CameraManager.cpp
*/
#include "CameraManager.h"
#include "FGEngine/GameObject.h"

#include "LookOnCamera.h"

void CameraManager::Awake()
{
}

/**
* Updateが始まる前に一度実行
*/
void CameraManager::Start()
{
	// ロックオンカメラを設定する
	lookOnCamera = OwnerObject()->AddComponent<LookOnCamera>();
}

/**
* 毎フレーム実行
*/
void CameraManager::LateUpdate()
{
	// ターゲットと自身の機体がいない場合何もしない
	if (!trsTarget || !trsMyMs)
	{
		return;
	}

	// ロックオンカメラ
	if (lookOnCamera)
	{
		lookOnCamera->LookCamera(trsTarget, trsMyMs);
	}
}

/**
* コンポーネントをクローンする
*/
ComponentPtr CameraManager::Clone() const
{
	return ComponentPtr();
}

/**
* 自身の機体を設定
*/
void CameraManager::SetMyMs(const TransformPtr& myMs)
{
	this->trsMyMs = myMs.get();
}

/**
* ターゲット機体を設定
*/
void CameraManager::SetTarget(const TransformPtr& target)
{
	this->trsTarget = target.get();
}
