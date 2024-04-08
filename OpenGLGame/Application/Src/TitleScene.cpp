/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
using namespace FGEngine::SceneSystem;
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;

/**
* �^�C�g���V�[���̏�����
* 
* @param engine �G���W��
*/
bool TitleScene::Initialize()
{
	auto objManager = ObjectManager::GetInstance();
	auto resouceManager = ResouceManager::GetInstance();

	auto camera = objManager->CreateGameObject("Camera");
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);

	auto material = std::make_shared<Material>();
	material->mainTexture = resouceManager->GetTexture("sky");

	skyMaterial = material;

	return true;
}

/**
* �^�C�g���V�[���̍X�V
* 
* @param engine		�G���W��
* @param deltaTime	�O��̍X�V����̌o�ߎ���
*/
void TitleScene::Update()
{
}

/**
* �^�C�g���V�[���̏I��
* 
* @param engine �G���W��
*/
void TitleScene::Finalize()
{
}
