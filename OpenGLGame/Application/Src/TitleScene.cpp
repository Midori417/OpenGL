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

	obj = objManager->CreateGameObject("GameObject", Vector3(0,5,0), Quaternion::identity);
	auto col = obj->AddComponent<SphereCollider>();
	obj->AddComponent<Rigidbody>();
	auto mesh = obj->AddComponent<MeshRenderer>();
	mesh->mesh = resouceManager->GetStaticMesh(ShapeType::Sphere);
	mesh->shader = resouceManager->GetShader(DefalutShader::Standard3D);
	mesh->materials = CloneMaterialList(mesh->mesh);
	mesh->materials[0]->mainTexture = resouceManager->GetTexture("white");

	auto obj2 = objManager->CreateGameObject("GameObject", Vector3(0,-2,0), Quaternion::identity);
	auto col2 = obj2->AddComponent<BoxCollider>();
	auto mesh2 = obj2->AddComponent<MeshRenderer>();
	mesh2->mesh = resouceManager->GetStaticMesh(ShapeType::Cube);
	mesh2->shader = resouceManager->GetShader(DefalutShader::Standard3D);
	mesh2->materials = CloneMaterialList(mesh2->mesh);
	mesh2->materials[0]->mainTexture = resouceManager->GetTexture("white");

	auto obj3 = objManager->CreateGameObject("UI", Vector3::zero, Quaternion::identity);
	auto image = obj3->AddComponent<Image>();
	image->size = Vector2(1280, 720);
	image->texture = resouceManager->GetTexture("white");


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
