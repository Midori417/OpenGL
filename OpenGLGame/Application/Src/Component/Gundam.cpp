/**
* @file Gndam.h
*/
#include "Gundam.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Other/Time.h"

#include "../GameInput.h"

// サウンドの名前
namespace Sound
{

}

// オウディオソースの番号
namespace AudioIndex
{

}

// アニメーションの名前
namespace Animation
{
	const char idleRifle[] = "Idle.Rifle";
	const char idleSable[] = "Idle.Sable";
	const char runRifle[] = "Run.Rifle";
	const char runSable[] = "Run.Sable";
}

/**
* 生成時に実行
*/
void Gundam::Awake()
{
	// アセットマネージャーを取得
	auto assetManager = AssetManager::GetInstance();

	OwnerObject()->name = "Gundam";
	OwnerObject()->tag = "MS";

	meshRender = OwnerObject()->AddComponent<GltfMeshRenderer>();
	meshRender->glTFfile = assetManager->GetGltfFile("Gundam");
	meshRender->shader = assetManager->GetShader(DefalutShader::Skeletal3D);
	meshRender->shadowShader = assetManager->GetShader(DefalutShader::ShadowSkeletal3D);

	rb = OwnerObject()->AddComponent<Rigidbody>();
	// 落下速度を上げたいので2にする
	rb->gravityScale = 2;

	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = 2.4f;
	col->ceneter = Vector3(0, -2.3f, 0);
	auto col2 = OwnerObject()->AddComponent<SphereCollider>();
	col2->radius = 2.5f;
	col2->ceneter = Vector3(0, -0.4f, -0.2f);

	anim = OwnerObject()->AddComponent<Animator>();
	anim->animationClips = meshRender->glTFfile->animationClips;

	// パラメータを設定
	paramater.hpMax = 600;
	paramater.hp = paramater.hpMax;
	paramater.cost = 2000;

	// 移動
	move.speed = 40.0f;
	move.rotationSpeed = 0.05f;

	// ジャンプ
	jump.power = 30.0f;
	jump.speed = 10.0f;
	jump.rotationSpeed = 0.05f;
	jump.useEnergy = 30.0f;

	// ダッシュ
	dash.speed = 40.0f;
	dash.rotationSpeed = 0.01f;
	dash.useEnergy = -30.0f;

	// 武装の追加
	{
		// ビームライフル
		{

		}
		// バズーカ
		{

		}
	}
}

/**
* Updateが始まる前に一度実行
*/
void Gundam::Start()
{
	// 最初に再生するアニメショーンを設定
	anim->SetAnimation(Animation::idleRifle, true);
	anim->Play();
}

/**
* 毎フレーム実行
*/
void Gundam::Update()
{
	// 破壊されていたら何もしない
	if (IsDestroy())
	{
		return;
	}

	// 破壊チェック
	if (DestroyCheck())
	{
		if (!IsDestroy())
		{
			Destroy();
		}
		return;
	}

	if (gameInput)
	{
		Move(gameInput->moveAxis);
	}
}

/**
* ガンダムコンポーネントをクローンをする
*
* @return クローンされたガンダムコンポーネント
*/
ComponentPtr Gundam::Clone() const
{
	return ComponentPtr();
}

/**
* 移動
*
* @param moveAxis 移動入力
*/
void Gundam::Move(const Vector2& moveAxis)
{
	// カメラの位置を取得
	auto cameraTrs = GetCameraTransform();
	if (!cameraTrs)
	{
		return;
	}
	\
		// カメラの方向から、X-Z単位ベクトル(正規化)を取得
		Vector3 cameraForward = Vector3::Normalize(cameraTrs->Forward() * Vector3(1, 0, 1));
	Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

	if (rb->IsGround())
	{
		// 進行方向に回転
		if (moveForward != Vector3::zero)
		{
			GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
				Quaternion::LookRotation(moveForward), move.rotationSpeed);
		}
		if (moveAxis != Vector2::zero)
		{
			// オブジェクトの向いてる方向に進む
			GetTransform()->position += GetTransform()->Forward() * move.speed * Time::DeltaTime();

		}
		// 移動入力があれば歩きアニメーションを再生
		if (moveAxis != Vector2::zero)
		{
			switch (handWeapon)
			{
			case Gundam::HandWeapon::Rifle:
				anim->SetAnimation(Animation::runRifle, true);
				anim->Play();
				break;
			case Gundam::HandWeapon::Sable:
				anim->SetAnimation(Animation::runSable, true);
				anim->Play();
				break;
			}
		}
		// 移動入力がなければアイドルアニメーションを再生
		else
		{
			switch (handWeapon)
			{
			case Gundam::HandWeapon::Rifle:
				anim->SetAnimation(Animation::idleRifle, true);
				anim->Play();
				break;
			case Gundam::HandWeapon::Sable:
				anim->SetAnimation(Animation::idleSable, true);
				anim->Play();
				break;
			}
		}
	}
}

