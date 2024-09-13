/**
* @file BattleSettingScene.h
*/
#ifndef BATTLESETTINGSCENE_H_INCLUDED
#define BATTLESETTINGSCENE_H_INCLUDED
#include "FGEngine/Scene/Scene.h"
using namespace FGEngine;

/**
* バトル設定シーン
*/
class BattleSettingScene : public Scene
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	BattleSettingScene() = default;

private:

	/**
	* バトル設定シーンの初期化
	*
	* @return true  初期化成功
	* @return false 初期化失敗
	*/
	virtual bool Initialize() override;
};

#endif // !BATTLESETTINGSCENE_H_INCLUDED
