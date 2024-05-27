/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine.h"
#include "GameInput.h"
using namespace FGEngine;

// 先行宣言
struct DamageInfo;
struct GameInput;

/**
* UIに表記する武装
*/
struct NumWeapon
{
	// 名前
	std::string name;

	// 残弾マックス
	float amoMax = 0;

	// 残弾
	float amo = 0;

	// リロードタイマー
	float reloadTimer = 0;

	// リロードタイム
	float reloadTime = 0;

	// 武器アイコン
	TexturePtr iconTexture;

	virtual void Initialize(){}
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
	* Hpを取得
	*/
	int GetHP() const;
	float GetHP01();

	/**
	* エネルギー残量の取得(0～1)
	*/
	float GetBoostEnergy() const;

	/**
	* 機体コストを取得
	*/
	int GetCost() const;

	/**
	* 死亡状態を取得
	* 
	* @retval true	死亡
	* @retval false 生存
	*/
	bool IsDeath() const;

	/**
	* 敵との距離を設定
	* 
	* @param distance 敵との距離
	*/
	void SetDistance(float distance);

	/**
	* 生き返る
	* 
	* @param removePos	生き返る位置
	* @param hpCut		体力のカット率
	*/
	virtual void Respon(const Vector3& removePos, float hpCut){}

	/**
	* ダメージを与える
	*
	* @param damageInfo ダメージ情報
	*/
	virtual void Damage(const DamageInfo& damgeInfo) {}

	/**
	* カメラトランスフォームの設定
	*/
	void SetCamera(Transform* camera);

	/**
	* ターゲットMSの設定
	*/
	void SetTargetMS(BaseMs* baseMS);

	/**
	* ゲーム入力を設定
	*/
	void SetGameInput(GameInput* gameInput);

protected:

	/**
	* 死亡チェック
	* 
	* @retval true	死亡
	* @retval false 生存
	*/
	bool DeadChaeck();

	/**
	* ブーストエネルギーの更新
	*/
	void BoostEnergyUpdate();

	/**
	* カメラのトランスフォームを取得
	*/
	Transform* GetCameraTransform() const;

	/**
	* ターゲットMSの取得
	*/
	BaseMs* GetTargetMs() const;

	/**
	* 敵との距離を取得
	*/
	float GetDistance() const;


public:

	// 数制限がる武器の配列
	std::vector<NumWeaponPtr> numWeapons;

	// 近接距離
	float proximityDistance = 0;

	// 赤ロック距離
	float redLookDistace = 0;

protected:

	// リギボ
	RigidbodyPtr rb;

	// アニメータ
	AnimatorPtr anim;

	// レンダラー
	GltfMeshRendererPtr renderer;

	// 入力
	GameInput* gameInput = nullptr;

	/**
	* 基礎パラメータ
	*/
	struct BaseParamater
	{
		// MSの名前
		std::string name;

		// 機体のコスト
		int cost = 0;

		// 機体のHPの最大値
		float hpMax = 0;

		// 機体のHP
		float hp = 0;

	};
	BaseParamater baseParamater;

	/**
	* ブーストパラメータ
	*/
	struct BoostParamater
	{
		// エネルギーの最大量
		const float max = 100;

		// 現在のエネルギー
		float current = 100;

		// 回復速度
		float chageSpeed = 500;

		// チャージ開始タイマー
		float chageStartTimer = 0;

		// チャージの開始速度
		const float chageStartTime = 0.2f;

		// チャージ開始速度(OVERHEATの場合)
		const float overHeatChageStartTime = 0.5f;

		// エネルギーを回復するか
		bool chageLock = false;
	};
	BoostParamater boostParamater;

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

		// ダッシュパラメータ
		DashParamater dash;

		// ジャンプパラメータ
		JumpPramter jump;
	};
	MoveParamater moveParamater;

	// 死亡状態
	bool isDeath = false;

	// ダウン値
	float downValue = 0;

	// 吹き飛び状態の有無
	bool isBlowAway = false;

	float blowAwayTimer = 0;

	float blowAwayTime = 1;

	float blowPower = 30.0f;

	bool isDown = false;

	// ダメージ状態の有無
	bool isDamage = false;

private:

	// 敵との距離
	float distance = 0;

	// カメラの位置
	Transform* cameraTrasform;

	// ターゲットのMS
	BaseMs* targetMs;

};

#endif // !BASEMS_H_INCLUDED
