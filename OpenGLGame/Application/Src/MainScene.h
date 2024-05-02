/**
* @file MainScene.h
*/
#ifndef MAINSCENE_H_INCLUDED
#define MAINSCENE_H_INCLUDED

#include "FGEngineSub.h"
using namespace FGEngine;

/**
* メインシーン
*/
class MainScene : public FGEngine::SceneSystem::Scene
{
public:

	// コンストラクタ
	MainScene() = default;

	// デストラクタ
	virtual ~MainScene() = default;

private:

	// メインシーンの初期化
	virtual bool Initialize() override;

	// メインシーンの更新
	virtual void Update() override;

	// メインシーンの終了処理
	virtual void Finalize() override;

};
#endif // !MAINSCENE_H_INCLUDED