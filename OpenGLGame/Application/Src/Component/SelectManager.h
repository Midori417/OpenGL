/**
* @file SelectManger.h
*/
#ifndef SELECTMANGER_H_INCLUDED
#define SELECTMANGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Color.h"
using namespace FGEngine;

// 先行宣言
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* 選択シーンの管理コンポーネント
*/
class SelectManager : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	SelectManager() = default;

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

	/**
	* 選択項目
	*/
	enum Select
	{
		// バトル画面に移動
		Battle,

		// ゲームを終了
		Exit,
	};
	// 現在選択している項目番号
	int selectNum = 0;

	// 未選択時の色
	Color noSelectColor = Color(0.5f, 0.5f, 0.5f, 1.0f);

	// 選択ボタンイメージコンポーネント配列
	std::vector<ImagePtr> imgButtons;

	// シーン切り替え時のフェードアウトコンポーネント
	FadeOutPtr fadeOut = nullptr;

	// 決定音を鳴らすためのコンポーネント
	AudioSourcePtr audioSource = nullptr;
};

#endif // !SELECTMANGER_H_INCLUDED
