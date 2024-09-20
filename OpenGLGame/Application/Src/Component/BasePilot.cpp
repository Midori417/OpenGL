/**
* @file BasePilot.cpp
*/
#include "BasePilot.h"

#include "BaseMs.h"
#include "CameraManager.h"

/**
* 初期化
*/
void BasePilot::Initialize()
{
	// 初期ターゲットを設定
	targetPilot = otherTeamPilots[0];

	// カメラに自身のMSを設定
	myCamera->SetMyMs(myMs->GetTransform());

	// カメラにターゲットを設定
	myCamera->SetTarget(targetPilot->myMs->GetTransform());

	// プレイヤーにカメラ設定
	myMs->SetTrsCamera(myCamera->GetTransform());
	myMs->SetTargetMs(targetPilot->myMs);

	// ゲーム入力を作成
	gameInput = std::make_shared<GameInput>();

	// ゲーム入力を設定
	myMs->SetMsInput(gameInput);
}

/**
* パートナーパイロットを設定
*
* @param 設定するパートナーパイロット
*/
void BasePilot::SetPartnerPilot(const BasePilotPtr& pilot)
{
	partnerPilot = pilot.get();
}

/**
* 相手チームのパイロットを設定
*
* @param 設定する相手チームのパイロット
*/
void BasePilot::SetOtherTeamPilot(const BasePilotPtr& pilot)
{
	otherTeamPilots.push_back(pilot.get());
}

/**
* パートナーパイロットを取得
*/
BasePilot* BasePilot::GetPartnerPilot() const
{
	return partnerPilot;
}

/**
* パートナーの機体を取得
*/
BaseMsPtr BasePilot::GetPartnerMs() const
{
	if (!partnerPilot)
	{
		// パートナーがいない
		return nullptr;
	}

	return partnerPilot->myMs;
}

/**
* 相手チームのパイロットを取得
*
* @param index パイロット番号
*/
BasePilot* BasePilot::GetOtherTeamPilot(size_t index) const
{
	// 相手チームのパイロットより多い配列番号の場合はnullptrを返す
	if (index > otherTeamPilots.size() - 1)
	{
		return nullptr;
	}

	return otherTeamPilots[index];
}

/**
* 相手チームの機体を取得
*
* @param index パイロット番号
*/
BaseMsPtr BasePilot::GetOtherTeamMs(size_t index) const
{
	// 相手チームのパイロットより多い配列番号の場合はnullptrを返す
	if (index > otherTeamPilots.size() - 1)
	{
		return nullptr;
	}

	return otherTeamPilots[index]->myMs;
}

/**
* 相手チームのパイロットの数を取得
*/
size_t BasePilot::GetOtherTeamPilotSize() const
{
	return otherTeamPilots.size();
}

/**
* ターゲットパイロットを取得
*/
BasePilot* BasePilot::GetTargetPilot() const
{
	return targetPilot;
}

/**
* ターゲット機体を取得
*/
BaseMsPtr BasePilot::GetTargetMs() const
{
	if (!targetPilot)
	{
		return nullptr;
	}

	return targetPilot->myMs;
}