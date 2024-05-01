/**
* @file Image.h
*/
#ifndef COMPONENT_IMAGE_H_INCLUDED
#define COMPONENT_IMAGE_H_INCLUDED
#include "ImGuiUI.h"
#include "Vector2.h"
#include "Color.h"
#include <string>

/**
* UI画像
*/
class Image : public ImGuiUI
{
public:

	// コンストラクタ
	Image() = default;

	// デストラクタ
	virtual ~Image() = default;


private:

	// UI処理部
	virtual void UIUpdate() override;

public:

	std::string filename;	// テクスチャのファイル名

	Vector2 size = Vector2::zero;
	Color color = Color::black;

	float radian = 0;

	float fillAmout = 1;	
};
using ImagePtr = std::shared_ptr<Image>;

#endif // !COMPONENT_IMAGE_H_INCLUDED
