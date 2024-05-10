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

public:

	/**
	* 移動
	* 
	* @param moveAxis 入力軸
	*/
	virtual void Move(const Vector2& moveAxis) override;

	virtual void CpuMove() override;

	/**
	* ジャンプ
	*/
	virtual void Jump(bool isJump) override;

	/**
	* ダッシュ
	*/
	virtual void Dash(bool isDash, const Vector2& moveAxis) override;

private:

	// リギボ
	RigidbodyPtr rb;

	// アニメータ
	AnimatorPtr anim;
};

#endif // !GUNDAM_H_INCLUDED
