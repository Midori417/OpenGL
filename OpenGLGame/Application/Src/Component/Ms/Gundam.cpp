/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/CreateGameObjectType.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/MeshRenderer.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Asset/AnimationClip.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Other/Time.h"

#include "../HomingBullet.h"

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
	namespace BeumRifleShot
	{
		namespace Idle
		{
			const char F[] = "Rifle.Shot.Idle.F";
			const char B[] = "Rifle.Shot.Idle.B";
			const char R[] = "Rifle.Shot.Idle.R";
			const char L[] = "Rifle.Shot.Idle.L";
			const char FR[] = "Rifle.Shot.Idle.FR";
			const char FL[] = "Rifle.Shot.Idle.FL";
		}
		namespace Run
		{
			const char F[] = "Rifle.Shot.Run.F";
			const char R[] = "Rifle.Shot.Run.R";
			const char L[] = "Rifle.Shot.Run.L";
			const char FR[] = "Rifle.Shot.Run.FR";
			const char FL[] = "Rifle.Shot.Run.FL";
		}
		namespace Dash
		{
			const char F[] = "Rifle.Shot.Dash.F";
			const char R[] = "Rifle.Shot.Dash.R";
			const char L[] = "Rifle.Shot.Dash.L";
		}
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
	// ライフルパラメータ
	{
		beumRifle.amoMax = 999;
		beumRifle.amo = beumRifle.amoMax;

		// 弾を作成
		GameObjectPtr bullet = GameObject::Create(CreateObjectType::Empty);

		MeshRendererPtr render = bullet->AddComponent<MeshRenderer>();
		render->mesh = assetManager->GetStaticMesh("Gundam/BeumRifleBullet");
		render->shader = assetManager->GetShader(DefalutShader::Standard3D);

		SphereColliderPtr col = bullet->AddComponent<SphereCollider>();
		col->isTrigger = true;

		auto homing = bullet->AddComponent<HomingBullet>();
		homing->SetParamater(70.0f, 200.0f, 5.0f, 0.4f);

		beumRifle.bullet = bullet;
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
	BeumRifleShot(msInput->action1Btn);
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
* アイドルアニメーションを再生可能かチェック
*
* @retval true	可能
* @retval false	不可能
*/
bool Gundam::IdleAnimationCheck() const
{
	if (beumRifle.isNow)
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
	if (!IdleAnimationCheck())
	{
		return;
	}
	if (handArmed == HandArmed::Rifle)
	{
		anim->SetAnimation(AnimationName::IdleRifle, true);
	}
	else
	{
		anim->SetAnimation(AnimationName::IdleSable, true);
	}
	anim->Play();
}

#pragma region Move

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
* 移動アニメーションを再生可能かチェック
*
* @retval true	可能
* @retval false	不可能
*/
bool Gundam::MoveAnimationCheck() const
{
	if (!beumRifle.isNow)
	{
		return false;
	}
	return true;
}

/**
* 移動アニメーションの処理
*/
void Gundam::MoveAnimation() const
{
	if (MoveAnimationCheck())
	{
		return;
	}

	if (handArmed == HandArmed::Rifle)
	{
		anim->SetAnimation(AnimationName::RunRifle, true);
	}
	else
	{
		anim->SetAnimation(AnimationName::RunSable, true);
	}
	anim->Play();
}

#pragma endregion

#pragma region Dash

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
* ダッシュアニメーションを再生可能かチェック
*
* @retval true	可能
* @retval false	不可能
*/
bool Gundam::DashAnimationCheck() const
{
	if (beumRifle.isNow)
	{
		return false;
	}
	return true;
}

/**
* ダッシュアニメーションの処理
*/
void Gundam::DashAnimation() const
{
	if (DashAnimationCheck())
	{
		return;
	}
	// ダッシュしていないときにアニメーションする
	if (!dash.isNow)
	{
		if (handArmed == HandArmed::Rifle)
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

#pragma endregion

#pragma region Jump

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
* ジャンプアニメーションを再生可能かチェック
*
* @retval true	可能
* @retval false	不可能
*/
bool Gundam::JumpAnimationCheck() const
{
	if (beumRifle.isNow)
	{
		return false;
	}
	return true;
}

/**
* ジャンプアニメーションの処理
*/
void Gundam::JumpAnimation() const
{
	if (!JumpAnimationCheck())
	{
		return;
	}

	// ジャンプしてない場合のみアニメーションを再生する
	if (!jump.isNow)
	{
		// 地面についていたら
		if (rb->IsGround())
		{
			if (handArmed == HandArmed::Rifle)
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
			if (handArmed == HandArmed::Rifle)
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

#pragma endregion

#pragma region BeumRifleShot

/**
* ビームライフル射撃ができるかチェック
*
* @retval true	可能
* @retval false	不可能
*/
bool Gundam::BeumRifleShotCheck() const
{
	if (beumRifle.isNow)
	{
		return false;
	}

	return true;
}

/**
* ビームライフル射撃処理
*/
void Gundam::BeumRifleShot(bool isBtn)
{
	// 射撃入力がある場合
	if (isBtn)
	{
		if (!BeumRifleShotCheck())
		{
			return;
		}

		// ビームライフルに弾があれば射撃する
		if (beumRifle.amo > 0)
		{
			beumRifle.isNow = true;
			// ハンド武装をライフルにする
			handArmed = HandArmed::Rifle;
		}
	}

	// 射撃中
	if (beumRifle.isNow)
	{
		BeumRifleShotAnimaion();

		// いまだに弾が打たれてなくてアニメーションの再生時間が発射時間になったら弾を発射
		if (anim->time > beumRifle.shotTime && !beumRifle.isShot)
		{
			// 残弾を減らす
			beumRifle.amo -= 1;

			TransformPtr trs = GetTransform();

			// ターゲットの方向を取得
			Vector3 directionToTarget;
			if (GetTarget())
			{
				directionToTarget = Vector3::Normalize(GetTarget()->GetTransform()->position - trs->position);
			}
			else
			{
				directionToTarget = trs->Forward();
			}

			Quaternion rot = Quaternion::LookRotation(directionToTarget);
			// 弾の生成位置を計算
			Vector3 pos = trs->position + rot * beumRifle.shotPos;

			// 弾を作成
			GameObjectPtr bullet = Instantate(beumRifle.bullet, pos, rot);
			auto homing = bullet->GetComponent<HomingBullet>();
			homing->SetTarget(GetTarget());

			// 撃った
			beumRifle.isShot = true;
		}
	}
	// アニメーションが終わったら
	if (anim->time >= anim->GetAnimationClip()->totalTime)
	{
		beumRifle.isNow = false;
		beumRifle.isShot = false;
		beumRifle.isBackShot = false;
	}
}

/**
* ビームライフル射撃アニメーションの処理
*
* @param perY	垂直Y
* @param dot	内積
*/
void Gundam::BeumRifleShotAnimaion()
{
	// ターゲットが自分から見てどの方向にいるか調べる
	Vector3 directionToTarget = Vector3::Normalize(GetTarget()->GetTransform()->position - GetTransform()->position);
	const float perendicularY = Vector3::Cross(directionToTarget, GetTransform()->Forward()).y;
	const float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());
	if (dot < -0.5f && !beumRifle.isBackShot)
	{
		beumRifle.isBackShot = true;
		anim->SetAnimation(AnimationName::BeumRifleShot::Idle::B);
		anim->Play();
	}

	if (!beumRifle.isBackShot)
	{
		// 歩く
		if (msInput->moveAxis != Vector2::zero)
		{
			// 前方
			if (dot > 0.9f)
			{
				if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::F)
				{
					const float time = anim->time;
					anim->SetAnimation(AnimationName::BeumRifleShot::Run::F);
					anim->time = time;
					anim->Play();
				}
			}
			// 右方
			else if (perendicularY < 0)
			{
				if (dot > 0.6f)
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::FR)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Run::FR);
						anim->time = time;
						anim->Play();
					}
				}
				else
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::R)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Run::R);
						anim->time = time;
						anim->Play();
					}
				}
			}
			// 左方
			else if (perendicularY > 0)
			{
				if (dot > 0.6f)
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::FL)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Run::FL);
						anim->time = time;
						anim->Play();
					}
				}
				else
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::L)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Run::L);
						anim->time = time;
						anim->Play();
					}
				}
			}
		}
		// アイドル
		else
		{
			// 前方
			if (dot > 0.9f)
			{
				if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::F)
				{
					const float time = anim->time;
					anim->SetAnimation(AnimationName::BeumRifleShot::Idle::F);
					anim->time = time;
					anim->Play();
				}
			}
			// 右方
			else if (perendicularY < 0)
			{
				if (dot > 0.6f)
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::FR)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Idle::FR);
						anim->time = time;
						anim->Play();
					}
				}
				else
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::R)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Idle::R);
						anim->time = time;
						anim->Play();
					}
				}
			}
			// 左方
			else if (perendicularY > 0)
			{
				if (dot > 0.6f)
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::FL)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Idle::FL);
						anim->time = time;
						anim->Play();
					}
				}
				else
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::L)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Idle::L);
						anim->time = time;
						anim->Play();
					}
				}
			}
		}
	}
}

#pragma endregion