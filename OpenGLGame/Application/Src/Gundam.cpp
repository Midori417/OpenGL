/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "Bullet.h"
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;

/**
* 最初に実行
*/
void Gundam::Awake()
{
	// リソースマネージャーを取得
	auto resManager = ResouceManager::GetInstance();
	resManager->LoadObj("Gundam/BeumRifleBullet", "Application/Res/Ms/Gundam/Model/BeumRifleBullet.obj");

	// 描画コンポーネントを追加
	auto renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = resManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// 重力を追加
	rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->gravityScale = 2;

	// コライダーを追加
	auto col = OwnerObject()->AddComponent<AabbCollider>();
	col->min = Vector3(-1, -5.2f, -1);
	col->max = Vector3(1, 2.4f, 1);

	// アニメータを追加
	anim = OwnerObject()->AddComponent<Animator>();
	anim->animationClips = renderer->glTFfile->animationClips;

	// 最初のアニメーションを追加
	anim->SetAnimation("RifleIdle", true);
	anim->Play();

	// ステータスを設定
	hpMax = 600;
	hp = hpMax;
	cost = 2000;
	boostEnergy = boostEnergyMax;

	// 攻撃の距離
	proximityDistance = 40.0f;
	redLookDistace = 90.0f;

	// 移動パラメータ
	moveParamater.speed = 30.0f;
	moveParamater.rotationSpeed = 0.05f;

	// ダッシュ
	moveParamater.dash.speed = 35.0f;
	moveParamater.dash.rotationSpeed = 0.01f;
	moveParamater.dash.useEnergy = -30.0f;

	// ジャンプ
	moveParamater.jump.power = 10.0f;
	moveParamater.jump.speed = 10.0f;
	moveParamater.jump.rotationSpeed = 0.05f;
	moveParamater.jump.useEnergy = -30.0f;

	// 残弾武器を追加
	numWeapons.reserve(3);
	rifle = std::make_shared<Rifle>();
	rifle->name = "BeumRifle";
	rifle->amoMax = 7;
	rifle->amo = rifle->amoMax;
	rifle->mesh = resManager->GetStaticMesh("Gundam/BeumRifleBullet");
	rifle->shader = resManager->GetShader(DefalutShader::Unlit);
	numWeapons.push_back(rifle);
}

/**
* 毎フレーム実行
*/
void Gundam::Update()
{
	// 地面についているとき
	if (rb->IsGrounded() && !boostEnergyChageLock)
	{
		if (boostEnergyChageTimer <= 0)
		{
			// ブーストエネルギーが減っていたら
			if (boostEnergy < boostEnergyMax)
			{
				boostEnergy += boostEnergyChage * Time::DeltaTime();
			}
		}
		else
		{
			// エネルギーチャージ開始タイマーを減らす
			boostEnergyChageTimer -= Time::DeltaTime();
		}
	}
	boostEnergy = Mathf::Clamp(boostEnergy, 0.0f, boostEnergyMax);
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

		}
		if (!rifle->isShot)
		{
			if (moveAxis != Vector2::zero)
			{
				// 歩くアニメーションをさせる
				anim->SetAnimation("RifleRun", true);
				anim->Play();
			}
			else
			{
				anim->SetAnimation("RifleIdle", true);
				anim->Play();
			}
		}
	}
}

/**
* CPUの移動
*/
void Gundam::CpuMove()
{
	if (rb->IsGrounded())
	{
		auto targetFoward = GetTargetMs()->GetTransform()->position * Vector3(1, 0, 1);
		auto targetRot = Matrix4x4::LookAt(GetTransform()->position * Vector3(1, 0, 1), targetFoward, Vector3::up);

		// ターゲットの方向を取得
		auto rot = GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
			Quaternion::RotationMatrixToQuaternion(targetRot), moveParamater.rotationSpeed);

		GetTransform()->rotation = Quaternion(rot.x, rot.y, rot.z, rot.w);

		// 前方向に進む
		GetTransform()->position += moveParamater.speed * GetTransform()->Forward() * Time::DeltaTime();

		// 歩くアニメーションをさせる
		anim->SetAnimation("RifleRun", true);
		anim->Play();
	}
}

