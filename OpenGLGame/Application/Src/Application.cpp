/**
* @file Application.cpp
*/
#include "Application.h"
using namespace FGEngine;
using namespace FGEngine::SceneSystem;

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
	// �G���W�����擾
	auto engine = Engine::GetInstance();

	// OBJ�t�@�C����ǂݍ���
	engine->LoadObj("Application/Res/Gundam/Model/MagunamBullet.obj");
	engine->LoadObj("Application/Res/Map/Load.obj");
	engine->LoadObj("Application/Res/Map/Biru01.obj");
	engine->LoadObj("Application/Res/Map/Biru02.obj");
	engine->LoadObj("Application/Res/Map/Biru03.obj");

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
