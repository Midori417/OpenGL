/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Other/Time.h"

/**
* アニメーションの名前
*/
namespace AnimationName
{
	const char IdleRifle[] = "Idle.Rifle";
	const char IdleSable[] = "Idle.Sable";

	const char RunRifle[] = "Run.Rifle";
	const char RunSable[] = "Run.Sable";
}

/**
* 生成時に実行
*/
void Gundam::Awake()
{
	// アセットマネージャーを取得
	auto assetManager = AssetManager::GetInstance();

	// 機体共通コンポーネントを取得
	ComponentGet();

	// デフォルトの落下速度だと遅いのでグラビティスケールを強くする
	rb->gravityScale = 2;

	// 描画コンポーネントを設定
	renderer->glTFfile = assetManager->GetGltfFile("Gundam");
	renderer->shader = assetManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = assetManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// アニメータを設定
	anim->animationClips = renderer->glTFfile->animationClips;
	// 最初に流すアニメーションを設定
	anim->SetAnimation(AnimationName::IdleRifle, true);
	anim->Play();

	// コライダーを追加
	SphereColliderPtr col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = 2.4f;
	col->ceneter = Vector3(0, -2.3f, 0);
	SphereColliderPtr col2 = OwnerObject()->AddComponent<SphereCollider>();
	col2->radius = 2.5f;
	col2->ceneter = Vector3(0, -0.4f, -0.2f);

	// 基礎パラメータを設定
	{
		paramater.strengthValue = 2000;
		paramater.durabilityMax = 600;
		paramater.durability = paramater.durabilityMax;
	}
	// 移動パラメータ
	{
		move.speed = 20.0f;
		move.rotationSpeed = 0.05f;
	}
}

/**
* 毎フレーム実行
*/
void Gundam::Update()
{
	if (!Check())
	{
		return;
	}

	Move(msInput->moveAxis);
}

/**
* 必要なコンポーネント、変数が取得できているかチェック
*
* @retval true	取得できている
* @retval false	必要なものが足りていない
*/
bool Gundam::Check()
{
	if (!rb)
	{
		return false;
	}
	if (!renderer)
	{
		return false;
	}
	if (!anim)
	{
		return false;
	}
	if (!msInput)
	{
		return false;
	}
	if (!GetTrsCamera())
	{
		return false;
	}

	return true;
}

/**
* アイドル状態にする
*/
void Gundam::IdleAnimation()
{
	if (handWeapon == HandWeapon::Rifle)
	{
		anim->SetAnimation(AnimationName::IdleRifle, true);
	}
	else
	{
		anim->SetAnimation(AnimationName::IdleSable, true);
	}
	anim->Play();
}

/**
* 移動処理
*/
void Gundam::Move(const Vector2& moveAxis)
{
	Vector3 moveFoward = MoveForward(moveAxis);

	if (rb->IsGround())
	{
		TransformPtr transform = GetTransform();
		// 進行方向に補間しながら回転
		if(moveFoward != Vector3::zero)
		{
			transform->rotation = Quaternion::Slerp(transform->rotation,
				Quaternion::LookRotation(moveFoward), move.rotationSpeed);
			transform->position += transform->Forward() * move.speed * Time::DeltaTime();
			MoveAnimation();
		}
		else
		{
			IdleAnimation();
		}
	}
}

/**
* 移動アニメーションの処理
*/
void Gundam::MoveAnimation()
{
	if (handWeapon == HandWeapon::Rifle)
	{
		anim->SetAnimation(AnimationName::RunRifle, true);
	}
	else
	{
		anim->SetAnimation(AnimationName::RunSable, true);
	}
	anim->Play();
}