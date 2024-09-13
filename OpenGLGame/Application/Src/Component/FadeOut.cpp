/**
* @file FadeOut.cpp
*/
#include "FadeOut.h"
#include "FGEngine/Component/Image.h"
#include "FGEngine/Component/ComponentHelper.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Other/Time.h"

/**
* フェードを開始する
*/
void FadeOut::FadeStart()
{
	if (!image)
	{
		// イメージコンポーネントが設定されていなければ一度取得してみる
		image = GetComponent<Image>();
	}

	// 取得できていればスタートする
	if (image)
	{
		isStart = true;
		image->isActive = true;
	}
}

/**
* フェードが開始しているか取得
*
* @retval true	始めっている
* @retval false 始まっていない
*/
bool FadeOut::IsFadeStart() const
{
	return isStart;
}

/**
* フェードの状況を取得
*
* @retval true	フェードアウト完了
* @retval false	フェード中またはフェード開始していない
*/
bool FadeOut::IsFadeOut() const
{
	return isFadeOut;
}

/**
* Updateが始まる前に一度実行
*/
void FadeOut::Start()
{
	// イメージコンポーネントを取得してみる
	image = GetComponent<Image>();

	// 取得できなければイメージコンポーネントを追加する
	if (!image)
	{
		image = OwnerObject()->AddComponent<Image>();
		image->texture = AssetManager::GetInstance()->GetTexture("white");
		image->color = Color::black;
		image->SetWindowSize();

		// 透明にしておきたいのでアルファ値をゼロにする
		image->color.a = 0;
		// フェードするまで処理してほしくないので非アクティブ状態にする
		image->isActive = false;
	}
}

/**
* 毎フレーム実行
*/
void FadeOut::Update()
{
	if (!image)
	{
		// イメージコンポーネントが取得できていなければ何もしない
		return;
	}

	// フェードが開始していないまたはフェードがすでに終了している場合は更新を止める
	if (!isStart || isFadeOut)
	{
		return;
	}

	// イメージのアルファ値を増加
	image->color.a += speed * Time::DeltaTime();

	// イメージが完全に表示されたらフェードを終了する
	if (image->color.a >= 1)
	{
		image->color.a = 1;
		isFadeOut = true;
	}
}

/**
* フェードアウトコンポーネントをクローンする
*
* @return クローンしたフェードアウトコンポーネント
*/
ComponentPtr FadeOut::Clone() const
{
	auto ptr = std::make_shared<FadeOut>();

	ptr->isActive = this->isActive;
	ptr->image = this->image;
	ptr->isStart = this->isStart;
	ptr->isFadeOut = this->isFadeOut;
	ptr->speed = this->speed;

	return ptr;
}
