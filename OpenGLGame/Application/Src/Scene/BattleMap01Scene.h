/**
* @file BattleMap01Scene.h
*/
#ifndef BATTLEMAP01SCENE_H_INCLUDED
#define BATTLEMAP01SCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* 戦闘シーン
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

	// 戦闘シーンの更新
	virtual void Update() override;

	// 戦闘シーンの終了処理
	virtual void Finalize() override;

public:

	// マップの大きさ横
	float mapX = 0;

	// マップの大きさ縦
	float mapZ = 0;

};
#endif // !MAINSCENE_H_INCLUDED