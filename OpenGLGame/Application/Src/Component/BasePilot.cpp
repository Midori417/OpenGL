/**
* @file BasePilot.cpp
*/
#include "BasePilot.h"

#include "BaseMs.h"
#include "CameraManager.h"

/**
* 自チームと相手チームの体力を設定
*
* @param myTeamHp		自チームの体力ポインター
* @param otherTeamHp	相手チームの体力ポインター
*/
void BasePilot::SetTeamHP(int* myTeamHp, int* otherTeamHp)
{
	this->myTeamHp = myTeamHp;
	this->otherTeamHp = otherTeamHp;
}

/**
* チーム体力を無限にする
*/
void BasePilot::TeamHPInivinit()
{
	isTeamHpInfinit = true;
}

/**
* コントロールの初期化
*/
void BasePilot::Initialize()
{
	// 初期ターゲットを設定
	targetOwner = otherTeamOwner[0];

	// カメラに自身のMSを設定
	myCamera->SetMyMs(myMs->GetTransform());

	// カメラにターゲットを設定
	myCamera->SetTarget(targetOwner->myMs->GetTransform());

	// プレイヤーにカメラ設定
	myMs->SetCamera(myCamera->GetTransform().get());
	myMs->SetTargetMS(targetOwner->myMs.get());

	// ゲーム入力を作成
	gameInput = std::make_shared<GameInput>();

	// ゲーム入力を設定
	myMs->SetGameInput(gameInput.get());
}

/**
* 自身の機体が死亡したときの処理
*/
void BasePilot::MyMsDeadUpdate()
{
	if (!isMsDeath)
	{
		if (!GetTeumHPInifinit())
		{
			// 自チームのHpを減らす
			TeumHpSud();
		}
		isMsDeath = true;
		responTimer = 0;
	}
	// チーム体力が0以上だったら復活させる
	if (MyTeamHp() > 0)
	{
		responTimer += Time::DeltaTime();
		if (responTimer > responTime)
		{
			int index = Random::Range(0, (int)responPoss.size() - 1);
			// 自チームの体力がコスト以上あればそのままの体力で復活
			if (MyTeamHp() >= myMs->GetCost())
			{
				myMs->Respon(responPoss[index], 1);
			}
			// 自チームの体力がコスト以下ならば体力カットして復活
			else if (MyTeamHp() < myMs->GetCost())
			{
				float hp = static_cast<float>(MyTeamHp());
				float cost = static_cast<float>(myMs->GetCost());
				float hpCut = ((cost - hp) / cost);
				myMs->Respon(responPoss[index], hpCut);
			}
			isMsDeath = false;
		}
	}
}

/**
* ターゲットの処理
*/
void BasePilot::TargetUpdate()
{
	// ターゲット切り替え
	if (gameInput->targetChangeBtn && otherTeamOwner.size() > 1)
	{
		if (targetOwner == otherTeamOwner[0])
		{
			targetOwner = otherTeamOwner[1];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SetTarget(targetOwner->myMs->GetTransform());
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			targetOwner = otherTeamOwner[0];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SetTarget(targetOwner->myMs->GetTransform());
		}
	}
	// ターゲットの機体が死んだら
	if (targetOwner->myMs->IsDeath() && otherTeamOwner.size() > 1)
	{
		if (targetOwner == otherTeamOwner[0])
		{
			targetOwner = otherTeamOwner[1];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SetTarget(targetOwner->myMs->GetTransform());
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			targetOwner = otherTeamOwner[0];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SetTarget(targetOwner->myMs->GetTransform());
		}
	}
}

/**
* 自チームの体力を取得
*/
int& BasePilot::MyTeamHp() const
{
	return *myTeamHp;
}

/**
* 相手チームの体力を取得
*/
int& BasePilot::OtherTeamHp() const
{
	return *otherTeamHp;
}

/**
* 自分の機体のコストでチーム体力を減らす
*/
void BasePilot::TeumHpSud()
{
	*myTeamHp -= myMs->GetCost();
}

/**
* 距離を取得する
*/
float BasePilot::GetDistance()
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
bool BasePilot::GetTeumHPInifinit() const
{
	return isTeamHpInfinit;
}
