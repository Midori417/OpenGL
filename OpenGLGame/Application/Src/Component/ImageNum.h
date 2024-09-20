/**
* @file ImageNum.h
*/
#ifndef IMAGENUM_H_INCLUDED
#define IMAGENUM_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

class ImageNum : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	ImageNum() = default;

private:

	/**
	* 生成されたときに実行
	*/
	virtual void Awake() override;

	/**
	* 最初に実行
	*/
	virtual void  Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

public:

	void Stop();

public:

	// 描画する数字
	int num = 0;

	// 調整
	Vector2 offsetPos = Vector2::zero;

	// 間隔
	float space = 50;

	// 数字の大きさ
	float scale = 1;

private:
	
	// 数字を入れる描画するイメージコンポーネント
	std::vector<ImagePtr> imgNums;

	// 数字テクスチャ配列
	std::vector<TexturePtr> texNums;
};


#endif // !IMAGENUM_H_INCLUDED
