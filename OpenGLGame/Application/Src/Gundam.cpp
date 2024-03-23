/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "PlayerManager.h"
#include "EnemyMs.h"
#include "MagunamBullet.h"
#include "SableAttack.h"
#include "PlayerController.h"
#include <algorithm>

/**
* 生成イベント
*/
void Gundam::Awake()
{
	// エンジンを取得
	auto engine = GetGameObject()->GetEngine();

	// コライダーを追加
	auto colllder = GetGameObject()->AddComponent<AabbCollider>();
	colllder->aabb = { Vector3(-1,-6.5f,-1), Vector3(1,1,1) };

	// プレイヤー入力を追加
	msInput = GetGameObject()->AddComponent<PlayerController>();

	// レンダラーを追加
	renderer = GetGameObject()->AddComponent<GltfAnimatedMeshRenderer>();
	renderer->fileBuffer = engine->GetGltfFileBuffer();
	renderer->file = engine->LoadGltf("Application/Res/Gundam/Model/GundamGL.gltf");

	// キャラクタームーブメントを追加
	characterMovement = GetGameObject()->AddComponent<CharacterMovement>();

	shotParameter.iconfileName = "Application/Res/Gundam/UI/BeumMagunamIcon.tga";
	shotParameter.maxAmo = 7;
	shotParameter.amo = shotParameter.maxAmo;

	numArmer.push_back(&shotParameter);
}

/**
* スタートイベント
*/
void Gundam::Start()
{
	// アニメーションを設定
	renderer->SetAnimation("MagunamIdle", false);
	renderer->Play();
	parameter.hpMax = 600;
	parameter.hp = parameter.hpMax;
	parameter.teum = 1;
}

