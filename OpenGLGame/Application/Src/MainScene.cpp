/**
* @file MainScene.cpp
*/
#include "MainScene.h"
#include <thread>
#include <chrono>

/**
* ���C���V�[���̏�����
* 
* @param engine �G���W��
* 
* @return true  ����������
* @return false ���������s
*/
bool MainScene::Initialize()
{
    auto objManager = ObjectSystem::ObjectManager::GetInstance();
    auto resManager = ResouceSystem::ResouceManager::GetInstance();

    auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
    camera->AddComponent<Camera>();
    objManager->SetMainCamera(camera);


    auto material = std::make_shared<Material>();
    material->mainTexture = resManager->GetTexture("sky");

    skyMaterial = material;


	return true;
}

/**
* ���C���V�[���̍X�V
* 
* @param engine �G���W��
*/
void MainScene::Update()
{
}

/**
* ���C���V�[���̏I��
* 
* @param engine �G���W��
*/
void MainScene::Finalize()
{

}
