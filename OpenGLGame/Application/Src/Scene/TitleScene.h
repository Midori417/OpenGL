/**
* @file TitleScene,h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* タイトルシーン
*/
class TitleScene : public Scene
{
public:

	// コンストラクタ
	TitleScene() = default;

	// デストラクタ
	virtual ~TitleScene() = default;

private:

	// タイトルシーンの初期化
	virtual bool Initialize() override;

	// タイトルシーンの更新
	virtual void Update() override;

	// タイトルシーンの終了
	virtual void Finalize() override;

private:

	// フェードコンポーネント
	FadeOutPtr fadeOut;

	// ボタンが押されたら
	bool isStart = false;

};
#endif // !TITLESCENE_H_INCLUDED
