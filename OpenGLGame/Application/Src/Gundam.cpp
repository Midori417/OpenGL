/**
* @file Gundam.cpp
*/
#include "Gundam.h"
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;

/**
* 最初に実行
*/
void Gundam::Awake()
{
	// リソースマネージャーを取得
	auto resManager = ResouceManager::GetInstance();

	// 描画コンポーネントを追加
	auto renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = resManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// 重力を追加
	rb = OwnerObject()->AddComponent<Rigidbody>();

	// コライダーを追加
	auto col = OwnerObject()->AddComponent<AabbCollider>();
	col->min = Vector3(-1, -5.2f, -1);
	col->max = Vector3(1, 2.4f, 1);

	// アニメータを追加
	anim = OwnerObject()->AddComponent<Animator>();
	anim->animationClips = renderer->glTFfile->animationClips;

	// 最初のアニメーションを追加
	anim->SetAnimation("MagunamIdle", true);
	anim->Play();

	// ステータスを設定
	hpMax = 600;
	hp = hpMax;
	cost = 2000;

	// 移動パラメータ
	moveParamater.speed = 30.0f;
	moveParamater.rotationSpeed = 0.05f;
	moveParamater.dash.speed = 35.0f;
	moveParamater.dash.rotationSpeed = 0.01f;
	moveParamater.jump.power = 10.0f;
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
	auto cameraTrs = GetCameraTransform();
	// カメラの位置を設定されていない
	if (!cameraTrs || moveParamater.dash.isNow || moveParamater.jump.isNow)
	{
		return;
	}

	// カメラの方向から、X-Z単位ベクトル(正規化)を取得
	Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
	Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

	if (rb->IsGrounded())
	{
		// 進行方向に回転
		if (moveForward != Vector3::zero)
		{
			GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
				Quaternion::LookRotation(moveForward), moveParamater.rotationSpeed);
		}
		if (moveAxis != Vector2::zero)
		{
			// オブジェクトの向いてる方向に進む
			GetTransform()->position += GetTransform()->Forward() * moveParamater.speed * Time::DeltaTime();

			// 歩くアニメーションをさせる
			anim->SetAnimation("MagunamRun", true);
			anim->Play();
		}
		else
		{
			anim->SetAnimation("MagunamIdle", true);
			anim->Play();
		}
	}
}

/**
* CPUの移動
*/
void Gundam::CpuMove()
{
}

/**
* ジャンプ
*/
void Gundam::Jump(bool isJump)
{
	if (moveParamater.dash.isNow)
	{
		return;
	}
	if (isJump)
	{
		rb->velocity.y = 0;
		GetTransform()->position.y += moveParamater.jump.power * Time::DeltaTime();

		if (!moveParamater.jump.isNow)
		{
			moveParamater.jump.isNow = true;
			anim->SetAnimation("MagunamJump");
			anim->Play();
		}
	}
	else
	{
		if (moveParamater.jump.isNow)
		{
			moveParamater.jump.isNow = false;
			anim->SetAnimation("MagunamIdle", true);
			anim->Play();
		}
	}
}

/**
* ダッシュ
*/
void Gundam::Dash(bool isDash, const Vector2& moveAxis)
{
	if (isDash)
	{
		rb->velocity.y = 0;
		auto cameraTrs = GetCameraTransform();
		// カメラの位置を設定されていない
		if (!cameraTrs)
		{
			return;
		}

		// カメラの方向から、X-Z単位ベクトル(正規化)を取得
		Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
		Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

		// 進行方向に回転
		if (moveForward != Vector3::zero)
		{
			GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
				Quaternion::LookRotation(moveForward), moveParamater.dash.rotationSpeed);
		}
		// オブジェクトの向いてる方向に進む
		GetTransform()->position += GetTransform()->Forward() * moveParamater.dash.speed * Time::DeltaTime();

		if (!moveParamater.dash.isNow)
		{
			// 歩くアニメーションをさせる
			anim->SetAnimation("MagunamDash", true);
			anim->Play();
		}
		moveParamater.dash.isNow = true;
	}
	else
	{
		if (moveParamater.dash.isNow)
		{
			moveParamater.dash.isNow = false;
			anim->SetAnimation("MagunamIdle", true);
			anim->Play();
		}
	}
}
