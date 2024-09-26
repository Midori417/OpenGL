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

	namespace Jump
	{
		const char Rifle[] = "Jump.Rifle";
		const char Sable[] = "Jump.Sable";

		const char GroundRifle[] = "Jump.Rifle.Ground";
		const char GroundSable[] = "Jump.Sable.Ground";
	}
	namespace Dash
	{
		const char Rifle[] = "Dash.Rifle";
		const char Sable[] = "Dash.Sable";
	}
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
	// ダッシュパラメータ
	{
		dash.speed = 30.0f;
		dash.rotationSpeed = 0.01f;
		dash.useBoost = 30.0f;
	}
	// ジャンプパラメータ
	{
		jump.power = 20.0f;
		jump.speed = 10.0f;
		jump.rotationSpeed = 0.01f;
		jump.useBoost = 30.0f;
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
	Dash(msInput->moveAxis, msInput->dashBtn);
	Jump(msInput->moveAxis, msInput->jumpBtn);
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
void Gundam::IdleAnimation() const
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
* 移動できるかチェック
*
* @retval true	可能
* @retval false	不可能
*/
bool Gundam::MoveCheck() const
{
	if (jump.isNow || dash.isNow)
	{
		return false;
	}
	return true;
}

/**
* 移動処理
*/
void Gundam::Move(const Vector2& moveAxis)
{
	Vector3 moveFoward = MoveForward(moveAxis);

	if (rb->IsGround())
	{
		// 移動処理できるかチェック
		if (!MoveCheck())
		{
			return;
		}

		// トランスフォームを取得
		TransformPtr transform = GetTransform();

		// 進行方向に補間しながら回転
		if (moveFoward != Vector3::zero)
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
void Gundam::MoveAnimation() const
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

/**
* ダッシュできるかチェック
*
* @retval true	可能
* @retval false	不可能
*/
bool Gundam::DashCheck() const
{
	return true;
}

/**
* ダッシュ処理
*/
void Gundam::Dash(const Vector2& moveAxis, bool isBtn)
{
	// ダッシュ入力があれば
	if (isBtn)
	{
		// ダッシュ可能かチェック
		if (!DashCheck())
		{
			return;
		}
		if (boost.current > 0)
		{
			// トランスフォームを取得
			TransformPtr transform = GetTransform();

			// 重力を無効化
			rb->isGravity = false;

			// 移動方向を取得
			Vector3 moveFoward = MoveForward(moveAxis);

			// 進行方向に補間しながら回転
			if (moveFoward != Vector3::zero)
			{
				transform->rotation = Quaternion::Slerp(transform->rotation,
					Quaternion::LookRotation(moveFoward), dash.rotationSpeed);
			}
			transform->position += transform->Forward() * dash.speed * Time::DeltaTime();

			// アニメーション切り替え
			DashAnimation();

			// ダッシュ状態にする
			dash.isNow = true;
		}
	}
	else
	{
		if (dash.isNow)
		{
			// 重力を有効
			rb->isGravity = true;

			// ダッシュ状態を解除
			dash.isNow = false;

			// アニメーション切り替え
			IdleAnimation();
		}
	}
}

/**
* ダッシュアニメーションの処理
*/
void Gundam::DashAnimation()
{
	// ダッシュしていないときにアニメーションする
	if (!dash.isNow)
	{
		if (handWeapon == HandWeapon::Rifle)
		{
			anim->SetAnimation(AnimationName::Dash::Rifle);
		}
		else
		{
			anim->SetAnimation(AnimationName::Dash::Sable);
		}
		anim->Play();
	}
}

/**
* ジャンプ可能かチェック
*
* @retval true	可能
* @retval false	不可能
*/
bool Gundam::JumpCheck() const
{
	if (dash.isNow)
	{
		return false;
	}
	return true;
}

/**
* ジャンプ処理
*/
void Gundam::Jump(const Vector2& moveAxis, bool isBtn)
{
	// ジャンプ可能かチェック
	if (!JumpCheck())
	{
		return;
	}

	// ジャンプ入力があれば
	if (isBtn)
	{
		if (boost.current > 0)
		{
			// トランスフォームを取得
			TransformPtr transform = GetTransform();

			// 重力を無効化
			rb->velocity = Vector3::zero;
			rb->isGravity = false;

			// 移動方向を取得
			Vector3 moveFoward = MoveForward(moveAxis);

			// 進行方向に補間しながら回転
			if (moveFoward != Vector3::zero)
			{
				transform->rotation = Quaternion::Slerp(transform->rotation,
					Quaternion::LookRotation(moveFoward), jump.rotationSpeed);
				transform->position += transform->Forward() * jump.speed * Time::DeltaTime();
			}

			// 上昇
			transform->position.y += jump.power * Time::DeltaTime();

			// アニメーション切り替え
			JumpAnimation();

			// ジャンプ状態にする
			jump.isNow = true;
		}
	}
	else
	{
		// ジャンプ中だった場合
		if (jump.isNow)
		{
			// 重力を有効
			rb->isGravity = true;

			// ジャンプ状態を解除
			jump.isNow = false;

			// アニメーション切り替え
			IdleAnimation();
		}
	}
}

/**
* ジャンプアニメーションの処理
*/
void Gundam::JumpAnimation() const
{
	// ジャンプしてない場合のみアニメーションを再生する
	if (!jump.isNow)
	{
		// 地面についていたら
		if (rb->IsGround())
		{
			if (handWeapon == HandWeapon::Rifle)
			{
				anim->SetAnimation(AnimationName::Jump::GroundRifle);
			}
			else
			{
				//anim->SetAnimation(AnimationName::Jump::GroundSable);
				anim->SetAnimation(AnimationName::Jump::GroundRifle);
			}
		}
		else
		{
			if (handWeapon == HandWeapon::Rifle)
			{
				anim->SetAnimation(AnimationName::Jump::Rifle);
			}
			else
			{
				anim->SetAnimation(AnimationName::Jump::Sable);
			}
		}
		anim->Play();
	}
}

/**
* ビームライフル射撃ができるかチェック
*
* @retval true	可能
* @retval false	不可能
*/
bool Gundam::BeumRifleShotCheck() const
{
	return true;
}

/**
* ビームライフル射撃処理
*/
void Gundam::BeumRifleShot(bool isBtn)
{
}

/**
* ビームライフル射撃アニメーションの処理
*/
void Gundam::BeumRifleShotAnimaion() const
{
}
