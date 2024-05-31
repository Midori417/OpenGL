/**
* @file BaseMs.cpp
*/
#include "BaseMs.h"

bool BaseMs::isResoueLoad = false;

/**
* HPを取得
*/
int BaseMs::GetHP() const
{
	return static_cast<int>(baseParamater.hp);
}

/**
* HPを取得(0～1)
*/
float BaseMs::GetHP01()
{
	return Mathf::Clamp01((baseParamater.hpMax - (baseParamater.hpMax - baseParamater.hp)) / baseParamater.hpMax);
}

/**
* エネルギー残量の取得(0～1)
*/
float BaseMs::GetBoostEnergy() const
{
	return Mathf::Clamp01((boostParamater.max - (boostParamater.max - boostParamater.current)) / boostParamater.max);
}

/**
* 機体コストを取得
*/
int BaseMs::GetCost() const
{
	return baseParamater.cost;
}

/**
* 死亡か取得
*/
bool BaseMs::IsDeath() const
{
	return isDeath;
}

/**
* 敵との距離を設定
* 
* @param distance 敵との距離
*/
void BaseMs::SetDistance(float distance)
{
	this->distance = distance;
}

/**
* カメラのトランスフォームを設定
*/
void BaseMs::SetCamera(Transform* camera)
{
	this->cameraTrasform = camera;
}

/**
* ターゲットMSの設定
*/
void BaseMs::SetTargetMS(BaseMs* baseMS)
{
	this->targetMs = baseMS;
}

/**
* ゲーム入力を設定
*/
void BaseMs::SetGameInput(GameInput* gameInput)
{
	this->gameInput = gameInput;
}

/**
* 停止させる
*/
void BaseMs::Stop()
{
	isStop = true;
}

/**
* 死亡チェック
*
* @retval true	死亡
* @retval false 生存
*/
bool BaseMs::DeadChaeck()
{
	// すでに死亡していたら何もしない
	if (isDeath)
	{
		return true;
	}

	// HPがなければ死亡状態にする
	if (baseParamater.hp <= 0 || GetTransform()->position.y < -10)
	{
		// 死亡状態にする
		isDeath = true;
		// 描画しない
		renderer->enabled = false;
		rb->velocity = Vector3::zero;
		return true;
	}
	return false;
}

/**
* ブーストエネルギーの更新
*/
void BaseMs::BoostEnergyUpdate()
{
	// 地面についているとき
	if (rb->IsGround() && !boostParamater.chageLock)
	{
		// エネルギーの回復スタートタイマーが0以下なら
		if (boostParamater.chageStartTimer <= 0)
		{
			// ブーストエネルギーが減っていたら
			if (boostParamater.current < boostParamater.max)
			{
				// エネルギーを回復
				boostParamater.current += boostParamater.chageSpeed * Time::DeltaTime();
			}
		}
		else
		{
			// エネルギーチャージ開始タイマーを減らす
			boostParamater.chageStartTimer -= Time::DeltaTime();
		}
		boostParamater.current = Mathf::Clamp(boostParamater.current, 0.0f, boostParamater.max);
	}
}

/**
* 敵との距離を取得
*/
float BaseMs::GetDistance() const
{
	return distance;
}

/**
* カメラのトランスフォームを取得
*/
Transform* BaseMs::GetCameraTransform() const
{
	return cameraTrasform;
}

/**
* ターゲットMSを取得
*/
BaseMs* BaseMs::GetTargetMs() const
{
	return targetMs;
}

