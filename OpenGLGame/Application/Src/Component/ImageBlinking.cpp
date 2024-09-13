/**
* @file ImageBlinking.h
*/
#include "ImageBlinking.h"
#include "FGEngine/Component/ComponentHelper.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Other/Time.h"

/**
* 毎フレーム実行
*/
void ImageBlinking::Update()
{
	if (!image)
	{
		image = GetComponent<Image>();
		return;
	}

	// 表示していく
	if (isBlinking)
	{
		image->color.a += speed * Time::DeltaTime();

		// 完全に表示されたら
		if (image->color.a >= 1)
		{
			image->color.a = 1;
			// 透けていく状態にする
			isBlinking = false;
		}
	}
	// 透けていく
	else
	{
		image->color.a -= speed * Time::DeltaTime();

		// 透明になったら
		if (image->color.a <= 0)
		{
			image->color.a = 0;
			
			// 表示していく
			isBlinking = true;
		}
	}
}

/**
* イメージ点滅コンポーネントのクローンを作成
*
* @return クローンしたイメージ点滅コンポーネント
*/
ComponentPtr ImageBlinking::Clone() const
{
	auto ptr = std::make_shared<ImageBlinking>();

	ptr->image = this->image;
	ptr->speed = this->speed;

	return ptr;
}
