/**
* @file Application.cpp
*/
#include "Application.h"

#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Scene/SceneManager.h"
using namespace FGEngine;

#include "Scene/TitleScene.h"
#include "Scene/SelectScene.h"
#include "Scene/BattleSettingScene.h"

#include "Scene/BattleMap01Scene.h"

/**
* �A�v���P�[�V�����̏�����
*
* @return 0		����ɏI��
* @return 0�ȊO �������Ɏ��s
*/
int Application::Initialize()
{
	auto assetManager = AssetManager::GetInstance();

	// ���\�[�X�̓ǂݍ���
	for (int i = 0; i < 10; i++)
	{
		std::string num = "Num" + std::to_string(i);
		assetManager->LoadTga(num, "Application/Res/UI/Num/" + num + ".tga");
	}

	// �^�C�g��
	{
		assetManager->LoadTga("TitleBackGround",	"Application/Res/UI/TitleBackGround.tga");
		assetManager->LoadTga("TitleGundamEye",		"Application/Res/UI/GundamEye.tga");
		assetManager->LoadTga("PleaseButton",		"Application/Res/UI/PleaseButton.tga");
	}
	// �I��
	{
		assetManager->LoadTga("SelectBackGround",	"Application/Res/UI/SelectBackGround.tga");
		assetManager->LoadTga("BattleButton",		"Application/Res/UI/SelectButton/BattleButton.tga");
		assetManager->LoadTga("ExitButton",			"Application/Res/UI/SelectButton/ExitButton.tga");
	}
	// �o�g���ݒ�
	{
		assetManager->LoadTga("BattleSettingBackGround", "Application/Res/UI/BattleSettingBackGround.tga");
	}
	// �o�g��
	{
		assetManager->LoadTga("Standbay",	"Application/Res/UI/Battle/Standbay.tga");
		assetManager->LoadTga("Go",			"Application/Res/UI/Battle/Go.tga");

		assetManager->LoadTga("BoostBar",			"Application/Res/UI/Battle/BoostBar.tga");
		assetManager->LoadTga("BoostBarBack",		"Application/Res/UI/Battle/BoostBarBack.tga");
		assetManager->LoadTga("BoostBarOVERHEAT",	"Application/Res/UI/Battle/BoostBarOverHeat.tga");

		assetManager->LoadTga("PlayerInfo", "Application/Res/UI/Battle/PlayerInfo.tga");


		assetManager->LoadTga("OtherTeumMsInfo", "Application/Res/UI/Battle/TargetMsInfo.tga");
		assetManager->LoadTga("OtherTeumMsHpBar", "Application/Res/UI/Battle/TargetMsHpBar.tga");

		assetManager->LoadTga("TargetMarkGreen", "Application/Res/UI/Battle/TargetMark/TargetMarkGreen.tga");
		assetManager->LoadTga("TargetMarkRed", "Application/Res/UI/Battle/TargetMark/TargetMarkRed.tga");
		assetManager->LoadTga("TargetMarkLock", "Application/Res/UI/Battle/TargetMark/TargetMarkLock.tga");
		assetManager->LoadTga("TargetMarkYellow", "Application/Res/UI/Battle/TargetMark/TargetMarkYellow.tga");

		assetManager->LoadTga("MyTeumOtherMsInfo", "Application/Res/UI/Battle/TeumOtherMsInfo.tga");
		assetManager->LoadTga("MyTeumOtherMsHpBar", "Application/Res/UI/Battle/TeumOtherMsHpBar.tga");
		assetManager->LoadTga("PartnerHpBack", "Application/Res/UI/Battle/PartnerHpBack.tga");

		assetManager->LoadTga("WeaponBack", "Application/Res/UI/Battle/WeaponBack.tga");
		assetManager->LoadTga("WeaponBar", "Application/Res/UI/Battle/WeaponBar.tga");

		assetManager->LoadTga("TeamHpFrame",	"Application/Res/UI/Battle/TeamHpFrame.tga");
		assetManager->LoadTga("MyTeamHpBar",	"Application/Res/UI/Battle/MyTeamHpBar.tga");
		assetManager->LoadTga("OtherTeamHpBar", "Application/Res/UI/Battle/OtherTeamHpBar.tga");

		assetManager->LoadTga("Win", "Application/Res/UI/Battle/Win.tga");
		assetManager->LoadTga("Lose", "Application/Res/UI/Battle/Lose.tga");
	}
	// �o�g���}�b�v01
	{
		assetManager->LoadTga("SkyBox",			"Application/Res/Map/skyBox.tga");
		assetManager->LoadGlTF("Map01/Ground",	"Application/Res/Map/Map01/Ground.gltf");
	}
	// MS
	{
		// �K���_��
		{
			assetManager->LoadGlTF("Gundam", "Application/Res/Ms/Gundam/Model/Gundam.gltf");
			assetManager->LoadObj("Gundam/BeumRifleBullet", "Application/Res/Ms/Gundam/Model/BeumRifleBullet.obj");
			assetManager->LoadTga("Gundam/BeumRifleIcon", "Application/Res/Ms/Gundam/UI/BeumRifleIcon.tga");
			assetManager->LoadObj("Gundam/BazookaBullet", "Application/Res/Ms/Gundam/Model/BazookaBullet.obj");
			assetManager->LoadTga("Gundam/BazookaIcon", "Application/Res/Ms/Gundam/UI/BazookaIcon.tga");
		}
	}

	// �V�[���̓o�^
	SceneManager::AddScene<TitleScene>("TitleScene");
	SceneManager::AddScene<SelectScene>("SelectScene");
	SceneManager::AddScene<BattleSettingScene>("BattleSettingScene");
	SceneManager::AddScene<BattleMap01Scene>("BattleMap01Scene");

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