/**
* 更新イベント 
*/
void Gundam::Update()
{
	auto engine = GetGameObject()->GetEngine();

	// 地面チャック
	GroundCheck();

	// インターバル更新
	IntervalUpdate();

	for (auto x : numArmer)
	{
		x->AmoReloadUpdate();
	}

	// 移動処理
	Move();

	
	// 地面についていたらエネルギー回復
	if (parameter.boostPower > 0 && state == State::None && isGrond)
	{
		parameter.boostPower -= powerHealSpeed * Time::deltaTime();
	}
	if (moveParameter.moveTimer > 0)
	{
		moveParameter.moveTimer -= Time::deltaTime();
	}

	// ステート
	switch (state)
	{
	case Gundam::State::None:
		
		// 武器状態がマグナムの時
		if (defaultWeapon == DefaultWeapon::Magunam)
		{
			if (msInput->inputAxis.magnitude() > 0.05f && isGrond && moveParameter.moveTimer <= 0)
			{
				if (animState != AnimState::MagunamRun)
				{
					animState = AnimState::MagunamRun;
					renderer->SetAnimation("MagunamRun");
					renderer->Play();
				}
			}
			// 移動入力がないとき || 地面についていない落下状態
			if(msInput->inputAxis.magnitude() <= 0.05f || !isGrond)
			{
				if (animState != AnimState::MagunamIdle)
				{
					animState = AnimState::MagunamIdle;
					renderer->SetAnimation("MagunamIdle", false);
					renderer->Play();
				}
			}
		}
		// 武器状態がサーベルの時
		if (defaultWeapon == DefaultWeapon::Sable)
		{
			if (msInput->inputAxis.magnitude() > 0.05f && isGrond && moveParameter.moveTimer <= 0)
			{
				if (animState != AnimState::SableRun)
				{
					animState = AnimState::SableRun;
					renderer->SetAnimation("SableRun");
					renderer->Play();
				}
			}
			if (msInput->inputAxis.magnitude() <= 0.05f || !isGrond)
			{
				if (animState != AnimState::SableIdle && renderer->GetAnimation()->name != "Sableget")
				{
					animState = AnimState::SableIdle;
					renderer->SetAnimation("SableIdle", false);
					renderer->Play();
				}
			}
		}

		// 近接攻撃
		if (msInput->fightBtn && sableParameter.timer <= 0)
		{
			if (playerManager->GetDistance() <= attackParameter.shotDistance)
			{
				defaultWeapon = DefaultWeapon::Sable;
				renderer->SetAnimation("SableAttackMove", false);
				renderer->Play();
				state = State::SableMove;
				animState = AnimState::SableAttack01;
				sableParameter.moveTimer = 0.6f;
				moveParameter.moveTimer = 0.6f;

			}
			if (playerManager->GetDistance() > attackParameter.shotDistance)
			{
				if (defaultWeapon != DefaultWeapon::Sable)
				{
					defaultWeapon = DefaultWeapon::Sable;
					renderer->SetAnimation("Sableget", false);
					renderer->Play();
					moveParameter.moveTimer = renderer->GetAnimation()->totalTime;
				}
				else if(defaultWeapon == DefaultWeapon::Sable && moveParameter.moveTimer <= 0)
				{
					renderer->SetAnimation("SableAttack01", false);
					renderer->Play();
					auto sable = engine->Create<GameObject>("SableCollision", transform->position + transform->rotation * sableParameter.sablePos);
					auto sableAttack = sable->AddComponent<SableAttack>();
					sableAttack->SetAtk(20.0f);
					sableAttack->SetTeum(parameter.teum);
					state = State::SableAttack;
					animState = AnimState::SableAttack01;
					moveParameter.moveTimer = renderer->GetAnimation()->totalTime;

				}
			}
		}
		
		// 遠距離攻撃
		if (msInput->shotBtn && shotParameter.timer <= 0 && shotParameter.amo > 0)
		{
			// 初期状態をマグナムにする
			defaultWeapon = DefaultWeapon::Magunam;

			// マグナムの弾を減らす
			shotParameter.amo -= 1;

			// 敵の位置を取得
			Vector3 pos = playerManager->enemyMs->transform->position;
			auto rot = LookAt(transform->position, pos, Vector3::up);
			// 敵の方向を向く
			transform->rotation = Quaternion::RotationMatrixToQuaternio(Matrix3x3(rot));
			
			// 射撃のインターバル
			shotParameter.timer = shotParameter.interval;

			// 弾を生成
			auto bullet = engine->Create<GameObject>("Bullet", transform->position + transform->rotation * shotParameter.shotPos, transform->rotation);
			auto magunamBullet = bullet->AddComponent<MagunamBullet>();
			bullet->tag = "PlayerBullet";
			magunamBullet->SetTargetTrs(playerManager->enemyMs->transform);
			magunamBullet->SetTeum(parameter.teum);
			if (playerManager->GetDistance() > attackParameter.shotDistance)
			{
				magunamBullet->SetHoming(false);
			}
			// 状態を射撃に変更
			state = State::Shot;
		}

		break;
	case Gundam::State::Jump:

		// 武器状態がマグナム
		if (defaultWeapon == DefaultWeapon::Magunam)
		{
			if (animState != AnimState::MagunamJump)
			{
				animState = AnimState::MagunamJump;
				renderer->SetAnimation("MagunamJump", false);
				renderer->Play();
			}
		}
		// 武器状態がサーベル
		else if (defaultWeapon == DefaultWeapon::Sable)
		{
			if (animState != AnimState::SableJump)
			{
				animState = AnimState::SableJump;
				renderer->SetAnimation("SableJump", false);
				renderer->Play();
			}
		}

		break;
	case Gundam::State::Dash:

		if (defaultWeapon == DefaultWeapon::Magunam)
		{
			if (animState != AnimState::MagunamDash)
			{
				animState = AnimState::MagunamDash;
				renderer->SetAnimation("MagunamDash", false);
				renderer->Play();
			}
		}
		else if (defaultWeapon == DefaultWeapon::Sable)
		{
			if (animState != AnimState::SableDash)
			{
				animState = AnimState::SableDash;
				renderer->SetAnimation("SableDash", false);
				renderer->Play();
			}

		}
		break;

	case Gundam::State::Shot:

		// 歩きながら射撃
		if (msInput->inputAxis.magnitude() > 0.05f && isGrond)
		{
			if (animState != AnimState::RunMagunamShot && animState != AnimState::MagunamShot)
			{
				animState = AnimState::RunMagunamShot;
				renderer->SetAnimation("RunMagunamShot", false);
				renderer->Play();
				shotParameter.shotAnimTimer = renderer->GetAnimation()->totalTime;
			}
		}
		if (msInput->inputAxis.magnitude() <= 0.05f || !isGrond)
		{
			if (animState != AnimState::MagunamShot && animState != AnimState::RunMagunamShot)
			{
				animState = AnimState::MagunamShot;
				renderer->SetAnimation("MagunamShot", false);
				renderer->Play();
				shotParameter.shotAnimTimer = renderer->GetAnimation()->totalTime;
			}
		}

		if (shotParameter.shotAnimTimer > 0)
		{
			shotParameter.shotAnimTimer -= Time::deltaTime();
		}
		if (shotParameter.shotAnimTimer <= 0)
		{
			transform->rotation = Quaternion::LookRotation(transform->forward() * Vector3(1, 0, 1));
			state = State::None;
		}
		break;

	case State::SableMove:

		transform->LookAt(playerManager->enemyMs->transform->position, Vector3::up);
		transform->position += 50 * transform->forward() * Time::deltaTime();

		sableParameter.moveTimer -= Time::deltaTime();
		if ((playerManager->GetDistance() <= 3 && state != State::SableAttack) || (sableParameter.moveTimer <= 0 && state == State::SableAttack))
		{
			state = State::SableAttack;
			renderer->SetAnimation("SableAttack01", false);
			renderer->Play();
			auto sable = engine->Create<GameObject>("SableCollision", transform->position + transform->rotation* sableParameter.sablePos);
			auto sableAttack =  sable->AddComponent<SableAttack>();
			sableAttack->SetAtk(20.0f);
			sableAttack->SetTeum(parameter.teum);

		}
		break;
	case State::SableAttack:

		if (renderer->GetTime() >= renderer->GetAnimation()->totalTime - 0.2f && msInput->fightBtn && state != State::SableAttack02)
		{
			state = State::SableAttack02;
			renderer->SetAnimation("SableAttack02", false);
			renderer->Play();
			auto sable = engine->Create<GameObject>("SableCollision", transform->position + transform->rotation * sableParameter.sablePos);
			auto sableAttack = sable->AddComponent<SableAttack>();
			sableAttack->SetAtk(30.0f);
			sableAttack->SetTeum(parameter.teum);
			moveParameter.moveTimer = renderer->GetAnimation()->totalTime;
		}
		else if (renderer->GetTime() >= renderer->GetAnimation()->totalTime)
		{
			state = State::None;
			transform->rotation = Quaternion::LookRotation(transform->forward() * Vector3(1, 0, 1));
			sableParameter.timer = sableParameter.interval;
		}
		break;
	case State::SableAttack02:
		
		if (renderer->GetTime() >= renderer->GetAnimation()->totalTime - 0.2f && msInput->fightBtn && state != State::SableAttack03)
		{
			state = State::SableAttack03;
			renderer->SetAnimation("SableAttack03", false);
			renderer->Play();
			auto sable = engine->Create<GameObject>("SableCollision", transform->position + transform->rotation * sableParameter.sablePos);
			auto sableAttack = sable->AddComponent<SableAttack>();
			sableAttack->SetAtk(40.0f);
			sableAttack->SetTeum(parameter.teum);

			moveParameter.moveTimer = renderer->GetAnimation()->totalTime;
		}
		else if (renderer->GetTime() >= renderer->GetAnimation()->totalTime)
		{
			state = State::None;
			transform->rotation = Quaternion::LookRotation(transform->forward() * Vector3(1, 0, 1));
			sableParameter.timer = sableParameter.interval;
		}

		break;
	case State::SableAttack03:

		if (renderer->GetTime() >= renderer->GetAnimation()->totalTime)
		{
			state = State::None;
			transform->rotation = Quaternion::LookRotation(transform->forward() * Vector3(1, 0, 1));
			sableParameter.timer = sableParameter.interval;
		}

		break;

	}
}


