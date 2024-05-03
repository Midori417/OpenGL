/**
* @file Application.cpp
*/
#include "Application.h"
#include "TitleScene.h"
#include "MainScene.h"
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
	auto resouceManager = ResouceManager::GetInstance();

	// ���\�[�X�̓ǂݍ���
	resouceManager->LoadGlTF("Gundam", "Application/Res/Gundam/Model/GundamGL.gltf");

	resouceManager->LoadTga("sky", "Application/Res/Map/sky2.tga");
	resouceManager->LoadTga("BoostbarBack", "Application/Res/UI/Battle/BoostbarBack.tga");
	resouceManager->LoadTga("Title", "Application/Res/UI/Title/Title.tga");

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
