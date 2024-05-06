/**
* @file ImagaeBlinking.h
*/
#ifndef IMAGEBLINKING_H_INCLUDED
#define IMAGEBLINKING_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

class ImageBlinking : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	ImageBlinking() = default;
	virtual ~ImageBlinking() = default;

private:

	/**
	* 更新
	*/
	virtual void Update() override;

public:
	
	// 点滅させるImageコンポーネント
	UI::ImagePtr image;

	// 点滅の速度
	float speed = 0.1f;

private:

	// true=つける:false=消える
	bool is = false;
};

#endif // !GUNDAMEYEBLINKING_H_INCLUDEDD
