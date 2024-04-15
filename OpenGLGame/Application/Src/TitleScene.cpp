/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
using namespace FGEngine::SceneSystem;
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;

/**
* タイトルシーンの初期化
*
* @param engine エンジン
*/
bool TitleScene::Initialize()
{
	auto objManager = ObjectManager::GetInstance();
	auto resouceManager = ResouceManager::GetInstance();

	auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, 10), Quaternion::identity);
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);

	auto obj = objManager->CreateGameObject("GameObject");
	auto mesh = obj->AddComponent<MeshRenderer>();
	mesh->mesh = resouceManager->GetStaticMesh(PrimitiveType::Cube);
	mesh->shader = resouceManager->GetShader("Unlit");
	mesh->materials = CloneMaterialList(mesh->mesh);
	mesh->materials[0]->mainTexture = resouceManager->GetTexture("white");

	obj->GetTransform()->SetParent(camera->GetTransform());

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
	auto objManager = ObjectManager::GetInstance();

	auto camera = objManager->GetMainCamera();

	if (InputKey::GetKey(KeyCode::E))
	{
		rotY++;
	}
	if (InputKey::GetKey(KeyCode::Q))
	{
		rotY--;
	}
	if (InputKey::GetKey(KeyCode::W))
	{

	}

	camera->GetTransform()->rotation = Quaternion::AngleAxis(rotY, Vector3::up);
}

/**
* タイトルシーンの終了
*
* @param engine エンジン
*/
void TitleScene::Finalize()
{
}
