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

	// カメラの作成
	auto camera = CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
	auto cameraInfo = camera->AddComponent<Camera>();
	SetMainCameraInfo(cameraInfo);

	// タイトルマネージャを作成
	auto titleManagerObj = CreateGameObject("TitleManager");
	auto titleManager = titleManagerObj->AddComponent<TitleManager>();

	// タイトル背景を作成
	{
		auto titleBack = CreateGameObject("TitleBack");
		auto image = titleBack->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleBack");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}
	// ガンダムを作成
	{
		auto titleGundam = CreateGameObject("TitleGundam");
		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}
	// ガンダムの眼を作成
	{
		auto gundamEye = CreateGameObject("GundamEye");
		auto image =gundamEye->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundamEye");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
		auto eyeBlinking = gundamEye->AddComponent<ImageBlinking>();
		eyeBlinking->image = image;
		eyeBlinking->speed = 0.5f;
	}

	// PleaseButtonを作成
	{
		auto pleauseButton = CreateGameObject("PleaseButton", Vector3(-50, 350, 0), Quaternion::identity);
		auto image = pleauseButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("PleaseButton");
		image->size = image->texture->GetSize() * 1.5f;
		auto imgBlinking = pleauseButton->AddComponent<ImageBlinking>();
		imgBlinking->image = image;
		imgBlinking->speed = 1;
	}

	// タイトルロゴを作成
	{
		auto titleLogo = CreateGameObject("TitleLogo");
		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 1.3f;
	}

	return true;
}