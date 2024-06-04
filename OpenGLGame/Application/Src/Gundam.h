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

	// 持っている武装
	enum class HandWeapon
	{
		// ライフル
		Rifle,

		// サーベル
		Sable,
	};

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

	/**
	* サーベル構造体
	*/
	struct Sable : public BaseWeapon
	{
		// サーベル行動中か
		bool isNow = false;

		// 誘導かかっているか
		bool isHoming = false;

		// サーベル取得状態か
		bool isGet = false;

		Vector3* targetPos;

		/**
		* サーベル移動構造体
		*/
		struct Move
		{
			// サーベル移動中か
			bool isNow = false;


			// 攻撃移動を始めた位置
			Vector3 attackStartPos = Vector3::zero;

			// サーベル移動最大距離(誘導あり)
			const float useHomingDistanceMax = 30.0f;

			// サーベル移動最大距離(誘導なし)
			const float noHomingDistanceMax = 10.0f;

			// 攻撃開始距離
			const float attackDistance = 7.0f;

			float moveTimer = 0;

			const float moveTimeMax = 0;

			// サーベル移動速度
			float speed = 40.0f;

			// エネルギーの消費
			float useEnergy = 30.0f;
		};
		Move move;

		/**
		* サーベル攻撃構造体
		*/
		struct Attack
		{
			// サーベル攻撃中か
			bool isNow = false;

			// 攻撃時移動速度
			float speed = 15.0f;

			// 与えるダメージ
			float damage = 0;

			// 与えるダウン値
			float downPower = 0;

			// 攻撃判定消滅時間
			float destoryTime = 0.5f;

			// 攻撃判定を生成したか
			bool isSlash = false;

			// 攻撃判定生成時間
			float slashTime = 0.2f;

			// 移動時間
			float moveTime = 0.3f;

		};
		Attack attack1;
		Attack attack2;
		Attack attack3;
	};

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

	/*
	* ビームサーベル攻撃終了
	*/
	void SableAttackFailded(Sable::Attack& attack);

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
	HandWeapon handWeapon = HandWeapon::Rifle;

	// ライフル武装
	std::shared_ptr<Rifle> rifle;

	// バズーカ武装
	std::shared_ptr<Bazooka> bazooka;

	// サーベル武装
	std::shared_ptr<Sable> sable;

};

#endif // !GUNDAM_H_INCLUDED
