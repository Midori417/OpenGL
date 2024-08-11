/**
* @file TestScene,h
*/
#ifndef TESTSCENE_H_INCLUDED
#define TESTSCENE_H_INCLUDED
#include "../FGEngine.h"
using namespace FGEngine::SceneSystem;

/**
* テストシーン「
*/
class TestScene : public Scene
{
public:

	// コンストラクタ
	TestScene() = default;

	// デストラクタ
	virtual ~TestScene() = default;

private:

	// タイトルシーンの初期化
	virtual bool Initialize() override;
};
#endif // !TITLESCENE_H_INCLUDED
