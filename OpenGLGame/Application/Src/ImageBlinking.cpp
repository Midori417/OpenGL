/**
* ImageBlinking.cpp
*/
#include "ImageBlinking.h"

/**
* 更新
*/
void ImageBlinking::Update()
{
	// イメージがなければ何もしないまたはループじゃない
	if (!image)
	{
		return;
	}

	if (is)
	{
		image->color.a += speed *Time::DeltaTime();
		if (image->color.a >= 1)
		{
			image->color.a = 1;
			// 消えていくに設定
			is = false;
		}
	}
	else
	{
		image->color.a -= 0.5f * Time::DeltaTime();
		if (image->color.a <= 0)
		{
			image->color.a = 0;
			// 消えていくに設定
			is = true;
		}

	}
}
