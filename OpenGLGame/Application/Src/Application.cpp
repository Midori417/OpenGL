/**
* @file Application.cpp
*/
#include "Application.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;
using namespace FGEngine::ResouceSystem;

#include "TitleScene.h"
#include "MainScene.h"

/**
* �A�v���P�[�V�����̏�����
*
* @return 0		����ɏI��
* @return 0�ȊO �������Ɏ��s
*/
int Application::Initialize()
{
	auto resouceManager = ResouceManager::GetInstance();
	// OBJ�t�@�C����ǂݍ���

	// �摜�ǂݍ���
	resouceManager->LoadTga("sky", "Application/Res/Map/sky2.tga");

	// �V�[���̓o�^
	SceneManager::AddScene<TitleScene>("�^�C�g���V�[��");
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
