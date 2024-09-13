/**
* @file SelectScene.h
*/
#ifndef SELECTSCENE_H_INCLUDED
#define SELECTSCENE_H_INCLUDED
#include "FGEngine/Scene/Scene.h"
using namespace FGEngine;

/**
* ゲーム選択シーン
*/
class SelectScene : public Scene
{
public:
	
	/**
	* デフォルトコンストラクタ
	*/
	SelectScene() = default;

private:

	/**
	* ゲーム選択シーンの初期化
	*
	* @return true  初期化成功
	* @return false 初期化失敗
	*/
	virtual bool Initialize() override;
};

#endif // !SELECTSCENE_H_INCLUDED
