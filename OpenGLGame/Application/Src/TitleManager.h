/**
* @file TitleManager.h
*/
#ifndef TITLEMANAGER_H_INCLUDED
#define TITLEMANAGER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

// 先行宣言
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* タイトル管理コンポーネント
*/
class TitleManager : public GameEvent
{
public:

	// コンストラクタ・デストラクタ
	TitleManager() = default;
	virtual ~TitleManager() = default;

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

private:

	// フェードアウト
	FadeOutPtr fadeOut;
};


#endif // !TITLEMANAGER_H_INCLUDED
