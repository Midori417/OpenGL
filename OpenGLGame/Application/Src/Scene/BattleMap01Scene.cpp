/**
* @file BattleMap01Scene.cpp
*/
#include "BattleMap01Scene.h"
#include "../BattleManager.h"
#include <thread>
#include <chrono>

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
	auto resManager = AssetManager::GetInstance();

	if (!isResouceLoad)
	{
		// ��̉摜
		resManager->LoadTga("Sky", "Application/Res/Map/sky2.tga");
		// �}�b�v01�̃��\�[�X�ǂݍ���
		resManager->LoadGlTF("Map01", "Application/Res/Map/Map01/Map01.gltf");
		resManager->LoadGlTF("Map01/Ground", "Application/Res/Map/Map01/Ground.gltf");
		//resManager->LoadGlTF("Map01/Biru01", "Application/Res/Map/Map01/Biru01.gltf");
		//resManager->LoadGlTF("Map01/Biru02", "Application/Res/Map/Map01/Biru02.gltf");
		//resManager->LoadGlTF("Map01/Biru03", "Application/Res/Map/Map01/Biru03.gltf");
		isResouceLoad = true;
	}

	// �J�������쐬
	GameObjectPtr camera = Create(CreateObject::Camera);

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
		GameObjectPtr battleManagerObject = Create(CreateObject::Empty);
		battleManagerObject->name = "BattleManager";

		auto battleManager = battleManagerObject->AddComponent<BattleManager>();
		// �}�b�v�̃��X�|�[���̈ʒu��`����
		battleManager->SetResponPos(responPoses);
	}
	
	// �ǂ̍���
	const float wallHeight = 100;

	// �ǂ��쐬
	{
		// �O
		{
			GameObjectPtr wall = Create(CreateObject::Empty);
			wall->name = "Wall_F";
			wall->GetTransform()->position = Vector3(0, -6.0f, mapSize.y);
			wall->GetTransform()->scale = Vector3(mapSize.x, wallHeight, 1);
			wall->tag = "Wall";

			// �Փ˔����ǉ�
			auto col = wall->AddComponent<AabbCollider>();
			col->min = Vector3(-1, -1, -10);

			// �ԐF�̐����쐬
			GameObjectPtr line = Create(CreateObject::Empty);
			line->name = "Line_F";
			line->GetTransform()->position = Vector3(0, 1.0f, mapSize.y);
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
			GameObjectPtr wall = Create(CreateObject::Empty);
			wall->name = "Wall_B";
			wall->GetTransform()->position = Vector3(0, -6.0f, -mapSize.y);
			wall->GetTransform()->scale = Vector3(mapSize.x, wallHeight, 1);
			wall->tag = "Wall";

			// �Փ˔����ǉ�
			auto col = wall->AddComponent<AabbCollider>();
			col->max = Vector3(1, 1, -10);

			// �ԐF�̐����쐬
			GameObjectPtr line = Create(CreateObject::Empty);
			line->name = "Line_B";
			line->GetTransform()->position = Vector3(0, 1.0f, -mapSize.y);
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
			GameObjectPtr wall = Create(CreateObject::Empty);
			wall->name = "Wall_R";
			wall->GetTransform()->position = Vector3(mapSize.x, -6.0f, 1);
			wall->GetTransform()->scale = Vector3(1, wallHeight, mapSize.y);
			wall->tag = "Wall";

			// �Փ˔����ǉ�
			auto col = wall->AddComponent<AabbCollider>();
			col->max = Vector3(10, 1, 1);

			// �ԐF�̐����쐬
			GameObjectPtr line = Create(CreateObject::Empty);
			line->name = "Line_R";
			line->GetTransform()->position = Vector3(mapSize.x, 1.0f, 0);
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
			GameObjectPtr wall = Create(CreateObject::Empty);
			wall->name = "Wall_R";
			wall->GetTransform()->position = Vector3(-mapSize.x, -6.0f, 1);
			wall->GetTransform()->scale = Vector3(1, wallHeight, mapSize.y);
			wall->tag = "Wall";

			// �Փ˔����ǉ�
			auto col = wall->AddComponent<AabbCollider>();
			col->min = Vector3(-10, -1, -1);

			// �ԐF�̐����쐬
			GameObjectPtr line = Create(CreateObject::Empty);
			line->name = "Line_R";
			line->GetTransform()->position = Vector3(-mapSize.x, 1.0f, 0);
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
			GameObjectPtr ground = Create(CreateObject::Empty);
			ground->name = "Ground";
			ground->GetTransform()->position = Vector3::down;

			auto renderer = ground->AddComponent<GltfMeshRenderer>();
			renderer->glTFfile = resManager->GetGltfFile("Map01/Ground");
			renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
			auto col = ground->AddComponent<AabbCollider>();
			col->min = Vector3(-mapSize.x, -10.0f, -mapSize.y);
			col->max = Vector3(mapSize.x, 1, mapSize.y);
		}
		// ����
		{

		}
	}


	// �X�J�C�X�t�B�A��ݒ�
	auto material = std::make_shared<Material>();
	material->mainTexture = resManager->GetTexture("Sky");
	skyBoxMaterial = material;

	return true;
}