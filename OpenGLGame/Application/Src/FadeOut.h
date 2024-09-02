/**
* @file FadeOut.h
*/
#ifndef FADEOUT_H_INCLUDED
#define FADEOUT_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::UI;

/**
* フェードアウトコンポーネント
*/
class FadeOut : public GameEvent
{
public:

	// コンストラクタ・デストラクタ
	FadeOut() = default;
	virtual ~FadeOut() = default;

	/**
	* フェードを開始する
	*/
	void FadeStart();

	/**
	* フェードが始まっているかを取得
	* 
	* @retval true 始まっている
	* @retval false 始まっていない
	*/
	bool IsFadeStart() const;

	/**
	* フェードの状況を取得
	*
	* @retval true	フェード終了
	* @retval false	終わっていない
	*/
	bool IsFadeOut() const;

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	virtual ComponentPtr Clone() const override
	{
		return nullptr;

	}

public:

	// イメージコンポーネント
	ImagePtr image;

	// フェード速度
	float speed = 1;

private:

	// フェードを開始するか
	bool isStart = false;

	// フェードが終わればtrue : 終わってなければfalse
	bool isFadeOut = false;
};


#endif // !FADEOUT_H_INCLUDED
