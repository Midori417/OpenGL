/**
* @file BattleMap01Scene.h
*/
#ifndef BATTLEMAP01SCENE_H_INCLUDED
#define BATTLEMAP01SCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* 戦闘シーンの初期化
*
* @return true  初期化成功
* @return false 初期化失敗
*/
class BattleMap01Scene : public Scene
{
public:

	// コンストラクタ
	BattleMap01Scene() = default;

	// デストラクタ
	virtual ~BattleMap01Scene() = default;

private:

	// 戦闘シーンの初期化
	virtual bool Initialize() override;

private:

	// マップの大きさ
	Vector2 mapSize = Vector2(150, 180);

	// リソースの読み込み
	static bool isResouceLoad;
};
#endif // !MAINSCENE_H_INCLUDED