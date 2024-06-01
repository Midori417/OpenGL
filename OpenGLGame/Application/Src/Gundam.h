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

	// 持っている武装
	enum class HandWeapon
	{
		// ライフル
		Rifle,

		// サーベル
		Sable,
	};
	HandWeapon handWeapon = HandWeapon::Rifle;

	/**
	* ライフル構造体
	*/
	struct Rifle : public ShotWeaponUI
	{

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

	/**
	* サーベル構造体
	*/
	struct Sable : public BaseWeapon
	{
		// サーベル行動中か
		bool isNow = false;

		/**
		* サーベル移動構造体
		*/
		// サーベル取得状態か
		bool isGet = false;
		struct Move
		{
			// サーベル攻撃移動中か
			bool isNow = false;

			// 攻撃移動を始めた位置
			Vector3 attackStartPos = Vector3::zero;

			// サーベル移動最大距離
			float distanceMax = 50.0f;

			// サーベル移動速度
			float speed = 40.0f;
		};
		Move move;

		/**
		* サーベル攻撃構造体
		*/
		struct Attack
		{
			bool isNow = false;

		};
		Attack attack1;
		Attack attack2;
		Attack attack3;
	};
	std::shared_ptr<Sable> sable;

};

#endif // !GUNDAM_H_INCLUDED
