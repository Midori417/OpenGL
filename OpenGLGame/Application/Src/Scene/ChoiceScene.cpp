/**
* @file ChoiceScene.cpp
*/
#include "ChoiceScene.h"
#include "../ChoiceManager.h"
using namespace FGEngine::WindowSystem;
using namespace FGEngine::UI;

/**
* �Q�[���I���V�[���̏�����
*/
bool ChoiceScene::Initialize()
{
	// �}�l�[�W���[���擾
	auto resManager = AssetManager::GetInstance();
	auto winManager = WindowManager::GetInstance();

	// �J�������쐬
	GameObjectPtr camer = Create(CreateObject::Camera);

	// �I���V�[���Ǘ��}�l�[�W���[���쐬
	GameObjectPtr choiceManagerObject = Create(CreateObject::Empty);
	choiceManagerObject->name = "ChoiceManager";
	auto choiceManager = choiceManagerObject->AddComponent<ChoiceManager>();

	// �^�C�g���w�i���쐬
	{
		GameObjectPtr titleBack = Create(CreateObject::Empty);
		titleBack->name = "TitleBack";

		auto image = titleBack->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleBack");
		image->size = winManager->GetWindowSize();
	}

	// �K���_�����쐬
	{
		GameObjectPtr titleGundam = Create(CreateObject::Empty);
		titleGundam->name = "TitleGundam";

		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = winManager->GetWindowSize();
	}

	// �w�i�������Â��������̂Ŕ��������I�u�W�F�N�g��ݒu
	{
		GameObjectPtr blackObject = Create(CreateObject::Empty);
		blackObject->name = "BlackObject";

		auto image = blackObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color(0, 0, 0, 0.7f);
		image->size = winManager->GetWindowSize();
	}

	// �^�C�g�����S���쐬
	{
		GameObjectPtr titleLogo = Create(CreateObject::Empty);
		titleLogo->name = "TitleLogoA";
		titleLogo->GetTransform()->position.x = 400;

		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 0.9f;
	}

	return false;
}
