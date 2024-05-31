/**
* @file ControlOwner.cpp
*/
#include "ControlOwner.h"
#include "BaseMs.h"
#include "LookOnCamera.h"

/**
* コントロールをスタート
*/
void ControlOwner::StartOk()
{
	isStart = true;
}

/**
* 自チームと相手チームの体力を設定
*
* @param myTeumHp		自チームの体力ポインター
* @param otherTeumHp	相手チームの体力ポインター
*/
void ControlOwner::SetTeumHP(int* myTeumHp, int* otherTeumHp)
{
	this->myTeumHp = myTeumHp;
	this->otherTeumHp = otherTeumHp;
}

/**
* チーム体力を無限にする
*/
void ControlOwner::TeumHPInivinit()
{
	isTeamHpInfinit = true;
}

/**
* コントロールの初期化
*/
void ControlOwner::Initialize()
{
	// 初期ターゲットを設定
	targetOwner = otherTeamOwner[0];

	// カメラに自身のMSを設定
	myCamera->SetMsTransform(myMs->GetTransform().get());

	// カメラにターゲットを設定
	myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());

	// プレイヤーにカメラ設定
	myMs->SetCamera(myCamera->GetTransform().get());
	myMs->SetTargetMS(targetOwner->myMs.get());

	// ゲーム入力を作成
	gameInput = std::make_shared<GameInput>();

	// ゲーム入力を設定
	myMs->SetGameInput(gameInput.get());
}

/**
* 自チームの体力を取得
*/
int& ControlOwner::MyTeumHp() const
{
	return *myTeumHp;
}

/**
* 相手チームの体力を取得
*/
int& ControlOwner::OtherTeumHp() const
{
	return *otherTeumHp;
}

/**
* 自分の機体のコストでチーム体力を減らす
*/
void ControlOwner::TeumHpSud()
{
	*myTeumHp -= myMs->GetCost();
}

/**
* 距離を取得する
*/
float ControlOwner::GetDistance()
{
	if (targetOwner)
	{
		auto targetMs = targetOwner->myMs;
		if (targetMs)
		{
			return Vector3::Distance(targetMs->GetTransform()->position, myMs->GetTransform()->position);
		}
	}

	return 0.0f;
}

/**
* チーム体力が無限かどうか
*/
bool ControlOwner::GetTeumHPInifinit() const
{
	return isTeamHpInfinit;
}
