/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
#include "../ImageBlinking.h"
#include "../FadeOut.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;
using namespace FGEngine::UI;

/**
* �^�C�g���V�[���̏�����
*
* @param engine �G���W��
*/
bool TitleScene::Initialize()
{
	auto objManager = ObjectManager::GetInstance();
	auto resManager = ResouceManager::GetInstance();

	// �J�����̍쐬
	auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -10));
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);

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
	// �K���_���̊���쐬
	{
		auto gundamEye = objManager->CreateGameObject("GundamEye");
		auto image =gundamEye->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleGundamEye");
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
		auto eyeBlinking = gundamEye->AddComponent<ImageBlinking>();
		eyeBlinking->image = image;
	}

	// PleaseButton���쐬
	{
		auto pleauseButton = objManager->CreateGameObject("PleaseButton", Vector3(-50, 350, 0));
		auto image = pleauseButton->AddComponent<Image>();
		image->texture = resManager->GetTexture("PleaseButton");
		image->size = image->texture->GetSize() * 1.5f;
		auto imgBlinking = pleauseButton->AddComponent<ImageBlinking>();
		imgBlinking->image = image;
		imgBlinking->speed = 1;
	}

	// �^�C�g�����S���쐬
	{
		auto titleLogo = objManager->CreateGameObject("TitleLogo");
		auto image = titleLogo->AddComponent<Image>();
		image->texture = resManager->GetTexture("TitleLogo");
		image->size = Vector2(937, 383) * 1.3f;
	}

	// �t�F�[�h�I�u�W�F�N�g���쐬
	{
		auto fadeObject = objManager->CreateGameObject("FadeObject");
		auto image = fadeObject->AddComponent<Image>();
		image->texture = resManager->GetTexture("white");
		image->color = Color::black;
		image->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();
		fadeOut = fadeObject->AddComponent<FadeOut>();
	}
	return true;
}

/**
* �^�C�g���V�[���̍X�V
*
* @param engine		�G���W��
* @param deltaTime	�O��̍X�V����̌o�ߎ���
*/
void TitleScene::Update()
{
	if (InputKey::AnyKey() && !isStart)
	{
		fadeOut->isStart = true;
		isStart = true;
	}
	// �t�F�[�h���I��������V�[���ړ�
	if (fadeOut->IsFadeOut())
	{
		SceneManager::LoadScene("�Q�[���I���V�[��");
	}
}

/**
* �^�C�g���V�[���̏I��
*
* @param engine �G���W��
*/
void TitleScene::Finalize()
{
}
