/**
* @file BaseMs.h
*/
#ifndef BASEMS_H_INCLUDED
#define BASEMS_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

// 先行宣言
struct GameInput;

/**
* MSの基底コンポーネント
*/
class BaseMs : public GameEvent
{
protected: // このコンポーネント継承先で実体化する

	/**
	* デフォルトコンストラクタ
	*/
	BaseMs() = default;

public:

	/**
	* 攻撃を受けたときに相手に呼び出してもらう
	* 
	* @parama damage 与えるダメージ
	*/
	virtual void Damage(float damage){}

	/**
	* 敵との距離を設定
	*
	* @param distance 敵との距離
	*/
	void SetDistance(float distance);

	/**
	* カメラトランスフォームの設定
	*/
	void SetCamera(Transform* camera);

	/**
	* ターゲットMSの設定
	*/
	void SetTargetMS(BaseMs* baseMS);

	/**
	* 機体入力を設定する
	*/
	void SetGameInput(GameInput* gameInput);

	/**
	* 機体が破壊されているか取得
	*/
	bool IsDestroy() const;

protected:

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

	/**
	* 破壊チェック
	*/
	bool DestroyCheck() const;

	/**
	* 破壊する
	*/
	void Destroy();

protected:

	// 機体の名前
	std::string name = "MS";

	GameInput* gameInput = nullptr;

	// コンポーネント
	RigidbodyPtr rb = nullptr;
	GltfMeshRendererPtr meshRender = nullptr;
	AnimatorPtr anim = nullptr;
	std::vector<AudioSourcePtr> audioSource;

private:

	//trueだと破壊されている
	bool isDestroy = false;

	// ターゲットとの距離
	float distance = 0;

	// カメラのトランスフォーム
	Transform* trsCamera;

	// ターゲットMS
	BaseMs* targetMs;

protected:

	/**
	* 基礎パラメータ
	*/
	struct Paramater
	{
		// 機体のコスト
		int cost = 0;

		// 機体の最大耐久値
		float hpMax = 0;

		// 機体耐久値
		float hp = 0;
	};
	Paramater paramater;

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
	BoostParamater boost;

protected: // 移動

	/**
	* 移動パラメータ
	*/
	struct MoveParamater
	{
		// 移動速度
		float speed = 0;

		// 旋回速度
		float rotationSpeed = 0;
	};
	MoveParamater move;

	/**
	* ジャンプパラメータ
	*/
	struct JumpParamater
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
	JumpParamater jump;

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
	DashParamater dash;
};

#endif // !BASEMS_H_INCLUDED
