/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

enum class Teum
{
	// チーム無し
	None,

	// 赤チーム
	Red,

	// 青チーム
	Blue,
};

/**
* UIに表記する武装
*/
struct NumWeapon
{
	// 名前
	std::string name;

	// 残弾マックス
	int amoMax = 0;

	// 残弾
	int amo = 0;

	// リロードタイマー
	float reloadTimer = 0;

	// リロードタイム
	float reloadTime = 0;

	// 武器アイコン
	TexturePtr iconTexture;
};
using NumWeaponPtr = std::shared_ptr<NumWeapon>;

/**
* MSの基底クラス
*/
class BaseMs : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	BaseMs() = default;
	virtual ~BaseMs() = default;

	/**
	* チームを取得
	*/
	Teum GetTeum() const;

	/**
	* Hpを取得
	*/
	int GetHP() const;

	float GetHP01();

	/**
	* エネルギー残量の取得(0～1)
	*/
	float GetBoostEnergy() const;


	/**
	* 敵との距離を設定
	* 
	* @param distance 敵との距離
	*/
	void SetDistance(float distance);

	/**
	* 敵との距離を取得
	*/
	float GetDistance() const;

	/**
	* 移動
	*
	* @param moveAxis 入力軸
	*/
	virtual void Move(const Vector2& moveAxis) {}

	/**
	* CPU移動
	*/
	virtual void CpuMove(){}

	/**
	* ジャンプ
	*/
	virtual void Jump(bool isJump, const Vector2& moveAxis){}

	/**
	* ダッシュ
	*/
	virtual void Dash(bool isDash, const Vector2& mvoeAxis){}

	// 攻撃
	virtual void Attack1(bool attackKey) {}
	virtual void Attack2(bool attackKey2) {}

	/**
	* ダメージを与える
	*
	* @param damage 与えるダメージ
	*/
	virtual void Damage(float damage) {}

	/**
	* カメラトランスフォームの設定
	*/
	void SetCamera(Transform* camera);

	/**
	* カメラのトランスフォームを取得
	*/
	Transform* GetCameraTransform() const;

	/**
	* ターゲットMSの設定
	*/
	void SetTargetMS(BaseMs* baseMS);

	/**
	* ターゲットMSの取得
	*/
	BaseMs* GetTargetMs() const;


public:


	// MSの名前
	std::string name;

	// 数制限がる武器の配列
	std::vector<NumWeaponPtr> numWeapons;

	// 近接距離
	float proximityDistance = 0;

	// 赤ロック距離
	float redLookDistace = 0;

protected:

	// チーム
	Teum teum = Teum::None;

	// 機体のコスト
	int cost = 0;

	// 機体のHPの最大値
	float hpMax = 0;

	// 機体のHP
	float hp = 0;

	// 死んでるかの有無
	bool isDeath = false;

	// エネルギー最大量
	const float boostEnergyMax = 100;

	// エネルギー
	float boostEnergy = 100;

	// エネルギー回復速度
	float boostEnergyChage = 500;

	// 地面についてからのチャージ速度
	float boostEnergyChageTimer = 0;

	// 地面についてからのチャージ開始までの速度
	float boostEnergyChageStartTime = 0.3f;

	// 地面についてからのチャージ開始までの速度(OVERHEATの場合)
	float boostEnergyChageOverHeatStartTime = 1;

	// エネルギー回復のロックの有無
	bool boostEnergyChageLock = false;

	/**
	* 移動パラメータ
	*/
	struct MoveParamater
	{
	private:

		/**
		* ダッシュパラメータ
		*/
		struct DashParamater
		{
			// 移動速度
			float speed = 0;

			// 旋回速度
			float rotationSpeed = 0;

			// エネルギーの消費量
			float useEnergy = 0;

			// ダッシュ中か
			bool isNow = false;
		};

		/**
		* ジャンプパラメータ
		*/
		struct JumpPramter
		{
			// ジャンプ力
			float power = 0;

			// 移動速度
			float speed = 0;

			// 旋回速度
			float rotationSpeed = 0;

			// エネルギーの消費量
			float useEnergy = 0;

			// ジャンプ中か
			bool isNow = false;
		};

	public:

		// 通常速度
		float speed = 0;

		// 通常時の旋回速度
		float rotationSpeed = 0;

		DashParamater dash;

		JumpPramter jump;
	};
	MoveParamater moveParamater;

private:

	// 敵との距離
	float distance = 0;

	// カメラの位置
	Transform* cameraTrasform;

	// ターゲットのMS
	BaseMs* targetMs;

};

#endif // !BASEMS_H_INCLUDED
