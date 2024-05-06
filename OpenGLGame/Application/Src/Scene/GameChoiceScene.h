/**
* @file GameChoiceScene.h
*/
#ifndef GAMECHOICESCENE_H_INCLUDED
#define GAMECHOICESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* ゲーム選択シーン
*/
class GameChiecScene : public Scene
{
public:

	// コンストラクタ
	GameChiecScene() = default;

	// デストラクタ
	virtual ~GameChiecScene() = default;

private:

	// ゲーム選択シーンの初期化
	virtual bool Initialize() override;

	// ゲーム選択シーンの更新
	virtual void Update() override;

	// ゲーム選択シーンの終了処理
	virtual void Finalize() override;

private:

	/**
	* 選択
	*/
	enum class Choice
	{
		// 戦闘
		Battle,

		// オプション
		Option,

		// ゲーム終了
		Exit,
	};

	Choice choice = Choice::Battle;
	int choiceNum = 0;

	Color highlightedColor = Color{ 1.3f, 1.3f, 1.3f , 1};		// 選択色
	Color pressedColor = Color{ 0.7f, 0.7f, 0.7f , 1};		// 押下色

	// ボタン配列
	std::vector<UI::ImagePtr> imgButtons;
};


#endif // !GAMECHOICESCENE_H_INCLUDED
