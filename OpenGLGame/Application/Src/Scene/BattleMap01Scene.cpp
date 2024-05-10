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

/**
* �퓬�V�[���̏�����
* 
* @param engine �G���W��
* 
* @return true  ����������
* @return false ���������s
*/
bool BattleMap01Scene::Initialize()
{
    auto objManager = ObjectManager::GetInstance();
    auto resManager = ResouceManager::GetInstance();

    resManager->LoadGlTF("Gundam", "Application/Res/Ms/Gundam/Model/GundamGL.gltf");

    // �}�b�v01�̃��\�[�X�ǂݍ���
    resManager->LoadObj("Biru01", "Application/Res/Map/Map01/Biru01.obj");
    resManager->LoadObj("Biru02", "Application/Res/Map/Map01/Biru02.obj");
    resManager->LoadObj("Biru03", "Application/Res/Map/Map01/Biru03.obj");
    resManager->LoadObj("Load", "Application/Res/Map/Map01/Load.obj");
    resManager->LoadObj("Ground", "Application/Res/Map/Map01/Ground.obj");
    resManager->LoadTga("Grass", "Application/Res/Map/Map01/Grass.tga");


    // �J�������쐬
    auto camera = objManager->CreateGameObject("Camera", Vector3(0, 0, -20), Quaternion::identity);
    camera->AddComponent<Camera>();
    objManager->SetMainCamera(camera);

    // �X�e�[�W�̑傫����ݒ�
    mapX = 150;
    mapZ = 120;


    // �o�g���}�l�[�W�F�[���쐬
    {
        auto battleManagerObj = objManager->CreateGameObject("BattleManager");
        auto battleManager = battleManagerObj->AddComponent<BattleManager>();
        battleManager->mapX = mapX;
        battleManager->mapZ = mapZ;
    }

    // �ǂ��쐬
    {
        // �O
        {
            auto wall = objManager->CreateGameObject("Wall", Vector3(0, -6.0f, 121));
            wall->GetTransform()->scale = Vector3(151, 100, 1);
            auto col = wall->AddComponent<AabbCollider>();

            auto line = objManager->CreateGameObject("Line", Vector3(0, -5.8f, 121));
            line->GetTransform()->scale = Vector3(151, 1, 1);
            auto render = line->AddComponent<MeshRenderer>();
            render->mesh = resManager->GetStaticMesh("Cube");
            render->shader = resManager->GetShader(DefalutShader::Unlit);
            render->materials = CloneMaterialList(render->mesh);
            render->materials[0]->mainTexture = resManager->GetTexture("white");
            render->materials[0]->color = Color::red;
        }
        // ���
        {
            auto wall = objManager->CreateGameObject("Wall", Vector3(0, -6.0f, -121));
            wall->GetTransform()->scale = Vector3(151, 100, 1);
            auto col = wall->AddComponent<AabbCollider>();

            auto line = objManager->CreateGameObject("Line", Vector3(0, -5.8f, -121));
            line->GetTransform()->scale = Vector3(151, 1, 1);
            auto render = line->AddComponent<MeshRenderer>();
            render->mesh = resManager->GetStaticMesh("Cube");
            render->shader = resManager->GetShader(DefalutShader::Unlit);
            render->materials = CloneMaterialList(render->mesh);
            render->materials[0]->mainTexture = resManager->GetTexture("white");
            render->materials[0]->color = Color::red;

        }

        // �E
        {
            auto wall = objManager->CreateGameObject("Wall", Vector3(151, -6.0f, 0));
            wall->GetTransform()->scale = Vector3(1, 100, 121);
            auto col = wall->AddComponent<AabbCollider>();

            auto line = objManager->CreateGameObject("Line", Vector3(151, -5.8f, 0));
            line->GetTransform()->scale = Vector3(1, 1, 121);
            auto render = line->AddComponent<MeshRenderer>();
            render->mesh = resManager->GetStaticMesh("Cube");
            render->shader = resManager->GetShader(DefalutShader::Unlit);
            render->materials = CloneMaterialList(render->mesh);
            render->materials[0]->mainTexture = resManager->GetTexture("white");
            render->materials[0]->color = Color::red;

        }
        // ��
        {
            auto wall = objManager->CreateGameObject("Wall", Vector3(-151, -6.0f, 0));
            wall->GetTransform()->scale = Vector3(1, 100, 121);
            auto col = wall->AddComponent<AabbCollider>();

            auto line = objManager->CreateGameObject("Line", Vector3(-151, -5.8f, 0));
            line->GetTransform()->scale = Vector3(1, 1, 121);
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
        // �n�ʂ��쐬
         auto ground = objManager->CreateGameObject("Ground", Vector3(0, -6.0f, 0));
        {
            ground->tag = "Ground";
            auto renderer = ground->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Ground");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("Grass");
            auto col = ground->AddComponent<AabbCollider>();
            col->min = Vector3(-150, -0.5f, -120);
            col->max = Vector3(150, 0.5f, 120);
        }

        // �����쐬
        {
            auto load = objManager->CreateGameObject("Load", Vector3(0, 0, 0));
            load->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = load->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Load");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.1f, 0.1f, 0.1f, 1);
        }
        // ����01A���쐬
        {
            auto biru01 = objManager->CreateGameObject("Biru01A", Vector3(-37.0f, 6.0f, 0));
            biru01->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru01->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru01");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
            auto collider = biru01->AddComponent<AabbCollider>();
            collider->min = Vector3(-8.0f, -6.0f, -12.0f);
            collider->max = Vector3(8.0f, 10.0f, 12.0f);
        }
        // ����01B���쐬
        {
            auto biru01 = objManager->CreateGameObject("Biru01B", Vector3(61.0f, 6.0f, -66.0f));
            biru01->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru01->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru01");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
            auto collider = biru01->AddComponent<AabbCollider>();
            collider->min = Vector3(-8.0f, -6.0f, -12.0f);
            collider->max = Vector3(8.0f, 10.0f, 12.0f);
        }
        // ����02A���쐬
        {
            auto biru02 = objManager->CreateGameObject("Biru02A", Vector3(-91.0f, 6.0f, -0.4f));
            biru02->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru02->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru02");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
            auto collider = biru02->AddComponent<AabbCollider>();
            collider->min = Vector3(-16.5f, -6.0f, -12.0f);
            collider->max = Vector3(16.5f, 6.0f, 12.0f);
        }
        // ����02B���쐬
        {
            auto biru02 = objManager->CreateGameObject("Biru02B", Vector3(-43.0f, 6.0f, 77.0f));
            biru02->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru02->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru02");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
            auto collider = biru02->AddComponent<AabbCollider>();
            collider->min = Vector3(-16.5f, -6.0f, -12.0f);
            collider->max = Vector3(16.5f, 6.0f, 12.0f);
        }
        // ����03A���쐬
        {
            auto biru03 = objManager->CreateGameObject("Biru03A", Vector3(-37.0f, 6.0f, 38.0f), Quaternion::AngleAxis(90, Vector3::up));
            biru03->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru03->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru03");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
            auto collider = biru03->AddComponent<AabbCollider>();
            collider->min = Vector3(-16.5f, -6.0f, -9.0f);
            collider->max = Vector3(16.5f, 11.0f, 9.0f);
        }
        // ����03B���쐬
        {
            auto biru03 = objManager->CreateGameObject("Biru03B", Vector3(-95.0f, 6.0f, 78.0f));
            biru03->GetTransform()->SetParent(ground->GetTransform());
            auto renderer = biru03->AddComponent<MeshRenderer>();
            renderer->mesh = resManager->GetStaticMesh("Biru03");
            renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
            renderer->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
            renderer->materials = CloneMaterialList(renderer->mesh);
            renderer->materials[0]->mainTexture = resManager->GetTexture("white");
            renderer->materials[0]->color = Color(0.3f, 0.3f, 0.3f, 1);
            auto collider = biru03->AddComponent<AabbCollider>();
            collider->min = Vector3(-16.5f, -6.0f, -9.0f);
            collider->max = Vector3(16.5f, 11.0f, 9.0f);
        }

    }

    // �X�J�C�X�t�B�A��ݒ�
    auto material = std::make_shared<Material>();
    material->mainTexture = resManager->GetTexture("sky");
    skyMaterial = material;

	return true;
}

/**
* �퓬�V�[���̍X�V
* 
* @param engine �G���W��
*/
void BattleMap01Scene::Update()
{
}

/**
* �퓬�V�[���̏I��
* 
* @param engine �G���W��
*/
void BattleMap01Scene::Finalize()
{

}
