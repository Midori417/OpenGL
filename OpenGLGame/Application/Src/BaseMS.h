/**
* @file BaseMS.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngineSub.h"
using namespace FGEngine;


// 先行宣言
class PlayerManager;

/**
* 数制限のある武装
*/
struct NumArmer
{
	float maxAmo = 0;
	float amo = 0;
	float amoReloadtimer = 0;
	float amoReloadSpeed = 3.0f;
	std::string iconfileName;

public:

	void AmoReloadUpdate()
	{
		if (amo < maxAmo)
		{
			amoReloadtimer += Time::deltaTime();
			if (amoReloadtimer > amoReloadSpeed)
			{
				amo += 1;
				amoReloadtimer = 0;
			}
		}
	}

};

/**
* すべてのMSの基底コンポーネント
*/
class BaseMS : public Component
{
public:

	BaseMS() = default;
	virtual ~BaseMS() = default;


public:

	virtual void Damage(float damage){}

protected:

	/**
	* 地面についているチェック(衝突処理が甘いための応急処置)
	*/
	void GroundCheck()
	{
		groundTimer += Time::deltaTime();
		// 地面についたとき
		if (GetGameObject()->isGrounded)
		{
			groundTimer = 0;
			isGrond = true;
		}
		// 地面についてない時間がgroundTimeを超えたら地面から離れている
		if (groundTimer > groundTime)
		{
			isGrond = false;
		}
	}


private:

	// 基礎パラメータ
	struct Parameter
	{
		float hp = 0;		// 体力
		float hpMax = 0;	// 体力マックス
		const float boostPowerMax = 100;	// エネルギーマックス量
		float boostPower = 0;				// エネルギー量
		int weaponMax = 1;					// 武器の数
		unsigned short teum = -1;			// チームナンバー
	};

	// 攻撃パラメータ
	struct AttackParameter
	{
		float clossRangeDistance = 30;		// 近接攻撃有効距離
		float shotDistance = 60;			// 遠距離有効距離
	};

	float groundTimer = 0;
	const float groundTime = 0.2f;

protected:

	// プレイヤーマネージャー
	PlayerManager* playerManager;

	// カメラ
	Transform* cameraTrs;

	// 基礎パラメータ
	Parameter parameter;

	// 攻撃のパラメータ
	AttackParameter attackParameter;

	float powerHealSpeed = 20.0f;		// エネルギー回復速度

	std::vector<NumArmer*> numArmer;	// 武装配列

	// 地面判定
	bool isGrond = true;				// 地面判定

public:

	/**
	* プレイヤーマネージャーを設定
	*/
	void SetPlayerManager(PlayerManager* playerManager)
	{
		this->playerManager = playerManager;
	}

	/**
	* カメラの位置を設定
	*/
	void SetCameraTrs(Transform* cameraTrs)
	{
		this->cameraTrs = cameraTrs;
	}

	/**
	* 基礎パラメータを取得
	*/
	Parameter GetParameter() const
	{
		return parameter;
	}

	/**
	* 攻撃パラメータを取得
	*/
	AttackParameter AttackDistance()
	{
		return attackParameter;
	}

	/**
	* 武装配列を取得
	*/
	NumArmer* GetNumArmer(int i)
	{
		return numArmer[i];
	}

};

#endif // !BASEMS_H_INCLUDED
