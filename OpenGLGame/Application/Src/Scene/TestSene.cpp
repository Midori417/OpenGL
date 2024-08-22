/**
* TesScene.cpp
*/
#include "TestScene.h"
using namespace FGEngine;

bool TestScene::Initialize()
{
	auto resManager = AssetManager::GetInstance();
	// ��̉摜
	resManager->LoadTga("Sky", "Application/Res/Map/sky2.tga");

	// �J�����̍쐬
	auto camera = CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
	auto cameraInfo = camera->AddComponent<Camera>();
	SetMainCameraInfo(cameraInfo);

	// �X�J�C�X�t�B�A��ݒ�
	auto material = std::make_shared<Material>();
	material->mainTexture = resManager->GetTexture("Sky");
	skyBoxMaterial = material;

	return 0;
}