/**
* @file Application.cpp
*/
#include "Application.h"
#include "Scene/TitleScene.h"
#include "Scene/MainScene.h"
#include "Scene/GameChoiceScene.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;
using namespace FGEngine::ResouceSystem;

/**
* �A�v���P�[�V�����̏�����
*
* @return 0		����ɏI��
* @return 0�ȊO �������Ɏ��s
*/
int Application::Initialize()
{
	auto resManager = ResouceManager::GetInstance();

	// ���\�[�X�̓ǂݍ���
	resManager->LoadTga("TitleBack", "Application/Res/UI/Title/TitleBack.tga");
	resManager->LoadTga("TitleGundam", "Application/Res/UI/Title/TitleGundam.tga");
	resManager->LoadTga("TitleGundamEye", "Application/Res/UI/Title/GundamEye.tga");
	resManager->LoadTga("TitleLogo", "Application/Res/UI/Title/TitleLogo.tga");
	resManager->LoadTga("TitleLogoWhite", "Application/Res/UI/Title/TitleLogoWhite.tga");
	resManager->LoadTga("sky", "Application/Res/Map/sky2.tga");
	resManager->LoadTga("PleaseButton", "Application/Res/UI/Title/PleaseButton.tga");

	// �V�[���̓o�^
	SceneManager::AddScene<TitleScene>("�^�C�g���V�[��");
	SceneManager::AddScene<GameChiecScene>("�Q�[���I���V�[��");
	SceneManager::AddScene<MainScene>("���C���V�[��");

	return 0;
}

/**
* �A�v���P�[�V�����̍X�V
*/
void Application::Update()
{
}

/**
* �A�v���P�[�V�����̏I��
*/
void Application::Fainalize()
{
}
