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

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

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
	virtual void Move(const Vector2& moveAxis);

private:

	float angle = 180;

	// リギボ
	RigidbodyPtr rb;

	// アニメータ
	AnimatorPtr anim;
};

#endif // !GUNDAM_H_INCLUDED
