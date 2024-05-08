/**
* @file ChoiceManager.h
*/
#ifndef CHOICEMANAGER_H_INCLUDED
#define CHOICEMANAGER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;


class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* 選択シーン管理クラス
*/
class ChoiceManager : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	ChoiceManager() = default;
	virtual ~ChoiceManager() = default;

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

private:

	/**
	* 選択
	*/
	enum class GameChoice
	{
		// 戦闘
		Battle,

		// オプション
		Option,

		// ゲーム終了
		Exit,
	};

	GameChoice choice = GameChoice::Battle;
	int choiceNum = 0;

	// 選択色
	Color highlightedColor = Color{ 0.7f, 0.7f, 0.7f , 1 };

	// ボタンが押されたら
	bool isFadeStart = false;

public:

	// ボタン配列
	std::vector<UI::ImagePtr> imgButtons;

	// フェードコンポーネント
	FadeOutPtr fadeOut;

};

#endif // !CHOICEMANAGER_H_INCLUDED
