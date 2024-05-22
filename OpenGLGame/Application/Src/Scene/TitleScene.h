/**
* @file TitleScene,h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine::SceneSystem;

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
};
#endif // !TITLESCENE_H_INCLUDED
