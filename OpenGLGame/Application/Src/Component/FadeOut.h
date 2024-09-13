/**
* @file FadeOut,h
*/
#ifndef FADEOUT_H_INCLUDED
#define FADEOUT_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/UsingNames/UsingComponent.h"
using namespace FGEngine;

/**
* フェードアウトオブジェクトコンポーネント
*/
class FadeOut : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	FadeOut() = default;

public:

	/**
	* フェードを開始する
	*/
	void FadeStart();

	/**
	* フェードが開始しているか取得
	* 
	* @retval true	始めっている
	* @retval false 始まっていない
	*/
	bool IsFadeStart() const;

	/**
	* フェードの状況を取得
	* 
	* @retval true	フェードアウト完了
	* @retval false	フェード中またはフェード開始していない
	*/
	bool IsFadeOut() const;

private:

	/**
	* Updateが始まる前に一度実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* フェードアウトコンポーネントをクローンする
	* 
	* @return クローンしたフェードアウトコンポーネント
	*/
	virtual ComponentPtr Clone() const override;

public:

	// フェードアウトする速度
	float speed = 1;

private:

	// イメージコンポーネント
	ImagePtr image = nullptr;

	// trueならフェードを開始する
	bool isStart = false;

	// フェードが完了したらtrue
	bool isFadeOut = false;

};
using FadeOutPtr = std::shared_ptr<FadeOut>;

#endif // !FADEOUT_H_INCLUDED
