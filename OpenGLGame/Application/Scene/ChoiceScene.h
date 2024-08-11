/**
* @file ChoiceScene.h
*/
#ifndef CHOICESCENE_H_INCLUDED
#define CHOICESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine::SceneSystem;

/**
* ゲーム選択シーン
*/
class ChoiceScene : public Scene
{
public:

	// コンストラクタ・デストラクタ
	ChoiceScene() = default;
	virtual ~ChoiceScene() = default;

private:

	/**
	* ゲーム選択シーンの初期化
	*/
	virtual bool Initialize() override;
};


#endif // !GAMECHOICESCENE_H_INCLUDED
