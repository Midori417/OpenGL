/**
* @file TitleScene.h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED
#include "FGEngine/Scene/Scene.h"
using namespace FGEngine;

/**
* タイトルシーン
*/
class TitleScene : public FGEngine::Scene
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	TitleScene() = default;

private:

	/**
	* タイトルシーンの初期化
	*
	* @return true  初期化成功
	* @return false 初期化失敗
	*/
	virtual bool Initialize() override;
};

#endif // !FGENGINE_TITLESCENE_H_INCLUDED
