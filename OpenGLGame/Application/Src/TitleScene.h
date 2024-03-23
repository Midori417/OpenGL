/**
* @file TitleScene,h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED

#include "FGEngineSub.h"
using namespace FGEngine;

/**
* タイトルシーン
*/
class TitleScene : public FGEngine::SceneSystem::Scene
{
public:

	// コンストラクタ
	TitleScene() = default;

	// デストラクタ
	virtual ~TitleScene() = default;

private:

	// タイトルシーンの初期化
	virtual bool Initialize(FGEngine::Engine& engine) override;

	// タイトルシーンの更新
	virtual void Update(FGEngine::Engine& engine) override;

	// タイトルシーンの終了
	virtual void Finalize(FGEngine::Engine& engine) override;

private:

};
#endif // !TITLESCENE_H_INCLUDED
