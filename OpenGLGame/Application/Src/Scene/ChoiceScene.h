/**
* @file ChoiceScene.h
*/
#ifndef CHOICESCENE_H_INCLUDED
#define CHOICESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* ゲーム選択シーン
*/
class ChoiceScene : public Scene
{
public:

	// コンストラクタ
	ChoiceScene() = default;

	// デストラクタ
	virtual ~ChoiceScene() = default;

private:

	// ゲーム選択シーンの初期化
	virtual bool Initialize() override;

	// ゲーム選択シーンの更新
	virtual void Update() override;

	// ゲーム選択シーンの終了処理
	virtual void Finalize() override;
};


#endif // !GAMECHOICESCENE_H_INCLUDED