/**
* 移動処理
*/
void Gundam::Move()
{
	if (!cameraTrs || moveParameter.moveTimer > 0)
	{
		return;
	}
	// カメラの方向から、X-Z単位ベクトル(正規化)を取得
	Vector3 cameraForward = Vector3::Scale(cameraTrs->forward(), Vector3(1, 0, 1)).normalized();
	Vector3 moveForward = cameraForward * msInput->inputAxis.y + cameraTrs->right() * msInput->inputAxis.x;

	if (isGrond) 
	{
		// 進行方向に回転
		if (moveForward != Vector3::zero)
		{
			transform->rotation = Quaternion::Slerp(transform->rotation, Quaternion::LookRotation(moveForward), moveParameter.rotationSpeed);
		}
		if (msInput->inputAxis != Vector2::zero) 
		{
			// オブジェクトの向いてる方向に進む
			transform->position += transform->forward() * moveParameter.speed * Time::deltaTime();
		}
	}
	if (msInput->jumpBtn)
	{
		if (parameter.boostPower >= parameter.boostPowerMax)
		{
			state = State::None;
			return;
		}

		// 重力をオフ
		//characterMovement->isGravity = false;
		if (state == State::Jump) 
		{
			// ジャンプ処理
			Jump(moveForward);
		}
		if (state == State::Dash)
		{
			// ダッシュ処理
			Dash(moveForward);
		}
	}
	else
	{
		if (state == State::Jump)
		{
			state = State::None;
		}
	}
	if (state != State::Dash) 
	{

		if (msInput->jumpBtn) 
		{
			if (!msInput->jumpBtnDown)
			{
				msInput->jumpBtnDown = true;
				// 前回押されていなければ押されたことにする
				if (!msInput->jumpBtnPush)
				{
					msInput->jumpBtnPush = true;
					state = State::Jump;
					msInput->jumpBtnTimer = 0;
				}
				else 
				{
					// 制限時間内に押されていればダッシュする
					if (msInput->jumpBtnTimer <= 0.5)
					{
						state = State::Dash;
					}
				}
			}
		}
		else 
		{
			// 押されいない
			msInput->jumpBtnDown = false;
		}
	}
	else 
	{
		if (!msInput->jumpBtn)
		{
			state = State::None;
			msInput->jumpBtnPush = false;
		}
	}
	// 最初の移動キー押していれば時間計測
	if (msInput->jumpBtnPush)
	{
		// 時間計測
		msInput->jumpBtnTimer += Time::deltaTime();

		if (msInput->jumpBtnTimer > 0.5)
		{
			msInput->jumpBtnPush = false;
		}
	}
}

