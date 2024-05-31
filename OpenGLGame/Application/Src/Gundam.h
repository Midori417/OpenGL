/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "BaseMs.h"
#include "BaseWeapon.h"

/**
* ガンダム
*/
class Gundam : public BaseMs
{
public:

	// コンストラクタ・デストラクタ
	Gundam() = default;
	virtual ~Gundam() = default;

	/**
	* 最初に実行
	*/
	virtual void Awake() override;

private:


	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* リロード更新
	*/
	void ReloadUpdate();

	/**
	* 移動
	* 
	* @param moveAxis 入力軸
	*/
	void Move(const Vector2& moveAxis);

	/**
	* ジャンプ
	* 
	* @param jumpBtn	ジャンプボタンの状態
	* @param moveAxis	入力軸
	*/
	void Jump(bool jumpBtn, const Vector2& moveAxis);

	/**
	* ダッシュ
	* 
	* @param dashBtn	ダッシュボタンの状態
	* @param moveAxis	入力軸
	*/
	void Dash(bool dashBtn, const Vector2& moveAxis);

	/**
	* 攻撃(ビームライフル)
	* 
	* @param acttion1Btn アクションボタン1の状態
	*/
	void Action1(bool acttion1Btn);

	/**
	* 攻撃2(バズーカ)
	* 
	* @param acttion2Btn アクションボタン2の状態
	*/
	void Action2(bool acttion2Btn);

	/**
	* 攻撃3(ビームサーベル)
	* 
	* @param acttion3Btn アクションボタン3の状態
	*/
	void Action3(bool acttion3Btn);

public:

	/**
	* ダメージを与える
	*
	* @param damageInfo ダメージ情報
	*/
	virtual void Damage(const DamageInfo& damgeInfo)override;

	/**
	* 生き返る
	*
	* @param removePos	生き返る位置
	* @param hpCut		体力のカット率
	*/
	virtual void Respon(const Vector3& removePos, float hpCut) override;

private:

	/**
	* ライフル構造体
	*/
	struct Rifle : public ShotWeaponUI
	{

		// 射撃状態か
		bool isNow = false;

		// 撃ったか
		bool isShot = false;

		// 停止して打つか
		bool isStopShot = false;

		/**
		* 初期化
		*/
		virtual void Initialize() override
		{
			amo = amoMax;
			isNow = false;
			isShot = false;
			isStopShot = false;
		}
	};
	std::shared_ptr<Rifle> rifle;

	/**
	* バズーカ構造体
	*/
	struct Bazooka : ShotWeaponUI
	{
		// 射撃状態か
		bool isNow = false;

		// 撃ったか
		bool isShot = false;

		/**
		* 初期化
		*/
		virtual void Initialize() override
		{
			amo = amoMax;
			isNow = false;
			isShot = false;
		}
	};
	std::shared_ptr<Bazooka> bazooka;

};

#endif // !GUNDAM_H_INCLUDED
