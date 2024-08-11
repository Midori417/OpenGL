/**
* @file ChoiceScene.cpp
*/
#include "ChoiceScene.h"
#include "../ChoiceManager.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::WindowSystem;
using namespace FGEngine::UI;

/**
* �Q�[���I���V�[���̏�����
*/
bool ChoiceScene::Initialize()
{
	// �}�l�[�W���[���擾
	auto objManager = ObjectManager::GetInstance();
	auto resManager = ResouceManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// �J�����̍쐬
	auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);

	// �I���V�[���Ǘ��}�l�[�W���[���쐬
	auto choiceManagerObj = objManager->CreateGameObject("ChoiceManager");
	auto choiceManager = choiceManagerObj->AddComponent<ChoiceManager>();

	// �^�C�g���w�i���쐬
	{
		auto titleBack = objManager->CreateGameObject("TitleBack");
		auto image = titleBack->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleBack");
		image->size = winManager->GetWindowSize();
	}

	// �K���_�����쐬
	{
		auto titleGundam = objManager->CreateGameObject("TitleGundam");
		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = winManager->GetWindowSize();
	}

	// �u���b�N�I�u�W�F�N�g���쐬
	{
		auto blackObject = objManager->CreateGameObject("BlackObject");
		auto image = blackObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color(0, 0, 0, 0.7f);
		image->size = winManager->GetWindowSize();
	}

	// �^�C�g�����S���쐬
	{
		auto titleLogo = objManager->CreateGameObject("TitleLogoA", Vector3(400, 0, 0));
		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 0.9f;
	}

	return false;
}
