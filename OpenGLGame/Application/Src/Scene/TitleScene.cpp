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
* �^�C�g���V�[���̏�����
*/
bool TitleScene::Initialize()
{
	auto resManager = AssetManager::GetInstance();

	// �J�������쐬
	GameObjectPtr camera = Create(CreateObject::Camera);

	// �^�C�g���}�l�[�W�����쐬
	GameObjectPtr titleManagerObject = Create(CreateObject::Empty);
	titleManagerObject->name = "TitleManager";
	auto titleManager = titleManagerObject->AddComponent<TitleManager>();

	// �^�C�g���w�i���쐬
	{
		GameObjectPtr titleBack = Create(CreateObject::Empty);
		titleBack->name = "TitleBack";
		auto image = titleBack->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleBack");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}
	// �K���_�����쐬
	{
		GameObjectPtr titleGundam = Create(CreateObject::Empty);
		titleGundam->name = "TitleGundam";
		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}
	// �K���_���̊���쐬
	{
		GameObjectPtr gundamEye = Create(CreateObject::Empty);
		gundamEye->name = "GundamEye";

		auto image = gundamEye->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundamEye");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();

		// �_�ł��������̂ŉ摜�_�ŃR���|�[�l���g��ǉ�
		auto eyeBlinking = gundamEye->AddComponent<ImageBlinking>();
		eyeBlinking->image = image;
		eyeBlinking->speed = 0.5f;
	}

	// PleaseButton���쐬
	{
		GameObjectPtr pleauseButton = Create(CreateObject::Empty);
		pleauseButton->name = "PleaseButton";
		pleauseButton->GetTransform()->position = Vector3(-50, 350, 0);

		auto image = pleauseButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("PleaseButton");
		image->size = image->texture->GetSize() * 1.5f;

		// �_�ł��������̂ŉ摜�_�ŃR���|�[�l���g��ǉ�
		auto imgBlinking = pleauseButton->AddComponent<ImageBlinking>();
		imgBlinking->image = image;
		imgBlinking->speed = 1;
	}

	// �^�C�g�����S���쐬
	{
		GameObjectPtr titleLogo = Create(CreateObject::Empty);
		titleLogo->name = "TitleLogo";

		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 1.3f;
	}

	return true;
}