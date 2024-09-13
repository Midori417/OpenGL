/**
* @file BattleMap01Scene,h
*/
#ifndef BATTLEMAP01SCENE_H_INCLUDED
#define BATTLEMAP01SCENE_H_INCLUDED
#include "FGEngine/Scene/Scene.h"
using namespace FGEngine;

/**
* バトルマップ01シーン
*/
class BattleMap01Scene : public Scene
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	BattleMap01Scene() = default;

private:

	/**
	* バトルマップ01シーンの初期化
	*
	* @return true  初期化成功
	* @return false 初期化失敗
	*/
	virtual bool Initialize() override;
};


#endif // !BATTLEMAP01SCENE_H_INCLUDED
