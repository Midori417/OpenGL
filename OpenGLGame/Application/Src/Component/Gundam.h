/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "BaseMs.h"

/**
* ガンダム
*/
class Gundam : public BaseMs
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	Gundam() = default;

private:

	/**
	* 生成時に実行
	*/
	virtual void Awake() override;

	/**
	* Updateが始まる前に一度実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* ガンダムコンポーネントをクローンをする
	* 
	* @return クローンされたガンダムコンポーネント
	*/
	virtual ComponentPtr Clone() const override;

private: // 移動

	/**
	* 移動
	* 
	* @param moveAxis 移動入力
	*/
	void Move(const Vector2& moveAxis);

	/**
	* ジャンプ
	*/
	void Jump(bool jumpBtn, const Vector2& moveAxis);

	/**
	* ダッシュ
	*
	* @param dashBtn	ダッシュボタンの状態
	* @param moveAxis	入力軸
	*/
	void Dash(bool dashBtn, const Vector2& moveAxis);

private: // 射撃攻撃

	/**
	* 攻撃(ビームライフル)
	*
	* @param acttion1Btn アクションボタン1の状態
	*/
	void BeumRifle(bool acttion1Btn);

	/**
	* 攻撃2(バズーカ)
	*
	* @param acttion2Btn アクションボタン2の状態
	*/
	void Bazooka(bool acttion2Btn);


private: // 武装


private:

	/**
	*  持っている武装
	*/
	enum class HandWeapon
	{
		// ライフル
		Rifle,

		// サーベル
		Sable,
	};
	// 持っている武装
	HandWeapon handWeapon = HandWeapon::Rifle;

};

#endif // !GUNDAM_H_INCLUDED
