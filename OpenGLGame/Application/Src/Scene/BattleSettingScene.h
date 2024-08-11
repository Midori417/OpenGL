/**
* @file BattleSettingScene.h
*/
#ifndef BATTLESETTINGSCENE_H_INCLUDED
#define BATTLESETTINGSCENE_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine::SceneSystem;

/**
* バトル設定シーン
*/
class BattleSettingScene : public Scene
{
public:

	// コンストラクタ・デストラクタ
	BattleSettingScene() = default;
	virtual ~BattleSettingScene() = default;

private:

	/**
	* バトル設定シーンの初期化
	*/
	virtual bool Initialize() override;
};


#endif // !GAMESETTINGSCENE_H_INCLUDED
