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

	/**
	* エネルギーの残量(0～1)を取得
	*/
	float GetBoostPower() const;

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
	virtual void Jump(bool isJump){}

	/**
	* ダッシュ
	*/
	virtual void Dash(bool isDash, const Vector2& mvoeAxis){}

	// 攻撃
	virtual void Attack1() {}
	virtual void Attack2() {}

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

protected:


	Teum teum = Teum::None;

	// 機体のコスト
	int cost = 0;

	// 機体のHPの最大値
	int hpMax = 0;

	// 機体のHP
	int hp = 0;

	// エネルギー最大量
	const float boostPowerMax = 100;

	// エネルギー使用量
	float boostPower = 0;

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
