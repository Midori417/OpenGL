/**
* TesScene.cpp
*/
#include "TestScene.h"
using namespace FGEngine;
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;

bool TestScene::Initialize()
{
	auto objManager = ObjectManager::GetInstance();
	auto resManager = ResouceManager::GetInstance();
	// ��̉摜
	resManager->LoadTga("Sky", "Application/Res/Map/sky2.tga");

	// �J�����̍쐬
	auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -10));
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);


	// �X�J�C�X�t�B�A��ݒ�
	auto material = std::make_shared<Material>();
	material->mainTexture = resManager->GetTexture("Sky");
	skyMaterial = material;

	return 0;
}