/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
using namespace FGEngine::SceneSystem;

/**
* タイトルシーンの初期化
* 
* @param engine エンジン
*/
bool TitleScene::Initialize(FGEngine::Engine& engine)
{
	engine.CreateCameraObject("camera");
	auto title = engine.Create<GameObject>("Title");
	{
		auto image = title->AddComponent<Image>();
		image->filename = "Application/Res/UI/Title/Title.tga";
		image->size = engine.GetFramebufferSize();
	}
	auto pos = engine.GetFramebufferSize() / 2;
	auto titleLogo = engine.Create<GameObject>("TitleLogo", Vector3(pos.x - 1000 /2, pos.y - 400 / 2, 0));
	{ 
		auto image = titleLogo->AddComponent<Image>();
		image->filename = "Application/Res/UI/Title/TitleLogo.tga";
		image->size = Vector2(1000, 400);
	}

	return true;
}

/**
* タイトルシーンの更新
* 
* @param engine		エンジン
* @param deltaTime	前回の更新からの経過時間
*/
void TitleScene::Update(FGEngine::Engine& engine)
{
	if (Input::GetKeyDown(KeyCode::Enter))
	{
		SceneManager::LoadScene("メインシーン");
	}
}

/**
* タイトルシーンの終了
* 
* @param engine エンジン
*/
void TitleScene::Finalize(FGEngine::Engine& engine)
{
	engine.AllClearGameObject();
}
