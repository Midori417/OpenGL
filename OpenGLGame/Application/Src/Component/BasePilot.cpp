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
* コントロールの初期化
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
	myMs->SetCamera(myCamera->GetTransform().get());
	myMs->SetTargetMS(targetPilot->myMs.get());

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
	if (gameInput->targetChangeBtn && otherTeamPilots.size() > 1)
	{
		if (targetPilot == otherTeamPilots[0])
		{
			targetPilot = otherTeamPilots[1];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetPilot->myMs.get());
			myCamera->SetTarget(targetPilot->myMs->GetTransform());
		}
		else if (targetPilot == otherTeamPilots[1])
		{
			targetPilot = otherTeamPilots[0];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetPilot->myMs.get());
			myCamera->SetTarget(targetPilot->myMs->GetTransform());
		}
	}
	// ターゲットの機体が死んだら
	if (targetPilot->myMs->IsDeath() && otherTeamPilots.size() > 1)
	{
		if (targetPilot == otherTeamPilots[0])
		{
			targetPilot = otherTeamPilots[1];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetPilot->myMs.get());
			myCamera->SetTarget(targetPilot->myMs->GetTransform());
		}
		else if (targetPilot == otherTeamPilots[1])
		{
			targetPilot = otherTeamPilots[0];
			// カメラと機体にターゲットを持たせる
			myMs->SetTargetMS(targetPilot->myMs.get());
			myCamera->SetTarget(targetPilot->myMs->GetTransform());
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
	if (targetPilot)
	{
		auto targetMs = targetPilot->myMs;
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
