/**
* @file TitleScene.cpp
*/
#include "TitleScene.h"
using namespace FGEngine::SceneSystem;
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

	obj = objManager->CreateGameObject("GameObject", Vector3(0,0,0), Quaternion::identity);
	auto col = obj->AddComponent<SphereCollider>();
	auto mesh = obj->AddComponent<MeshRenderer>();
	mesh->mesh = resouceManager->GetGltfFile("Gundam")->meshes[0];
	mesh->materials = resouceManager->GetGltfFile("Gundam")->materials;
	mesh->shader = resouceManager->GetShader(DefalutShader::Standard3D);
	mesh->shadowShader = resouceManager->GetShader(DefalutShader::Shadow3D);
	//mesh->materials = CloneMaterialList(mesh->mesh);
	//mesh->materials[0]->mainTexture = resouceManager->GetTexture("white");

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

	auto camera = obj;

	if (InputKey::GetKey(KeyCode::E))
	{
		rotY += 1 * Time::DeltaTime();
	}
	if (InputKey::GetKey(KeyCode::Q))
	{
		rotY -= 1 * Time::DeltaTime();
	}
	if (InputKey::GetKey(KeyCode::W))
	{
		camera->GetTransform()->position += camera->GetTransform()->Forward() * Time::DeltaTime();
	}
	if (InputKey::GetKey(KeyCode::S))
	{
		camera->GetTransform()->position -= camera->GetTransform()->Forward() * Time::DeltaTime();
	}
	if (InputKey::GetKey(KeyCode::A))
	{
		camera->GetTransform()->position -= camera->GetTransform()->Right() * Time::DeltaTime();
	}
	if (InputKey::GetKey(KeyCode::D))
	{
		camera->GetTransform()->position += camera->GetTransform()->Right() * Time::DeltaTime();
	}

	camera->GetTransform()->rotation = Quaternion::AngleAxis(rotX, Vector3::right) * Quaternion::AngleAxis(rotY, Vector3::up);
}

/**
* �^�C�g���V�[���̏I��
*
* @param engine �G���W��
*/
void TitleScene::Finalize()
{
}
