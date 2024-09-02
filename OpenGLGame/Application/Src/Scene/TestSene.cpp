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

	// �J�������쐬
	GameObjectPtr camer = Create(CreateObject::Camera);

	// �X�J�C�X�t�B�A��ݒ�
	auto material = std::make_shared<Material>();
	material->mainTexture = resManager->GetTexture("Sky");
	skyBoxMaterial = material;

	return 0;
}