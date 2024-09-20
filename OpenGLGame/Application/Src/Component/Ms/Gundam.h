/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "../BaseMs.h"

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

	/**
	* アイドル状態にする
	*/
	void IdleAnimation();

private: // 移動

	/**
	* 移動処理
	*/
	void Move(const Vector2& moveAxis);

	/**
	* 移動アニメーションの処理
	*/
	void MoveAnimation();

private:

	/**
	* 持っている武器
	*/
	enum class HandWeapon
	{
		Rifle,

		Sable
	};
	HandWeapon handWeapon = HandWeapon::Rifle;
};

#endif // !GUNDAM_H_INCLUDED
