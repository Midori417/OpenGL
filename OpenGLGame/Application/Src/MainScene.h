/**
* @file MainScene.h
*/
#ifndef MAINSCENE_H_INCLUDED
#define MAINSCENE_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

/**
* メインシーン
*/
class MainScene : public Scene
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