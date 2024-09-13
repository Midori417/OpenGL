/**
* @file BattleMap01Scene,cpp
*/
#include "BattleMap01Scene.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/AabbCollider.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Asset/Material.h"

#include "../Component/BattleManger.h"

/**
* �o�g���}�b�v01�V�[���̏�����
*
* @return true  ����������
* @return false ���������s
*/
bool BattleMap01Scene::Initialize()
{
    // �A�Z�b�g�}�l�[�W���[���擾
    auto assetManager = AssetManager::GetInstance();

    // �J�����쐬
    auto camera = Instantate(CreateObjectType::Camera);

    // �o�g���}�l�[�W���[���쐬
    GameObjectPtr manager = Instantate(CreateObjectType::Empty);
    auto batManager = manager->AddComponent<BattleManager>();
    
    // �X�e�[�W�̑傫����ݒ�
    const Vector2 mapSize(150, 180);

    // ���A�ʒu
    std::vector<Vector3> responPoses;
    responPoses.push_back(Vector3(0, 20, 50));
    responPoses.push_back(Vector3(0, 20, -50));
    responPoses.push_back(Vector3(-118, 20, -30));
    responPoses.push_back(Vector3(-100, 20, -79));
    responPoses.push_back(Vector3(140, 20, 112));

    // �}�l�[�W���[�Ƀ��X�|�[���ʒu��ݒ�
    batManager->SetResponPos(responPoses);

    // �}�b�v���쐬
    {
        // �n��
        {
            GameObjectPtr ground = Instantate(CreateObjectType::Empty);
            ground->name = "Ground";
            ground->GetTransform()->position = Vector3::zero;

            GltfMeshRendererPtr render = ground->AddComponent<GltfMeshRenderer>();
            render->glTFfile = assetManager->GetGltfFile("Map01/Ground");
            render->shader = assetManager->GetShader(DefalutShader::Standard3D);

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
    material->mainTexture = assetManager->GetTexture("SkyBox");
    skyBoxMaterial = material;

    return false;
}
