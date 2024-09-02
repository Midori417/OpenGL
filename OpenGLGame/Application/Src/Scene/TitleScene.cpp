/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
#include "../ImageBlinking.h"
#include "../FadeOut.h"
#include "../TitleManager.h"
using namespace FGEngine::InputSystem;
using namespace FGEngine::UI;

/**
* タイトルシーンの初期化
*/
bool TitleScene::Initialize()
{
	auto resManager = AssetManager::GetInstance();

	// カメラを作成
	GameObjectPtr camera = Create(CreateObject::Camera);

	// タイトルマネージャを作成
	GameObjectPtr titleManagerObject = Create(CreateObject::Empty);
	titleManagerObject->name = "TitleManager";
	auto titleManager = titleManagerObject->AddComponent<TitleManager>();

	// タイトル背景を作成
	{
		GameObjectPtr titleBack = Create(CreateObject::Empty);
		titleBack->name = "TitleBack";
		auto image = titleBack->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleBack");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}
	// ガンダムを作成
	{
		GameObjectPtr titleGundam = Create(CreateObject::Empty);
		titleGundam->name = "TitleGundam";
		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}
	// ガンダムの眼を作成
	{
		GameObjectPtr gundamEye = Create(CreateObject::Empty);
		gundamEye->name = "GundamEye";

		auto image = gundamEye->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundamEye");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();

		// 点滅させたいので画像点滅コンポーネントを追加
		auto eyeBlinking = gundamEye->AddComponent<ImageBlinking>();
		eyeBlinking->image = image;
		eyeBlinking->speed = 0.5f;
	}

	// PleaseButtonを作成
	{
		GameObjectPtr pleauseButton = Create(CreateObject::Empty);
		pleauseButton->name = "PleaseButton";
		pleauseButton->GetTransform()->position = Vector3(-50, 350, 0);

		auto image = pleauseButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("PleaseButton");
		image->size = image->texture->GetSize() * 1.5f;

		// 点滅させたいので画像点滅コンポーネントを追加
		auto imgBlinking = pleauseButton->AddComponent<ImageBlinking>();
		imgBlinking->image = image;
		imgBlinking->speed = 1;
	}

	// タイトルロゴを作成
	{
		GameObjectPtr titleLogo = Create(CreateObject::Empty);
		titleLogo->name = "TitleLogo";

		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 1.3f;
	}

	return true;
}