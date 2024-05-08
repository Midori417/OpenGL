/**
* @file Gundam.cpp
*/
#include "Gundam.h"
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;

/**
* 最初に実行
*/
void Gundam::Start()
{
	// リソースマネージャーを取得
	auto resManager = ResouceManager::GetInstance();

	// 描画コンポーネントを追加
	auto renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Standard3D);
}

/**
* 毎フレーム実行
*/
void Gundam::Update()
{
}

/**
* 移動
*
* @param moveAxis 入力軸
*/
void Gundam::Move(const Vector2& moveAxis)
{
    auto camera = OwnerObject();

    if (InputKey::GetKey(KeyCode::Q))
    {
        angle -= 10 * Time::DeltaTime();
    }
    if (InputKey::GetKey(KeyCode::E))
    {
        angle += 10 * Time::DeltaTime();
    }
    const float speed = 3;
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


    camera->GetTransform()->rotation = Quaternion::AngleAxis(angle, Vector3::up);
}
