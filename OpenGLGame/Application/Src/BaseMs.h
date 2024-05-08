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
	virtual void Move(const Vector2&) {}

	// 攻撃
	virtual void Attack1() {}
	virtual void Attack2() {}

	/**
	* ダメージを与える
	*
	* @param damage 与えるダメージ
	*/
	virtual void Damage(float damage) {}

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
		// 地上での速度
		float groundSpeed = 0;

		// ダッシュの速度
		float dashSpeed = 0;

		// ジャンプ力
		float jumpPower = 0;
	};
	MoveParamater moveParamater;

private:

	// 敵との距離
	float distance = 0;

};

#endif // !BASEMS_H_INCLUDED
