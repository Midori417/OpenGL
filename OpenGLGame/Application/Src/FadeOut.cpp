/**
* @file FadeOut.cpp
*/
#include "FadeOut.h"

/**
* 最初に実行
*/
void FadeOut::Start()
{
	// コンポーネントを取得
	image = OwnerObject()->GetComponent<Image>();

	// イメージがなければ何もしない
	if (!image)
	{
		return;
	}

	image->color.a = 0;
}

/**
* 更新
*/
void FadeOut::Update()
{
	// イメージがなければ何もしない
	if (!image || isFadeOut || !isStart)
	{
		return;
	}

	// アルファ値を増加
	image->color.a += speed * Time::DeltaTime();
	if (image->color.a >= 1)
	{
		image->color.a = 1;
		isFadeOut = true; // フェード終了
	}
}

/**
* フェードの状況を取得
*
* @retval true	フェード終了
* @retval false	終わっていない
*/
bool FadeOut::IsFadeOut() const
{
	return isFadeOut;
}
