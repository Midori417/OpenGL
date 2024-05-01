/**
* @file TitleScene,h
*/
#ifndef TITLESCENE_H_INCLUDED
#define TITLESCENE_H_INCLUDED

#include "MyEngine.h"

/**
* タイトルシーン
*/
class TitleScene : public SceneManagment::Scene
{
public:

	// コンストラクタ
	TitleScene() = default;

	// デストラクタ
	virtual ~TitleScene() = default;

private:

	// タイトルシーンの初期化
	virtual bool Initialize(Engine& engine) override;

	// タイトルシーンの更新
	virtual void Update(Engine& engine) override;

	// タイトルシーンの終了
	virtual void Finalize(Engine& engine) override;

private:

};
#endif // !TITLESCENE_H_INCLUDED
