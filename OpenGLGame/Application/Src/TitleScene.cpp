/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;
using namespace FGEngine::UI;

/**
* �^�C�g���V�[���̏�����
*
* @param engine �G���W��
*/
bool TitleScene::Initialize()
{
	auto objManager = ObjectManager::GetInstance();
	auto resouceManager = ResouceManager::GetInstance();

	auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -10), Quaternion::identity);
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);

	auto title = objManager->CreateGameObject("title");
	auto iamge = title->AddComponent<Image>();
	iamge->texture = resouceManager->GetTexture("Title");
	iamge->size = WindowSystem::WindowManager::GetInstance()->GetWindowSize();

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
	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		SceneManager::LoadScene("���C���V�[��");
	}
}

/**
* �^�C�g���V�[���̏I��
*
* @param engine �G���W��
*/
void TitleScene::Finalize()
{
	ObjectManager::GetInstance()->AllClearGameObject();
}
