/**
* @file ControlOwner.cpp
*/
#include "ControlOwner.h"
#include "BaseMs.h"
#include "LookOnCamera.h"

/**
* 自チームと相手チームの体力を設定
*
* @param myTeamHp		自チームの体力ポインター
* @param otherTeamHp	相手チームの体力ポインター
*/
void ControlOwner::SetTeamHP(int* myTeamHp, int* otherTeamHp)
{
	this->myTeamHp = myTeamHp;
	this->otherTeamHp = otherTeamHp;
}

/**
* チーム体力を無限にする
*/
void ControlOwner::TeamHPInivinit()
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
* 自身の機体が死亡したときの処理
*/
void ControlOwner::MyMsDeadUpdate()
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
void ControlOwner::TargetUpdate()
{
	// ターゲット切り替え
	if (gameInput->targetChangeBtn && otherTeamOwner.size() > 1)
	{
		if (targetOwner == otherTeamOwner[0])
		{
			targetOwner = otherTeamOwner[1];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			targetOwner = otherTeamOwner[0];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
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
			myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
		}
		else if (targetOwner == otherTeamOwner[1])
		{
			targetOwner = otherTeamOwner[0];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetOwner->myMs.get());
			myCamera->SelectTarget(targetOwner->myMs->GetTransform().get());
		}
	}
}

/**
* 自チームの体力を取得
*/
int& ControlOwner::MyTeamHp() const
{
	return *myTeamHp;
}

/**
* 相手チームの体力を取得
*/
int& ControlOwner::OtherTeamHp() const
{
	return *otherTeamHp;
}

/**
* 自分の機体のコストでチーム体力を減らす
*/
void ControlOwner::TeumHpSud()
{
	*myTeamHp -= myMs->GetCost();
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
