/**
* @file Application.cpp
*/
#include "Application.h"
#include "Scene/TitleScene.h"
#include "Scene/BattleMap01Scene.h"
#include "Scene/BattleSettingScene.h"
#include "Scene/ChoiceScene.h"
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
	for (int i = 0; i < 10; i++)
	{
		std::string num = "Num" + std::to_string(i);
		resManager->LoadTga(num, "Application/Res/UI/Num/" + num + ".tga");
	}
	resManager->LoadTga("TitleBack", "Application/Res/UI/Title/TitleBack.tga");
	resManager->LoadTga("TitleGundam", "Application/Res/UI/Title/TitleGundam.tga");
	resManager->LoadTga("TitleGundamEye", "Application/Res/UI/Title/GundamEye.tga");
	resManager->LoadTga("TitleLogo", "Application/Res/UI/Title/TitleLogo.tga");
	resManager->LoadTga("TitleLogoWhite", "Application/Res/UI/Title/TitleLogoWhite.tga");
	resManager->LoadTga("Sky", "Application/Res/Map/sky2.tga");
	resManager->LoadTga("PleaseButton", "Application/Res/UI/Title/PleaseButton.tga");
	resManager->LoadTga("BattleButton", "Application/Res/UI/Title/BattleButton.tga");
	resManager->LoadTga("OptionButton", "Application/Res/UI/Title/OptionButton.tga");
	resManager->LoadTga("ExitButton", "Application/Res/UI/Title/ExitButton.tga");
	resManager->LoadTga("BattleSetting", "Application/Res/UI/BattleSetting/BattleSetting.tga");
	resManager->LoadTga("BoostBar", "Application/Res/UI/Battle/Boostbar.tga");
	resManager->LoadTga("BoostBarBack", "Application/Res/UI/Battle/BoostbarBack.tga");
	resManager->LoadTga("BoostBarOVERHEAT", "Application/Res/UI/Battle/BoostbarOverHeat.tga");
	resManager->LoadTga("BurstBar", "Application/Res/UI/Battle/BurstBar.tga");
	resManager->LoadTga("BurstBarBack", "Application/Res/UI/Battle/BurstBarBack.tga");
	resManager->LoadTga("GO", "Application/Res/UI/Battle/Go.tga");
	resManager->LoadTga("GoBack", "Application/Res/UI/Battle/GoBack.tga");
	resManager->LoadTga("PlayerInfo", "Application/Res/UI/Battle/PlayerInfo.tga");
	resManager->LoadTga("STANDBAY", "Application/Res/UI/Battle/Standbay.tga");
	resManager->LoadTga("TargetMark01", "Application/Res/UI/Battle/TargetMark01.tga");
	resManager->LoadTga("TargetMark02", "Application/Res/UI/Battle/TargetMark02.tga");
	resManager->LoadTga("TargetMark03", "Application/Res/UI/Battle/TargetMark03.tga");
	resManager->LoadTga("TargetMsInfo", "Application/Res/UI/Battle/TargetMsInfo.tga");
	resManager->LoadTga("TargetMsHpBar", "Application/Res/UI/Battle/TargetMsHpBar.tga");
	resManager->LoadTga("Timer", "Application/Res/UI/Battle/Timer.tga");
	resManager->LoadTga("TeumFrame", "Application/Res/UI/Battle/TeumFrame.tga");
	resManager->LoadTga("TeumHpBar", "Application/Res/UI/Battle/TeumHpBar.tga");
	resManager->LoadTga("TeumEnemyHpBar", "Application/Res/UI/Battle/TeumEnemyBar.tga");
	resManager->LoadTga("WeaponBack", "Application/Res/UI/Battle/WeaponBack.tga");
	resManager->LoadTga("WeaponBar", "Application/Res/UI/Battle/WeaponBar.tga");
	resManager->LoadTga("Win", "Application/Res/UI/Battle/Win.tga");
	resManager->LoadTga("Lose", "Application/Res/UI/Battle/Lose.tga");

	// MS�̓ǂݍ���
	resManager->LoadGlTF("Gundam", "Application/Res/Ms/Gundam/Model/Gundam.gltf");


	// �V�[���̓o�^
	SceneManager::AddScene<TitleScene>("�^�C�g���V�[��");
	SceneManager::AddScene<ChoiceScene>("�Q�[���I���V�[��");
	SceneManager::AddScene<BattleSettingScene>("�o�g���ݒ�V�[��");
	SceneManager::AddScene<BattleMap01Scene>("�o�g���}�b�v01�V�[��");

	// �ŏ��ɗ����V�[��
	//SceneManager::LoadScene("�^�C�g���V�[��");
	SceneManager::LoadScene("�o�g���ݒ�V�[��");

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
