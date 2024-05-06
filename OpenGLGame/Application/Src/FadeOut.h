/**
* @file FadeOut.h
*/
#ifndef FADEOUT_H_INCLUDED
#define FADEOUT_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::UI;

class FadeOut : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	FadeOut() = default;
	virtual ~FadeOut() = default;

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 更新
	*/
	virtual void Update() override;

public:

	/**
	* フェードの状況を取得
	* 
	* @retval true	フェード終了
	* @retval false	終わっていない
	*/
	bool IsFadeOut() const;

public:

	// イメージコンポーネント
	ImagePtr image;

	float speed = 1;

	// フェードを開始するか
	bool isStart = false;

private:

	// フェードが終わればtrue : 終わってなければfalse
	bool isFadeOut = false;
};


#endif // !FADEOUT_H_INCLUDED
