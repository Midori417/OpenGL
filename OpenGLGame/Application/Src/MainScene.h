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
	virtual bool Initialize(Engine& engine) override;

	// メインシーンの更新
	virtual void Update(Engine& engine) override;

	// メインシーンの終了処理
	virtual void Finalize(Engine& engine) override;

private:

	GltfAnimatedMeshRendererPtr animTestRenderer;

};
#endif // !MAINSCENE_H_INCLUDED