/**
* ジャンプ
*/
void Gundam::Jump(bool isJump, const Vector2& moveAxis)
{
	if (moveParamater.dash.isNow)
	{
		return;
	}
	if (isJump)
	{
		// エネルギーがあれば
		if (boostEnergy > 0)
		{
			// 重力の速度を0にして　
			rb->velocity.y = 0;

			auto cameraTrs = GetCameraTransform();
			// カメラの方向から、X-Z単位ベクトル(正規化)を取得
			Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
			Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

			// 進行方向に回転
			if (moveForward != Vector3::zero)
			{
				GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
					Quaternion::LookRotation(moveForward), moveParamater.jump.rotationSpeed);
			}
			if (moveAxis != Vector2::zero)
			{
				// オブジェクトの向いてる方向に進む
				GetTransform()->position += GetTransform()->Forward() * moveParamater.jump.speed * Time::DeltaTime();
			}

			// 上昇
			GetTransform()->position.y += moveParamater.jump.power * Time::DeltaTime();

			boostEnergy += moveParamater.jump.useEnergy * Time::DeltaTime();

			// ジャンプした最初にアニメーションをさせる
			if (!moveParamater.jump.isNow)
			{
				anim->SetAnimation("RifleJump");
				anim->Play();
			}
			moveParamater.jump.isNow = true;

			//ブーストエネルギーの回復をロック
			boostEnergyChageLock = true;
		}
		else
		{
			if (moveParamater.jump.isNow)
			{
				moveParamater.jump.isNow = false;
				boostEnergyChageLock = false;
				boostEnergyChageTimer = boostEnergyChageOverHeatStartTime;
				anim->SetAnimation("RifleIdle", true);
				anim->Play();
			}
		}
	}
	else
	{
		if (moveParamater.jump.isNow)
		{
			moveParamater.jump.isNow = false;
			boostEnergyChageLock = false;
			boostEnergyChageTimer = boostEnergyChageStartTime;
			anim->SetAnimation("RifleIdle", true);
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
		if (boostEnergy > 0)
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

			boostEnergy += moveParamater.dash.useEnergy * Time::DeltaTime();

			if (!moveParamater.dash.isNow)
			{
				anim->SetAnimation("RifleDash", true);
				anim->Play();
			}
			moveParamater.dash.isNow = true;
			boostEnergyChageLock = true;
		}
		else
		{
			if (moveParamater.dash.isNow)
			{
				moveParamater.dash.isNow = false;
				boostEnergyChageLock = false;
				boostEnergyChageTimer = boostEnergyChageOverHeatStartTime;
				anim->SetAnimation("RifleIdle", true);
				anim->Play();
			}
		}
	}
	else
	{
		if (moveParamater.dash.isNow)
		{
			moveParamater.dash.isNow = false;
			boostEnergyChageLock = false;
			boostEnergyChageTimer = boostEnergyChageStartTime;
			anim->SetAnimation("RifleIdle", true);
			anim->Play();
		}
	}
}

/**
* 攻撃(ビームライフル)
*/
void Gundam::Attack1(bool attackKey)
{
	if (attackKey)
	{
		// ビームライフルの弾があるときだけ打つ
		if (rifle->amo > 0 && !rifle->isShot)
		{
			// 残弾を減らす
			rifle->amo -= 1;

			// ターゲットがいてたらそちらを向く
			if (GetTargetMs())
			{
				GetTransform()->LookAt(GetTargetMs()->GetTransform());
			}
			auto pos = GetTransform()->position + (GetTransform()->rotation * Vector3(0.5f, 0.8f, 11.0f));

			// 弾を作成
			auto bullet = Instantate("Bullet", pos, GetTransform()->rotation);
			auto renderer = bullet->AddComponent<MeshRenderer>();
			renderer->mesh = rifle->mesh;
			renderer->shader = rifle->shader;
			auto bulletMove = bullet->AddComponent<Bullet>();
			bulletMove->targetMS = GetTargetMs();

			if (anim->GetAnimationClip()->name == "RifleIdle")
			{
				anim->SetAnimation("RifleShot");
				anim->Play();
			}
			else if (anim->GetAnimationClip()->name == "RifleRun")
			{
				anim->SetAnimation("RunRifleShot");
				anim->Play();
			}


			rifle->isShot = true;
		}
	}
	if (rifle->isShot)
	{
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			rifle->isShot = false;
		}
	}
}

/**
* ダメージ
* 
* @param damage 与えるダメージ
*/
void Gundam::Damage(float damage)
{
	hp -= static_cast<int>(damage);
	if (hp <= 0)
	{
		anim->SetAnimation("RifleDown");
		anim->Play();
	}
}
