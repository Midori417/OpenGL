/**
* @file HomingBullet.h
*/
#ifndef HOMINGBULLET_H_INCLUDED
#define HOMINGBULLET_H_INCLUDED
#include "BaseBullet.h"
#include "FGEngine/Math/Vector3.h"

// 先行宣言
class BaseMs;

/**
* 誘導弾
*/
class HomingBullet : public BaseBullet
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	HomingBullet() = default;

private: // イベント

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* クローンを作成する
	*/
	virtual ComponentPtr Clone() const override;

private:

	/**
	* ホーミング可能かチェック
	* 
	* @retval true	ホーミング可能
	* @retval flase	ホーミング不可
	*/
	bool HomingCheck() const;

	/**
	* ホーミング処理
	*/
	void Homing() const;

public:

	/**
	* パラメータを設定
	* 
	* @param damage			与えるダメージ
	* @param speed			弾の速さ
	* @param destroyTime	消滅するまでの時間
	* @param homingPower	誘導力
	*/
	void SetParamater(float damage, float speed, float destroyTime, float homingPower = 0);

	/**
	* ターゲット機体を設定
	* 設定しない場合まっすぐ飛ぶ弾になる
	*/
	void SetTarget(BaseMs* target);

private:

	// 誘導力
	float homingPower = 0;

	// trueなら誘導弾にする
	bool isHoming = false;

	// ターゲットの機体
	BaseMs* target = nullptr;

	// 発射位置
	Vector3 shotPos = Vector3::zero;
};

#endif // !HOMINGBULLET_H_INCLUDED
