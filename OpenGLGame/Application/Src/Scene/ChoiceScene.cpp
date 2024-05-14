/**
* @file ChoiceScene.cpp
*/
#include "ChoiceScene.h"
#include "../ChoiceManager.h"
#include "../FadeOut.h"
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
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}

	// �K���_�����쐬
	{
		auto titleGundam = objManager->CreateGameObject("TitleGundam");
		auto image = titleGundam->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundam");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}

	// �u���b�N�I�u�W�F�N�g���쐬
	{
		auto blackObject = objManager->CreateGameObject("BlackObject");
		auto image = blackObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color(0, 0, 0, 0.7f);
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
	}

	// �^�C�g�����S���쐬
	{
		auto titleLogo = objManager->CreateGameObject("TitleLogoA", Vector3(-400, 0, 0));
		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 0.9f;
	}

	// �o�g���{�^�����쐬
	{
		auto battleButton = objManager->CreateGameObject("BattleButton", Vector3(500, -200, 0));
		auto image = battleButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("BattleButton");
		image->size = image->texture->GetSize() * 1.3f;
		choiceManager->imgButtons.push_back(image);
	}

	// �I�v�V�����{�^�����쐬
	{
		auto optionButton = objManager->CreateGameObject("OptionButton", Vector3(500, 0, 0));
		auto image = optionButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("OptionButton");
		image->size = image->texture->GetSize() * 1.3f;
		choiceManager->imgButtons.push_back(image);
	}

	// ��߂�{�^�����쐬
	{
		auto exitButton = objManager->CreateGameObject("ExitButton", Vector3(500, 200, 0));
		auto image = exitButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("ExitButton");
		image->size = image->texture->GetSize() * 1.3f;
		choiceManager->imgButtons.push_back(image);
	}

	// �t�F�[�h�I�u�W�F�N�g���쐬
	{
		auto fadeObject = objManager->CreateGameObject("FadeObjectA");
		auto image = fadeObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color::black;
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
		choiceManager->fadeOut = fadeObject->AddComponent<FadeOut>();
	}

	return false;
}

/**
* �Q�[���I���V�[���̍X�V
*/
void ChoiceScene::Update()
{
}

/**
* �Q�[���I���V�[���̏I��
*/
void ChoiceScene::Finalize()
{
}
