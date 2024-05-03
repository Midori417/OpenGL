/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;
using namespace FGEngine::UI;

/**
* タイトルシーンの初期化
*
* @param engine エンジン
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
* タイトルシーンの更新
*
* @param engine		エンジン
* @param deltaTime	前回の更新からの経過時間
*/
void TitleScene::Update()
{
	if (InputKey::GetKeyDown(KeyCode::Enter))
	{
		SceneManager::LoadScene("メインシーン");
	}
}

/**
* タイトルシーンの終了
*
* @param engine エンジン
*/
void TitleScene::Finalize()
{
	ObjectManager::GetInstance()->AllClearGameObject();
}
