/**
* @file Application.cpp
*/
#include "Application.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/CreateGameObjectType.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Scene/SceneManager.h"
using namespace FGEngine;

#include "Scene/TitleScene.h"
#include "Scene/SelectScene.h"
#include "Scene/BattleSettingScene.h"
#include "Scene/BattleMap01Scene.h"

#include "Component/FadeOut.h"

/**
* アプリケーションの初期化
*
* @return 0		正常に終了
* @return 0以外 初期化に失敗
*/
int Application::Initialize()
{
	auto assetManager = AssetManager::GetInstance();

	// リソースの読み込み
	for (int i = 0; i < 10; i++)
	{
		std::string num = "Num" + std::to_string(i);
		assetManager->LoadTga(num, "Application/Res/UI/Num/" + num + ".tga");
	}

	// タイトル
	{
		assetManager->LoadTga("TitleBackGround",	"Application/Res/UI/TitleBackGround.tga");
		assetManager->LoadTga("TitleGundamEye",		"Application/Res/UI/GundamEye.tga");
		assetManager->LoadTga("PleaseButton",		"Application/Res/UI/PleaseButton.tga");
	}
	// 選択
	{
		assetManager->LoadTga("SelectBackGround",	"Application/Res/UI/SelectBackGround.tga");
		assetManager->LoadTga("BattleButton",		"Application/Res/UI/SelectButton/BattleButton.tga");
		assetManager->LoadTga("ExitButton",			"Application/Res/UI/SelectButton/ExitButton.tga");
	}
	// バトル設定
	{
		assetManager->LoadTga("BattleSettingBackGround", "Application/Res/UI/BattleSettingBackGround.tga");
	}
	// バトル
	{
		assetManager->LoadTga("Standby",	"Application/Res/UI/Battle/Standbay.tga");
		assetManager->LoadTga("Go",			"Application/Res/UI/Battle/Go.tga");

	}
	// バトルマップ01
	{
		assetManager->LoadTga("SkyBox",			"Application/Res/Map/skyBox.tga");
		assetManager->LoadGlTF("Map01/Ground",	"Application/Res/Map/Map01/Ground.gltf");
		assetManager->LoadGlTF("Map01/BiruA",	"Application/Res/Map/Map01/BuildingA.gltf");
		assetManager->LoadGlTF("Map01/BiruB",	"Application/Res/Map/Map01/BuildingB.gltf");
		assetManager->LoadGlTF("Map01/BiruC",	"Application/Res/Map/Map01/BuildingC.gltf");
	}
	// MS
	{
		// ガンダム
		{
			assetManager->LoadGlTF("Gundam", "Application/Res/Ms/Gundam/Model/Gundam.gltf");
			assetManager->LoadObj("Gundam/BeumRifleBullet", "Application/Res/Ms/Gundam/Model/BeumRifleBullet.obj");
			assetManager->LoadTga("Gundam/BeumRifleIcon", "Application/Res/Ms/Gundam/UI/BeumRifleIcon.tga");
			assetManager->LoadObj("Gundam/BazookaBullet", "Application/Res/Ms/Gundam/Model/BazookaBullet.obj");
			assetManager->LoadTga("Gundam/BazookaIcon", "Application/Res/Ms/Gundam/UI/BazookaIcon.tga");
		}
	}

	auto fadeObject = GameObject::Create(CreateObjectType::Empty);
	fadeObject->name = "FadeObject";
	fadeObject->AddComponent<FadeOut>();

	// これからも使う予定なのでアセットマネージャーに登録しておく
	AssetManager::GetInstance()->LoadGameObject(fadeObject);

	// シーンの登録
	//SceneManager::AddScene<TitleScene>("TitleScene");
	//SceneManager::AddScene<SelectScene>("SelectScene");
	//SceneManager::AddScene<BattleSettingScene>("BattleSettingScene");
	SceneManager::AddScene<BattleMap01Scene>("BattleMap01Scene");

	return 0;
}

/**
* アプリケーションの更新
*/
void Application::Update()
{
}

/**
* アプリケーションの終了
*/
void Application::Fainalize()
{
}