void Gundam::Jump(const Vector3& moveForward)
{
	if (msInput->inputAxis != Vector2::zero) {
		// 向いてる方向に少し進む
		transform->position += transform->forward() * (moveParameter.speed / 2) * Time::deltaTime();
	}
	parameter.boostPower += 10.0f * Time::deltaTime();
	characterMovement->velocity.y = moveParameter.jumpPower;

	// 進行方向に回転
	if (moveForward != Vector3::zero) {
		transform->rotation = Quaternion::Slerp(transform->rotation, Quaternion::LookRotation(moveForward), moveParameter.rotationSpeed / 2);
	}
}

void Gundam::Dash(const Vector3& moveForward)
{
	characterMovement->velocity.y = 0;
	transform->position += transform->forward() * moveParameter.dashSpeed * Time::deltaTime();
	parameter.boostPower += 10.0f * Time::deltaTime();
	// 進行方向に回転
	if (moveForward != Vector3::zero)
	{
		transform->rotation = Quaternion::Slerp(transform->rotation, Quaternion::LookRotation(moveForward),0.01f);
	}
}

/**
* インターバル処理
*/
void Gundam::IntervalUpdate()
{
	if (shotParameter.timer > 0)
	{
		shotParameter.timer -= Time::deltaTime();
	}

	if (sableParameter.timer > 0)
	{
		sableParameter.timer -= Time::deltaTime();
	}
}
