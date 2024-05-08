/**
* @file Gundam.cpp
*/
#include "Gundam.h"
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;

/**
* �ŏ��Ɏ��s
*/
void Gundam::Start()
{
	// ���\�[�X�}�l�[�W���[���擾
	auto resManager = ResouceManager::GetInstance();

	// �`��R���|�[�l���g��ǉ�
	auto renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Skeletal3D);
    //renderer->shadowShader = resManager->GetShader(DefalutShader::ShadowSkeletal3D);
    //rb = OwnerObject()->AddComponent<Rigidbody>();

    auto col = OwnerObject()->AddComponent<AabbCollider>();
    col->min = Vector3(-1, -5.2f, -1);
    col->max = Vector3(1,  2.4f, 1);

    anim = OwnerObject()->AddComponent<Animator>();
    anim->animationClips = renderer->glTFfile->animationClips;
    anim->SetAnimation("MagunamRun", true);
    anim->Play();
}

/**
* ���t���[�����s
*/
void Gundam::Update()
{
}

/**
* �ړ�
*
* @param moveAxis ���͎�
*/
void Gundam::Move(const Vector2& moveAxis)
{
    auto camera = OwnerObject();

    if (InputKey::GetKey(KeyCode::Q))
    {
        camera->GetTransform()->Rotate(Vector3(0, -1, 0));
    }
    if (InputKey::GetKey(KeyCode::E))
    {
        camera->GetTransform()->Rotate(Vector3(0, 1, 0));
    }
    const float speed = 20;
    if (InputKey::GetKey(KeyCode::A))
    {
        camera->GetTransform()->position -= speed * camera->GetTransform()->Right() * Time::DeltaTime();
    }
    if (InputKey::GetKey(KeyCode::D))
    {
        camera->GetTransform()->position += speed * camera->GetTransform()->Right() * Time::DeltaTime();
    }
    if (InputKey::GetKey(KeyCode::LeftShift))
    {
        camera->GetTransform()->position -= speed * camera->GetTransform()->Up() * Time::DeltaTime();
    }
    if (InputKey::GetKey(KeyCode::Space))
    {
        camera->GetTransform()->position += speed * camera->GetTransform()->Up() * Time::DeltaTime();
    }
    if (InputKey::GetKey(KeyCode::S))
    {
        camera->GetTransform()->position -= speed * camera->GetTransform()->Forward() * Time::DeltaTime();
    }
    if (InputKey::GetKey(KeyCode::W))
    {
        camera->GetTransform()->position += speed * camera->GetTransform()->Forward() * Time::DeltaTime();
    }
}
