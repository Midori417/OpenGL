/**
* @file BattleMap01Scene.cpp
*/
#include "BattleMap01Scene.h"
#include "../BattleManager.h"
#include <thread>
#include <chrono>
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::ObjectSystem;
using namespace FGEngine::InputSystem;

bool BattleMap01Scene::isResouceLoad = false;

/**
* �퓬�V�[���̏�����
*
* @return true  ����������
* @return false ���������s
*/
bool BattleMap01Scene::Initialize()
{
	// �e�}�l�[�W�����擾
	auto objManager = ObjectManager::GetInstance();
	auto resManager = ResouceManager::GetInstance();

	if (!isResouceLoad)
	{
		// ��̉摜
		resManager->LoadTga("Sky", "Application/Res/Map/sky2.tga");
		// �}�b�v01�̃��\�[�X�ǂݍ���
		resManager->LoadGlTF("Map01", "Application/Res/Map/Map01/Map01.gltf");
		//resManager->LoadGlTF("Map01/Ground", "Application/Res/Map/Map01/Ground.gltf");
		//resManager->LoadGlTF("Map01/Biru01", "Application/Res/Map/Map01/Biru01.gltf");
		//resManager->LoadGlTF("Map01/Biru02", "Application/Res/Map/Map01/Biru02.gltf");
		//resManager->LoadGlTF("Map01/Biru03", "Application/Res/Map/Map01/Biru03.gltf");
		isResouceLoad = true;
	}
	// �J�������쐬
	auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -20), Quaternion::identity);
	camera->AddComponent<Camera>();
	objManager->SetMainCamera(camera);

	// �X�e�[�W�̑傫����ݒ�
	mapSize.x = 150;
	mapSize.y = 180;

	// ���A�ʒu
	std::vector<Vector3> responPoses;
	responPoses.push_back(Vector3(0, 20, 50));
	responPoses.push_back(Vector3(0, 20, -50));
	responPoses.push_back(Vector3(-118, 20, -30));
	responPoses.push_back(Vector3(-100, 20, -79));
	responPoses.push_back(Vector3(140, 20, 112));

	// �o�g���}�l�[�W�����쐬
	{
		auto battleManagerObj = objManager->CreateGameObject("BattleManager");
		auto battleManager = battleManagerObj->AddComponent<BattleManager>();
		battleManager->SetResponPos(responPoses);
	}

	// �ǂ��쐬
	{
		// �O
		{
			auto wall = objManager->CreateGameObject("Wall", Vector3(0, -6.0f, mapSize.y));
			wall->GetTransform()->scale = Vector3(mapSize.x, 100, 1);
			auto col = wall->AddComponent<AabbCollider>();

			auto line = objManager->CreateGameObject("Line", Vector3(0, 1.0f, mapSize.y));
			line->GetTransform()->scale = Vector3(mapSize.x, 1, 1);
			auto render = line->AddComponent<MeshRenderer>();
			render->mesh = resManager->GetStaticMesh("Cube");
			render->shader = resManager->GetShader(DefalutShader::Unlit);
			render->materials = CloneMaterialList(render->mesh);
			render->materials[0]->mainTexture = resManager->GetTexture("white");
			render->materials[0]->color = Color::red;
		}
		// ���
		{
			auto wall = objManager->CreateGameObject("Wall", Vector3(0, -6.0f, -mapSize.y));
			wall->GetTransform()->scale = Vector3(mapSize.x, 100, 1);
			auto col = wall->AddComponent<AabbCollider>();

			auto line = objManager->CreateGameObject("Line", Vector3(0, 1.0f, -mapSize.y));
			line->GetTransform()->scale = Vector3(mapSize.x, 1, 1);
			auto render = line->AddComponent<MeshRenderer>();
			render->mesh = resManager->GetStaticMesh("Cube");
			render->shader = resManager->GetShader(DefalutShader::Unlit);
			render->materials = CloneMaterialList(render->mesh);
			render->materials[0]->mainTexture = resManager->GetTexture("white");
			render->materials[0]->color = Color::red;

		}

		// �E
		{
			auto wall = objManager->CreateGameObject("Wall", Vector3(mapSize.x, -6.0f, 0));
			wall->GetTransform()->scale = Vector3(1, 100, mapSize.y);
			auto col = wall->AddComponent<AabbCollider>();

			auto line = objManager->CreateGameObject("Line", Vector3(mapSize.x, 1.0f, 0));
			line->GetTransform()->scale = Vector3(1, 1, mapSize.y);
			auto render = line->AddComponent<MeshRenderer>();
			render->mesh = resManager->GetStaticMesh("Cube");
			render->shader = resManager->GetShader(DefalutShader::Unlit);
			render->materials = CloneMaterialList(render->mesh);
			render->materials[0]->mainTexture = resManager->GetTexture("white");
			render->materials[0]->color = Color::red;

		}
		// ��
		{
			auto wall = objManager->CreateGameObject("Wall", Vector3(-mapSize.x, -6.0f, 0));
			wall->GetTransform()->scale = Vector3(1, 100, mapSize.y);
			auto col = wall->AddComponent<AabbCollider>();

			auto line = objManager->CreateGameObject("Line", Vector3(-mapSize.x, 1.0f, 0));
			line->GetTransform()->scale = Vector3(1, 1, mapSize.y);
			auto render = line->AddComponent<MeshRenderer>();
			render->mesh = resManager->GetStaticMesh("Cube");
			render->shader = resManager->GetShader(DefalutShader::Unlit);
			render->materials = CloneMaterialList(render->mesh);
			render->materials[0]->mainTexture = resManager->GetTexture("white");
			render->materials[0]->color = Color::red;
		}

	}

	// �X�e�[�W���쐬
	{
		// �y��
		{
			auto groundObj = objManager->CreateGameObject("Ground", Vector3(0, -1.0f, 0));
			auto renderer = groundObj->AddComponent<GltfMeshRenderer>();
			renderer->glTFfile = resManager->GetGltfFile("Map01");
			renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
			auto col = groundObj->AddComponent<AabbCollider>();
			col->min = Vector3(-mapSize.x, -10.0f, -mapSize.y);
			col->max = Vector3(mapSize.x, 1.0f, mapSize.y);
		}
		// ����01
		//{
		//	// A
		//	{
		//		auto biruObjA = objManager->CreateGameObject("Biru01A", Vector3(-43.0f, 0.0f, -18.0f));
		//		auto renderer = biruObjA->AddComponent<GltfMeshRenderer>();
		//		renderer->glTFfile = resManager->GetGltfFile("Map01/Biru01");
		//		renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
		//	}
		//	// B
		//	{
		//		auto biruObjB = objManager->CreateGameObject("Biru01B", Vector3(0, 0.0f, 0));
		//		auto renderer = biruObjB->AddComponent<GltfMeshRenderer>();
		//		renderer->glTFfile = resManager->GetGltfFile("Map01/Biru01");
		//		renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
		//	}
		//}
	}


	// �X�J�C�X�t�B�A��ݒ�
	auto material = std::make_shared<Material>();
	material->mainTexture = resManager->GetTexture("Sky");
	skyMaterial = material;

	return true;
}