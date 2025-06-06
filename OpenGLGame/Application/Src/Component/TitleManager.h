/**
* @file TitleManager.h
*/
#ifndef TITLEMANAGER_H_INCLUDED
#define TITLEMANAGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/UsingNames/UsingComponent.h"
using namespace FGEngine;

// 先行宣言
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* タイトルシーンの管理コンポーネント
*/
class TitleManager : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	TitleManager() = default;

private:

	/**
	* Updateが始まる前に一度実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;
	
	/**
	* 特にクローンする予定がないので何も書かない
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

private:

	// シーン切り替え時のフェードアウトコンポーネント
	FadeOutPtr fadeOut = nullptr;

	// 決定音を鳴らすためのコンポーネント
	AudioSourcePtr audioSource = nullptr;
};

#endif // !TITLEMANAGER_H_INCLUDED
