/**
* @file ImageBlinking.h
*/
#ifndef IMAGEBLINKING_H_INCLUDED
#define IMAGEBLINKING_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/UsingNames/UsingComponent.h"
using namespace FGEngine;

/**
* イメージを点滅する
*/
class ImageBlinking : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	ImageBlinking() = default;

private:

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* イメージ点滅コンポーネントのクローンを作成
	* 
	* @return クローンしたイメージ点滅コンポーネント
	*/
	virtual ComponentPtr Clone() const override;

public:

	// 点滅速度
	float speed = 1;

private:

	// イメージコンポーネント
	ImagePtr image = nullptr;

	// 点滅の制御
	bool isBlinking = false;
};
using ImageBlinkingPtr = std::shared_ptr<ImageBlinking>;

#endif // !IMAGEBLINKING_H_INCLUDED