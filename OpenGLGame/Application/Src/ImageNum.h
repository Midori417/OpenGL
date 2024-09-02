/**
* @file ImageNum.h
*/
#ifndef IMAGENUM_H_INCLUDED
#define IMAGENUM_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::UI;

class ImageNum : public GameEvent
{
public:

	// コンストラクタ・デストラクタ
	ImageNum() = default;
	virtual ~ImageNum() = default;

public:

	/**
	* 生成されたときに実行
	*/
	virtual void Awake() override;

	void Stop();

	virtual ComponentPtr Clone() const override
	{
		return nullptr;

	}

private:

	/**
	* 最初に実行
	*/
	virtual void  Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;


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
