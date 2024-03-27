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
bool TitleScene::Initialize()
{

	return true;
}

/**
* タイトルシーンの更新
* 
* @param engine		エンジン
* @param deltaTime	前回の更新からの経過時間
*/
void TitleScene::Update()
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
void TitleScene::Finalize()
{
}
