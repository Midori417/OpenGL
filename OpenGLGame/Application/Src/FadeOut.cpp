/**
* @file FadeOut.cpp
*/
#include "FadeOut.h"
using namespace FGEngine::WindowSystem;

/**
* フェードを開始する
*/
void FadeOut::FadeStart()
{
	image->SetEnable(true);
	isStart = true;
}

/**
* フェードが始まっているかを取得
*
* @retval true 始まっている
* @retval false 始まっていない
*/
bool FadeOut::IsFadeStart() const
{
	return isStart;
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


/**
* 最初に実行
*/
void FadeOut::Start()
{
	// イメージコンポーネントを追加
	image = OwnerObject()->AddComponent<Image>();
	image->texture = AssetManager::GetInstance()->GetTexture("white");
	image->color = Color::black;
	image->size = WindowManager::GetInstance()->GetWindowSize();

	// アルファをゼロにする
	image->color.a = 0;
	image->SetEnable(false);
}

/**
* 毎フレーム実行
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

	// アルファ値が1以上になればフェードを終了する
	if (image->color.a >= 1)
	{
		image->color.a = 1;
		isFadeOut = true; // フェード終了
	}
}