/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
#include "../GameInput.h"

// 先行宣言
struct DamageInfo;
struct GameInput;
class UIWeapon;
using UIWeaponPtr = std::shared_ptr<UIWeapon>;

/**
* MSの基底クラス
*/
class BaseMs : public GameEvent
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

	/**
	* 停止させる
	*/
	void Stop();

	/**
	* 誘導可能かチェック
	*
	* @retval true  誘導可能
	* @retval false 誘導不可
	*/
	bool HomingCheck() const;

	bool GetHoimngCancel() const;

	virtual ComponentPtr Clone() const override
	{
		return nullptr;

	}

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

	/**
	* ブーストエネルギーがオーバーヒートしてるか
	*/
	void BoostCheck();


public:

	// UIに表示する武装
	std::vector<UIWeaponPtr> uiWeapons;

	// 近接距離
	float proximityDistance = 0;

	// 赤ロック距離(平行)
	float redLookDistaceXZ = 0;

	// 赤ロック距離(+Y)
	float redLookDistanceMaxY = 0;

	// 赤ロック距離(-Y)
	float redLookDistanceMinY = 0;

protected:

	// リギボ
	RigidbodyPtr rb;

	// アニメータ
	AnimatorPtr anim;

	// レンダラー
	GltfMeshRendererPtr renderer;

	// 入力
	GameInput* gameInput = nullptr;

	// リソース読み込み
	static bool isResoueLoad;

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

		struct Step
		{
			Vector3 direction = Vector3::zero;

			float useEnergy = 0.0f;
			
			bool isNow = false;

			float speed = 0.0f;
		};

	public:

		// 通常速度
		float speed = 0;

		// 通常時の旋回速度
		float rotationSpeed = 0;

		float moveTimer = 0;

		const float moveTime = 0.3f;

		// ダッシュパラメータ
		DashParamater dash;

		// ジャンプパラメータ
		JumpPramter jump;

		// ステップパラメータ
		Step step;
	};
	MoveParamater moveParamater;

	// 死亡状態
	bool isDeath = false;

	// ダウン値
	float downValue = 0;

	/**
	* 吹き飛び構造体
	*/
	struct BlowAway
	{
		// 吹き飛び状態か
		bool isNow = false;

		// 吹き飛ぶ時間
		float timer = 0;

		float time = 0.5f;

		float power = 70.0f;
	};
	BlowAway blowAway;

	bool isDownCancel = false;

	bool isDown = false;

	// ダウンしてからの時間
	float downTimer = 0;
	
	// ダウンしてから強制立ち上がりの時間
	const float downStandUpTime = 3;

	// ダメージ状態の有無
	bool isDamage = false;

	float responTimer = 0;
	float responTime = 0.5f;

	// リスポーン状態
	bool isRespon = false;

	// ストップさせる
	bool isStop = false;

private:

	// 敵との距離
	float distance = 0;

	// カメラの位置
	Transform* cameraTrasform;

	// ターゲットのMS
	BaseMs* targetMs;

};

#endif // !BASEMS_H_INCLUDED
