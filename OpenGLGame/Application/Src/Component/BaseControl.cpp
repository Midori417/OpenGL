/**
* @file BaseControl.cpp
*/
#include "BaseControl.h"
#include "FGEngine/Component/Transform.h"

#include "LookOnCamera.h"
#include "BaseMs.h"

/**
* 開始合図
*/
void BaseControl::StartOk()
{
	isStart = true;
}

/**
* コントロールの初期化
*/
void BaseControl::Initialize()
{
	// 初期ターゲットを設定
	targetControl = otherTeamControls[0];

	Transform* targetMs = targetControl->myMs->GetTransform().get();

	// カメラに自身の機体とターゲットを伝える
	myCamera->SetMsTransform(myMs->GetTransform().get());
	myCamera->SelectTarget(targetMs);

	// 機体にカメラとターゲットを伝える
	myMs->SetCamera(myCamera->GetTransform().get());
	myMs->SetTargetMS(targetControl->myMs.get());

	// ゲーム入力を作成
	gameInput = std::make_shared<GameInput>();
}

/**
* 開始されているか取得
*/
bool BaseControl::IsStart() const
{
	return isStart;
}

/**
* ターゲットとの距離を計算
*/
bool BaseControl::GetDistance() const
{
	if (targetControl)
	{
		auto targetMs = targetControl->myMs;
		if (targetMs)
		{
			return Vector3::Distance(targetMs->GetTransform()->position, myMs->GetTransform()->position);
		}
	}

	return 0.0f;
}

/**
* ターゲットの状態を更新
*/
void BaseControl::TargetUpdate()
{
	// ターゲット切り替え
	if (gameInput->targetChangeBtn && otherTeamControls.size() > 1)
	{
		if (targetControl == otherTeamControls[0])
		{
			targetControl = otherTeamControls[1];

			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetControl->myMs.get());
			myCamera->SelectTarget(targetControl->myMs->GetTransform().get());
		}
		else if (targetControl == otherTeamControls[1])
		{
			targetControl = otherTeamControls[0];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetControl->myMs.get());
			myCamera->SelectTarget(targetControl->myMs->GetTransform().get());
		}
	}
	// ターゲットの機体が死んだら
	if (targetControl->myMs->IsDestroy() && otherTeamControls.size() > 1)
	{
		if (targetControl == otherTeamControls[0])
		{
			targetControl = otherTeamControls[1];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetControl->myMs.get());
			myCamera->SelectTarget(targetControl->myMs->GetTransform().get());
		}
		else if (targetControl == otherTeamControls[1])
		{
			targetControl = otherTeamControls[0];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetControl->myMs.get());
			myCamera->SelectTarget(targetControl->myMs->GetTransform().get());
		}
	}
}
