/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "../BaseMs.h"
#include "FGEngine/Math/Vector3.h"

/**
* ガンダム
*/
class Gundam : public BaseMs
{
public:

	// コンストラクタ・デストラクタ
	Gundam() = default;
	
private:	// イベント

	/**
	* 生成時に実行
	*/
	virtual void Awake() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

private: // 便利

	/**
	* 必要なコンポーネント、変数が取得できているかチェック
	*/
	virtual bool Check();

private: // アイドル

	/**
	* アイドルアニメーションを再生可能かチェック
	*
	* @retval true	可能
	* @retval false	不可能
	*/
	bool IdleAnimationCheck() const;

	/**
	* アイドルアニメーションの処理
	*/
	void IdleAnimation() const;

private: // 移動

	/**
	* 移動できるかチェック
	* 
	* @retval true	可能
	* @retval false	不可能
	*/
	bool MoveCheck() const;

	/**
	* 移動処理
	*/
	void Move(const Vector2& moveAxis);

	/**
	* 移動アニメーションを再生可能かチェック
	* 
	* @retval true	可能
	* @retval false	不可能
	*/
	bool MoveAnimationCheck() const;

	/**
	* 移動アニメーションの処理
	*/
	void MoveAnimation() const;

private: // ダッシュ

	/**
	* ダッシュできるかチェック
	*
	* @retval true	可能
	* @retval false	不可能
	*/
	bool DashCheck() const;

	/**
	* ダッシュ処理
	*/
	void Dash(const Vector2& moveAxis, bool isBtn);

	/**
	* ダッシュアニメーションを再生可能かチェック
	*
	* @retval true	可能
	* @retval false	不可能
	*/
	bool DashAnimationCheck() const;

	/**
	* ダッシュアニメーションの処理
	*/
	void DashAnimation() const;

private: // ジャンプ

	/**
	* ジャンプ可能かチェック
	* 
	* @retval true	可能
	* @retval false	不可能
	*/
	bool JumpCheck() const;

	/**
	* ジャンプ処理
	*/
	void Jump(const Vector2& moveAxis, bool isBtn);

	/**
	* ジャンプアニメーションを再生可能かチェック
	*
	* @retval true	可能
	* @retval false	不可能
	*/
	bool JumpAnimationCheck() const;

	/**
	* ジャンプアニメーションの処理
	*/
	void JumpAnimation() const;

private: // ビームライフル射撃

	/**
	* ビームライフル構造体
	*/
	struct BeumRifle
	{
		// 弾
		int amo = 0;

		// 最大弾
		int amoMax = 0;

		// オブジェクト
		GameObjectPtr bullet;

		// 弾発射タイミング(アニメーションが再生されてから)
		const float shotTime = 0.2f;

		// 弾生成位置
		const Vector3 shotPos = Vector3(0, 0, 5);

		// 射撃中
		bool isNow = false;

		// 弾が発射したか
		bool isShot = false;

		// バックショットしているか
		bool isBackShot = false;
	};
	BeumRifle beumRifle;

	/**
	* ビームライフル射撃ができるかチェック
	* 
	* @retval true	可能
	* @retval false	不可能
	*/
	bool BeumRifleShotCheck() const;

	/**
	* ビームライフル射撃処理
	*/
	void BeumRifleShot(bool isBtn);

	/**
	* ビームライフル射撃アニメーションの処理
	* 
	* @param perY	垂直Y
	* @param dot	内積
	*/
	void BeumRifleShotAnimaion();

private:

	/**
	* 持っている武器
	*/
	enum class HandArmed
	{
		Rifle,

		Sable
	};
	HandArmed handArmed = HandArmed::Rifle;
};

#endif // !GUNDAM_H_INCLUDED
