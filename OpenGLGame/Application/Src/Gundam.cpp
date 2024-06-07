/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "HomingBullet.h"
#include "BaseSlash.h"
#include "DamageInfo.h"
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;

/**
* 効果音設定
*/
namespace SE
{
	char legSound[] = "Application/Res/Ms/Gundam/Sound/LegSound.mp3";
	char boostSound[] = "Application/Res/Ms/Gundam/Sound/BoostSound.mp3";
	char beumRifleShot[] = "Application/Res/Ms/Gundam/Sound/BeumRifleShot.mp3";
	char bazookaShot[] = "Application/Res/Ms/Gundam/Sound/BazookaShot.mp3";
	char sableAttack[] = "Application/Res/Ms/Gundam/Sound/SableAttack.mp3";
	char sableHit[] = "Application/Res/Ms/Gundam/Sound/SableHit.mp3";
	char dead[] = "Application/Res/Ms/Gundam/Sound/Dead.mp3";
}

namespace Animation
{
	char idleRifle[] = "Idle.Rifle";
	char idleSable[] = "Idle.Sable";
	char stepRifleF[] = "Step.Rifle.F";
	char stepRifleB[] = "Step.Rifle.B";
	char stepRifleR[] = "Step.Rifle.R";
	char stepRifleL[] = "Step.Rifle.L";
	char downCancelRifle[] = "DownCancel.Rifle";
}

namespace AudioIndex
{
	int legSound = 0;
	int otherSound = 1;
}

/**
* 最初に実行
*/
void Gundam::Awake()
{
	// タグをMsにする
	OwnerObject()->tag = "Ms";

	// リソースマネージャーを取得
	auto resManager = ResouceManager::GetInstance();
	if (!isResoueLoad)
	{
		resManager->LoadGlTF("Gundam", "Application/Res/Ms/Gundam/Model/Gundam.gltf");
		resManager->LoadObj("Gundam/BeumRifleBullet", "Application/Res/Ms/Gundam/Model/BeumRifleBullet.obj");
		resManager->LoadTga("Gundam/BeumRifleIcon", "Application/Res/Ms/Gundam/UI/BeumRifleIcon.tga");
		resManager->LoadObj("Gundam/BazookaBullet", "Application/Res/Ms/Gundam/Model/BazookaBullet.obj");
		resManager->LoadTga("Gundam/BazookaIcon", "Application/Res/Ms/Gundam/UI/BazookaIcon.tga");
		isResoueLoad = true;
	}

	// 描画コンポーネントを追加
	renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = resManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// 重力を追加
	rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->gravityScale = 2;

	// コライダーを追加
	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = 2.4f;
	col->ceneter = Vector3(0, -2.3f, 0);
	auto col2 = OwnerObject()->AddComponent<SphereCollider>();
	col2->radius = 2.5f;
	col2->ceneter = Vector3(0, -0.4f, -0.2f);

	// アニメータを追加
	anim = OwnerObject()->AddComponent<Animator>();
	anim->animationClips = renderer->glTFfile->animationClips;

	// 最初のアニメーションを追加
	anim->SetAnimation(Animation::idleRifle, true);
	anim->Play();

	// サウンド
	{
		auto audio = OwnerObject()->AddComponent<AudioSource>();
		audio->SetSoundFilename(SE::legSound);
		audio->SetVolume(0.2f);
		audio->is3DSound = true;
		audioSources.push_back(audio);
	}
	{
		auto audio = OwnerObject()->AddComponent<AudioSource>();
		audio->is3DSound = true;
		audioSources.push_back(audio);
	}

	// 基礎パラメータを設定
	baseParamater.hpMax = 600;
	baseParamater.hp = baseParamater.hpMax;
	baseParamater.cost = 2000;

	// 攻撃の距離
	proximityDistance = 40.0f;
	redLookDistaceXZ = 100.0f;
	redLookDistanceMinY = -100.0f;
	redLookDistanceMaxY = 10.0f;

	// 移動パラメータ
	moveParamater.speed = 20.0f;
	moveParamater.rotationSpeed = 0.05f;

	// ダッシュ
	moveParamater.dash.speed = 40.0f;
	moveParamater.dash.rotationSpeed = 0.01f;
	moveParamater.dash.useEnergy = -30.0f;

	// ジャンプ
	moveParamater.jump.power = 30.0f;
	moveParamater.jump.speed = 10.0f;
	moveParamater.jump.rotationSpeed = 0.05f;
	moveParamater.jump.useEnergy = -30.0f;

	// ステップ
	moveParamater.step.speed = 30.0f;
	moveParamater.step.useEnergy = 20.0f;

	// ライフルの生成
	{
		rifle = std::make_shared<Rifle>();
		rifle->name = "BeumRifle";
		rifle->amoMax = 7;
		rifle->reloadTime = 3;
		rifle->iconTexture = resManager->GetTexture("Gundam/BeumRifleIcon");
		rifle->amo = rifle->amoMax;

		// 弾のパラメータを設定
		rifle->bullet.damage = 70.0f;
		rifle->bullet.downPower = 40;
		rifle->bullet.homingPower = 0.4f;
		rifle->bullet.speed = 200.0f;
		rifle->bullet.mesh = resManager->GetStaticMesh("Gundam/BeumRifleBullet");
		rifle->bullet.shader = resManager->GetShader(DefalutShader::Unlit);
	}
	{
		// バズーカの生成
		bazooka = std::make_shared<Bazooka>();
		bazooka->name = "Bazooka";
		bazooka->amoMax = 3;
		bazooka->amo = bazooka->amoMax;
		bazooka->reloadTime = 4;
		bazooka->iconTexture = resManager->GetTexture("Gundam/BazookaIcon");

		// 弾のパラメータを設定
		bazooka->bullet.damage = 99.0f;
		bazooka->bullet.downPower = 100;
		bazooka->bullet.homingPower = 0.9f;
		bazooka->bullet.speed = 80.0f;
		bazooka->bullet.mesh = resManager->GetStaticMesh("Gundam/BazookaBullet");
		bazooka->bullet.shader = resManager->GetShader(DefalutShader::Standard3D);
		bazooka->bullet.shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
	}
	// サーベル
	{
		sable = std::make_shared<Sable>();
		sable->name = "Sable";
		sable->attack1.damage = 65;
		sable->attack1.downPower = 35;
		sable->attack1.destoryTime = 0.3f;

		sable->attack2.damage = 65;
		sable->attack2.downPower = 35;
		sable->attack2.destoryTime = 0.3f;

		sable->attack3.damage = 75;
		sable->attack3.downPower = 35;
		sable->attack3.destoryTime = 0.5f;
		sable->attack3.slashTime = 0.4f;
	}

	// UI武装配列に追加
	uiWeapons.push_back(bazooka);
	uiWeapons.push_back(rifle);

}

/**
* 毎フレーム実行
*/
void Gundam::Update()
{
	// 停止状態なら何もしない
	if (isStop)
	{
		return;
	}

	// 死亡チェック、死んでいれば何もしない
	if (DeadChaeck())
	{
		if (!isDeath)
		{
			audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::dead);
			audioSources[AudioIndex::otherSound]->Play();
			// 死亡状態にする
			isDeath = true;
		}
		return;
	}

	// 吹き飛び処理
	if (blowAway.isNow && !isDown)
	{
		blowAway.timer += Time::DeltaTime();

		// アニメーションによって吹き飛ぶ方向を変える
		if (anim->GetAnimationClip()->name == "BlowAway.Rifle.F")
		{
			GetTransform()->position -= blowAway.power * GetTransform()->Forward() * Time::DeltaTime();
		}
		else if (anim->GetAnimationClip()->name == "BlowAway.Rifle.B")
		{
			GetTransform()->position += blowAway.power * GetTransform()->Forward() * Time::DeltaTime();
		}
		if (blowAway.timer > blowAway.time && rb->IsGround())
		{
			blowAway.isNow = false;
			rb->gravityScale = 2;

			if (anim->GetAnimationClip()->name == "BlowAway.Rifle.F")
			{
				anim->SetAnimation("Down.Rifle.F");
				anim->Play();
			}
			else if (anim->GetAnimationClip()->name == "BlowAway.Rifle.B")
			{
				anim->SetAnimation("Down.Rifle.B");
				anim->Play();
			}
			downTimer = 0;
			isDown = true;
		}

		// バグ対策
		if (blowAway.timer > 5)
		{
			rb->gravityScale = 2;
			blowAway.isNow = false;
		}
	}

	if (isDown || (blowAway.isNow && blowAway.timer > 0.2f))
	{
		if (gameInput->moveAxis != Vector2::zero)
		{
			boostParamater.current -= 10;
			boostParamater.chageLock = true;
			if (blowAway.isNow)
			{
				rb->gravityScale = 2;
				blowAway.isNow = false;
			}
			if (isDown)
			{
				isDown = false;
			}
			rb->isGravity = false;
			rb->velocity = Vector3::zero;
			anim->SetAnimation(Animation::downCancelRifle);
			anim->Play();
			isDownCancel = true;
		}
	}

	// ダウンキャンセル状態なら
	if (isDownCancel)
	{
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			rb->isGravity = true;
			isDownCancel = false;
			boostParamater.chageLock = false;
			boostParamater.chageStartTimer = boostParamater.chageStartTime;
			if (handWeapon == HandWeapon::Rifle)
			{
				anim->SetAnimation(Animation::idleRifle);
				anim->Play();
			}
			else
			{
				anim->SetAnimation(Animation::idleSable);
				anim->Play();
			}
		}
	}

	// ダウン状態
	if (isDown)
	{
		// ダウン時間を増加
		downTimer += Time::DeltaTime();
		if (downTimer >= downStandUpTime)
		{
			if (anim->GetAnimationClip()->name == "Down.Rifle.F")
			{
				anim->SetAnimation("StandUp.Rifle.F");
				anim->Play();

			}
			else if (anim->GetAnimationClip()->name == "Down.Rifle.B")
			{
				anim->SetAnimation("StandUp.Rifle.B");
				anim->Play();
			}
		}
		// 立ち上げるアニメーション中で
		if (anim->GetAnimationClip()->name == "StandUp.Rifle.F" ||
			anim->GetAnimationClip()->name == "StandUp.Rifle.B")
		{
			// アニメーションが終われば
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// ダウン状態を終了
				isDown = false;
				anim->SetAnimation("Idle.Rifle");
				anim->Play();
			}
		}
	}

	// ダメージ状態なら
	if (isDamage)
	{
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			// ダメージアニメーションが終わればダメージ状態を解除
			isDamage = false;

			// それぞれの状態を元に戻す
			rb->isGravity = true;

			// アニメーションを再生
			if (anim->GetAnimationClip()->name == "Damage.Rifle")
			{
				anim->SetAnimation("Idle.Rifle");
				anim->Play();
			}
		}
	}

	// リスポーン状態
	if (isRespon)
	{
		responTimer -= Time::DeltaTime();
		if (responTimer <= 0)
		{
			isRespon = false;
		}
	}

	// MSの入力行動
	if (gameInput && !isRespon)
	{
		// ダメージ状態なら何もしない
		if (!isDamage && !blowAway.isNow && !isDown && !isDownCancel)
		{
			Step(gameInput->stepBtn, gameInput->moveAxis);
			// 移動
			Move(gameInput->moveAxis);
			// ジャンプ
			Jump(gameInput->jumpBtn, gameInput->moveAxis);
			// ダッシュ
			Dash(gameInput->dashBtn, gameInput->moveAxis);
			// 攻撃(ビームライフル)
			Action1(gameInput->action1Btn);
			// 攻撃2(バズーカ)
			Action2(gameInput->action2Btn);
			// 攻撃(サーベル)
			Action3(gameInput->action3Btn);
		}
	}

	// ブーストエネルギーを更新
	BoostEnergyUpdate();

	// リロードを更新
	ReloadUpdate();
}

/**
* リロード更新
*/
void Gundam::ReloadUpdate()
{
	// ビームライフルのリロード
	{
		// 弾が減っていればリロード
		if (rifle->amo < rifle->amoMax)
		{
			rifle->reloadTimer += Time::DeltaTime();
			if (rifle->reloadTimer > rifle->reloadTime)
			{
				rifle->reloadTimer = 0;
				rifle->amo++;
			}
		}
	}
	// バズーカのリロード
	{
		if (bazooka->amo <= 0)
		{
			bazooka->reloadTimer += Time::DeltaTime();
			if (bazooka->reloadTimer > bazooka->reloadTime)
			{
				bazooka->reloadTimer = 0;
				bazooka->amo = bazooka->amoMax;
			}
		}
	}
}

/**
* 移動
*
* @param moveAxis 入力軸
*/
void Gundam::Move(const Vector2& moveAxis)
{
	// カメラの位置を取得
	auto cameraTrs = GetCameraTransform();
	if (!cameraTrs)
	{
		return;
	}

	// ジャンプ・ダッシュ・ライフルの移動禁止・バズーカ状態なら移動しない
	if (moveParamater.dash.isNow || moveParamater.jump.isNow || moveParamater.step.isNow ||
		rifle->isStopShot || bazooka->isNow || sable->isNow)
	{
		return;
	}

	// カメラの方向から、X-Z単位ベクトル(正規化)を取得
	Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
	Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

	if (rb->IsGround())
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
		if (!rifle->isNow && !bazooka->isNow)
		{
			// 移動入力があれば歩きアニメーションを再生
			if (moveAxis != Vector2::zero)
			{
				moveParamater.moveTimer -= Time::DeltaTime();
				if (moveParamater.moveTimer <= 0)
				{
					moveParamater.moveTimer = moveParamater.moveTime;
					audioSources[AudioIndex::legSound]->Play();
				}

				switch (handWeapon)
				{
				case Gundam::HandWeapon::Rifle:
					anim->SetAnimation("Run.Rifle", true);
					anim->Play();
					break;
				case Gundam::HandWeapon::Sable:
					anim->SetAnimation("Run.Sable", true);
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
					anim->SetAnimation("Idle.Rifle", true);
					anim->Play();
					break;
				case Gundam::HandWeapon::Sable:
					anim->SetAnimation("Idle.Sable", true);
					anim->Play();
					break;
				}
			}
		}
	}
}

/**
* ジャンプ
*/
void Gundam::Jump(bool isJump, const Vector2& moveAxis)
{
	// ダッシュ・ライフルの移動禁止・バズーカ状態ならジャンプしない
	if (moveParamater.dash.isNow || rifle->isStopShot || bazooka->isNow || sable->isNow || moveParamater.step.isNow)
	{
		return;
	}

	// ジャンプ入力があれば
	if (isJump)
	{
		// エネルギーがあればジャンプさせる
		if (boostParamater.current > 0)
		{
			// カメラを取得
			auto cameraTrs = GetCameraTransform();
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
					Quaternion::LookRotation(moveForward), moveParamater.jump.rotationSpeed);
			}
			if (moveAxis != Vector2::zero)
			{
				// オブジェクトの向いてる方向に進む
				GetTransform()->position += GetTransform()->Forward() * moveParamater.jump.speed * Time::DeltaTime();
			}

			// 射撃状態ならアニメーションをキャンセル
			if (!rifle->isNow)
			{
				// ジャンプアニメーションを再生
				if (!moveParamater.jump.isNow)
				{
					audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::boostSound);
					audioSources[AudioIndex::otherSound]->Play();
					if (rb->IsGround())
					{
						if (handWeapon == HandWeapon::Rifle)
						{
							anim->SetAnimation("Jump.Rifle.Ground");
						}
						else
						{
							anim->SetAnimation("Jump.Sable");
						}
					}
					else
					{

						if (handWeapon == HandWeapon::Rifle)
						{
							anim->SetAnimation("Jump.Rifle");
						}
						else
						{
							anim->SetAnimation("Jump.Sable");
						}
					}
					anim->Play();
				}
			}

			// 重力の速度を0にして　
			rb->velocity = Vector3(0);
			// 上昇
			GetTransform()->position.y += moveParamater.jump.power * Time::DeltaTime();

			// エネルギーを消費
			boostParamater.current += moveParamater.jump.useEnergy * Time::DeltaTime();

			//ブーストエネルギーの回復をロック
			boostParamater.chageLock = true;

			// ジャンプ状態に変更
			moveParamater.jump.isNow = true;
		}
		else
		{
			// エネルギーがなくなればジャンプ状態を終わる
			if (moveParamater.jump.isNow)
			{
				// エネルギーチャージのロックを解除
				boostParamater.chageLock = false;
				// エネルギーチャージのタイマーを代入
				boostParamater.chageStartTimer = boostParamater.overHeatChageStartTime;

				// 射撃状態ならアニメーションをキャンセル
				if (!rifle->isNow)
				{
					if (handWeapon == HandWeapon::Rifle)
					{
						anim->SetAnimation("Idle.Rifle", true);
					}
					else
					{
						anim->SetAnimation("Idle.Sable", true);
					}

					anim->Play();
				}
				// ジャンプ状態を終了
				moveParamater.jump.isNow = false;
			}
		}
	}
	else
	{
		if (moveParamater.jump.isNow)
		{
			// エネルギーチャージのロックを解除
			boostParamater.chageLock = false;
			// エネルギーチャージのタイマーを代入
			boostParamater.chageStartTimer = boostParamater.chageStartTime;

			if (!rifle->isNow)
			{
				if (handWeapon == HandWeapon::Rifle)
				{
					anim->SetAnimation("Idle.Rifle", true);
				}
				else
				{
					anim->SetAnimation("Idle.Sable", true);
				}
			}

			// ジャンプ状態を終了
			moveParamater.jump.isNow = false;
		}
	}
}

/**
* ダッシュ
*/
void Gundam::Dash(bool isDash, const Vector2& moveAxis)
{
	// ライフルの停止・バズーカ状態ならダッシュしない
	if (rifle->isStopShot || bazooka->isNow || sable->isNow || moveParamater.step.isNow)
	{
		return;
	}

	if (isDash)
	{
		// エネルギーがあればダッシュさせる
		if (boostParamater.current > 0)
		{
			rb->isVelocity = false;

			rb->velocity.y = 0;
			// カメラを取得
			auto cameraTrs = GetCameraTransform();
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
			rb->velocity = GetTransform()->Forward() * moveParamater.dash.speed;

			// エネルギーを消費
			boostParamater.current += moveParamater.dash.useEnergy * Time::DeltaTime();

			// 射撃状態ならアニメーションをキャンセル
			if (!rifle->isNow)
			{
				if (!moveParamater.dash.isNow)
				{
					audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::boostSound);
					audioSources[AudioIndex::otherSound]->Play();
					if (handWeapon == HandWeapon::Rifle)
					{
						anim->SetAnimation("Dash.Rifle", true);
					}
					else
					{
						anim->SetAnimation("Dash.Sable", true);
					}
					anim->Play();
				}
			}
			// ダッシュ中に変更
			moveParamater.dash.isNow = true;
			// エネルギーチャージをロック
			boostParamater.chageLock = true;
		}
		else
		{
			// エネルギーがなくなればダッシュ状態を終わる
			if (moveParamater.dash.isNow)
			{
				rb->isVelocity = true;
				// エネルギーチャージのロックを解除
				boostParamater.chageLock = false;
				// エネルギーチャージのタイマーを代入
				boostParamater.chageStartTimer = boostParamater.overHeatChageStartTime;

				if (!rifle->isNow)
				{
					if (handWeapon == HandWeapon::Rifle)
					{
						anim->SetAnimation("Idle.Rifle", true);
					}
					else
					{
						anim->SetAnimation("Idle.Sable", true);
					}
				}

				// ダッシュ状態を終了
				moveParamater.dash.isNow = false;
			}
		}
	}
	else
	{
		if (moveParamater.dash.isNow)
		{
			rb->isVelocity = true;
			// エネルギーチャージのロックを解除
			boostParamater.chageLock = false;
			// エネルギーチャージのタイマーを代入
			boostParamater.chageStartTimer = boostParamater.chageStartTime;


			if (!rifle->isNow)
			{
				if (handWeapon == HandWeapon::Rifle)
				{
					anim->SetAnimation("Idle.Rifle", true);
				}
				else
				{
					anim->SetAnimation("Idle.Sable", true);
				}
			}

			// ダッシュ状態を終了
			moveParamater.dash.isNow = false;
		}
	}
}

/**
* 攻撃(ビームライフル)
*/
void Gundam::Action1(bool attackKey)
{
	// 攻撃入力があれば
	if (attackKey)
	{
		if (bazooka->isNow || sable->isNow || moveParamater.step.isNow)
		{
			return;
		}

		// ビームライフルの弾があれば射撃
		if (rifle->amo > 0 && !rifle->isNow)
		{
			// 持っている武装をライフルにする
			handWeapon = HandWeapon::Rifle;

			// ターゲットが自分から見てどの方向にいるか調べる
			Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
			Vector3 perendicular = Vector3::Cross(directionToTarget, GetTransform()->Forward());
			float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());

			// 後ろ向き射撃だけ共通
			if (dot < -0.5f)
			{
				// 動きを止める
				rifle->isStopShot = true;
				// 重力を使わない
				rb->isGravity = false;
				rb->velocity = Vector3(0);

				// 相手の逆方向を向く
				GetTransform()->rotation = Quaternion::LookRotation(-directionToTarget * Vector3(1, 0, 1));

				anim->SetAnimation("Rifle.Shot.Idle.B");
				anim->Play();
			}
			// アイドル・ジャンプ状態
			else if (anim->GetAnimationClip()->name == "Idle.Rifle" ||
				anim->GetAnimationClip()->name == "Jump.Rifle" || anim->GetAnimationClip()->name == "Jump.Rifle.Ground")
			{
				rb->velocity = Vector3(0, 1, 0);
				// 動きを止める
				rifle->isStopShot = true;

				// 前方
				if (dot > 0.9f)
				{
					anim->SetAnimation("Rifle.Shot.Idle.F");
					anim->Play();
				}
				// 右方
				else if (perendicular.y < 0)
				{
					if (dot > 0.6f)
					{
						anim->SetAnimation("Rifle.Shot.Idle.FR");
						anim->Play();
					}
					else
					{
						anim->SetAnimation("Rifle.Shot.Idle.R");
						anim->Play();
					}
				}
				// 左方
				else if (perendicular.y > 0)
				{
					if (dot > 0.6f)
					{
						anim->SetAnimation("Rifle.Shot.Idle.FL");
						anim->Play();
					}
					else
					{
						anim->SetAnimation("Rifle.Shot.Idle.L");
						anim->Play();
					}
				}
			}
			// 歩き状態
			else if (anim->GetAnimationClip()->name == "Run.Rifle" && rb->IsGround())
			{
				// 前方
				if (dot > 0.9f)
				{
					anim->SetAnimation("Rifle.Shot.Run.F");
					anim->Play();
				}
				// 右方
				else if (perendicular.y < 0)
				{
					if (dot > 0.4f)
					{
						anim->SetAnimation("Rifle.Shot.Run.FR");
						anim->Play();
					}
					else
					{
						anim->SetAnimation("Rifle.Shot.Run.R");
						anim->Play();
					}
				}
				// 左方
				else if (perendicular.y > 0)
				{
					if (dot > 0.4f)
					{
						anim->SetAnimation("Rifle.Shot.Run.FL");
						anim->Play();
					}
					else
					{
						anim->SetAnimation("Rifle.Shot.Run.L");
						anim->Play();
					}
				}
			}
			// ダッシュ状態
			else if (anim->GetAnimationClip()->name == "Dash.Rifle")
			{
				// 前方
				if (dot > 0.9f)
				{
					anim->SetAnimation("Rifle.Shot.Dash.F");
					anim->Play();
				}
				// 右方
				else if (perendicular.y < 0)
				{
					anim->SetAnimation("Rifle.Shot.Dash.R");
					anim->Play();
				}
				// 左
				else if (perendicular.y > 0)
				{
					anim->SetAnimation("Rifle.Shot.Dash.L");
					anim->Play();
				}
			}
			else
			{
				rb->velocity = Vector3(0, 1, 0);
				// 動きを止める
				rifle->isStopShot = true;

				// 前方
				if (dot > 0.9f)
				{
					anim->SetAnimation("Rifle.Shot.Idle.F");
					anim->Play();
				}
				// 右方
				else if (perendicular.y < 0)
				{
					if (dot > 0.6f)
					{
						anim->SetAnimation("Rifle.Shot.Idle.FR");
						anim->Play();
					}
					else
					{
						anim->SetAnimation("Rifle.Shot.Idle.R");
						anim->Play();
					}
				}
				// 左方
				else if (perendicular.y > 0)
				{
					if (dot > 0.6f)
					{
						anim->SetAnimation("Rifle.Shot.Idle.FL");
						anim->Play();
					}
					else
					{
						anim->SetAnimation("Rifle.Shot.Idle.L");
						anim->Play();
					}
				}

			}

			// 射撃中
			rifle->isNow = true;
		}
	}
	// 射撃状態
	if (rifle->isNow)
	{
		if (anim->time >= 0.2f && !rifle->isShot)
		{
			auto msPos = GetTransform()->position;

			audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::beumRifleShot);
			audioSources[AudioIndex::otherSound]->Play();

			// 残弾を減らす
			rifle->amo -= 1;

			// ターゲットの方向を取得
			Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
			Quaternion rot = Quaternion::LookRotation(directionToTarget);

			// 弾の生成位置を計算
			auto pos = GetTransform()->position + (rot * Vector3(0, 0, 5));

			// 弾を作成
			auto bulletObj = Instantate("Bullet", pos, rot);
			auto renderer = bulletObj->AddComponent<MeshRenderer>();
			auto homingBullet = bulletObj->AddComponent<HomingBullet>();
			ShotWeapon::Bullet* bullet = &rifle->bullet;
			renderer->mesh = bullet->mesh;
			renderer->shader = bullet->shader;
			homingBullet->damage = bullet->damage;
			homingBullet->downPower = bullet->downPower;
			homingBullet->speed = bullet->speed;
			homingBullet->homingSpeed = bullet->homingPower;

			// 距離によって誘導をつける
			if (HomingCheck())
			{
				homingBullet->SetTargetMs(GetTargetMs());
			}

			// 撃った
			rifle->isShot = true;
		}

		// 射撃アニメーションが終われば射撃状態を解除する
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			// アニメーションを再生
			if (anim->GetAnimationClip()->name == "Rifle.Shot.Idle.F" || anim->GetAnimationClip()->name == "Rifle.Shot.Idle.B" ||
				anim->GetAnimationClip()->name == "Rifle.Shot.Idle.R" || anim->GetAnimationClip()->name == "Rifle.Shot.Idle.L" ||
				anim->GetAnimationClip()->name == "Rifle.Shot.Idle.FR" || anim->GetAnimationClip()->name == "Rifle.Shot.Idle.FL")
			{
				anim->SetAnimation("Idle.Rifle");
				anim->Play();
				rb->isGravity = true;
			}
			else if (anim->GetAnimationClip()->name == "Rifle.Shot.Run.F" ||
				anim->GetAnimationClip()->name == "Rifle.Shot.Run.R" || anim->GetAnimationClip()->name == "Rifle.Shot.Run.L" ||
				anim->GetAnimationClip()->name == "Rifle.Shot.Run.FR" || anim->GetAnimationClip()->name == "Rifle.Shot.Run.FL")
			{
				anim->SetAnimation("Run.Rifle", true);
				anim->Play();
			}
			else if (anim->GetAnimationClip()->name == "Rifle.Shot.Dash.F" ||
				anim->GetAnimationClip()->name == "Rifle.Shot.Dash.R" || anim->GetAnimationClip()->name == "Rifle.Shot.Dash.L")
			{
				anim->SetAnimation("Dash.Rifle");
				anim->Play();
			}

			rifle->isNow = false;
			rifle->isShot = false;
			rifle->isStopShot = false;
		}
	}
}

/**
* 攻撃2(バズーカ)
*/
void Gundam::Action2(bool attackKey)
{
	// 攻撃入力があれば
	if (attackKey)
	{
		if (rifle->isNow || sable->isNow || moveParamater.step.isNow)
		{
			return;
		}

		// バズーカの弾があるなら射撃
		if (bazooka->amo > 0 && !bazooka->isNow)
		{
			// 持っている武装をライフルにする
			handWeapon = HandWeapon::Rifle;

			// ターゲットがいれば
			if (GetTargetMs())
			{
				// ターゲットが自分から見てどの方向にいるか調べる
				Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
				float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());

				// 重力を使わない
				rb->isGravity = false;
				rb->velocity = Vector3(0);

				// 相手の逆方向を向く
				GetTransform()->rotation = Quaternion::LookRotation(directionToTarget * Vector3(1, 0, 1));
			}

			// アニメーションを再生
			anim->SetAnimation("Bazooka.Shot");
			anim->Play();

			// 射撃中
			bazooka->isNow = true;
		}
	}
	// 射撃中
	if (bazooka->isNow)
	{
		if (!bazooka->isShot)
		{
			boostParamater.chageLock = true;
			boostParamater.current -= 30 * Time::DeltaTime();
		}
		if (anim->time >= 0.4f && !bazooka->isShot)
		{

			audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::bazookaShot);
			audioSources[AudioIndex::otherSound]->Play();

			// 残弾を減らす
			bazooka->amo -= 1;

			// 弾の生成位置を計算
			auto pos = GetTransform()->position + (GetTransform()->rotation * Vector3(0.3f, 0, 5));

			// 弾を作成
			auto bulletObj = Instantate("Bullet", pos, GetTransform()->rotation);
			auto renderer = bulletObj->AddComponent<MeshRenderer>();
			auto homingBullet = bulletObj->AddComponent<HomingBullet>();
			ShotWeapon::Bullet* bullet = &bazooka->bullet;
			renderer->mesh = bullet->mesh;
			renderer->shader = bullet->shader;
			renderer->shadowShader = bullet->shadowShader;
			homingBullet->damage = bullet->damage;
			homingBullet->downPower = bullet->downPower;
			homingBullet->speed = bullet->speed;
			homingBullet->homingSpeed = bullet->homingPower;

			// 反動で後ろに動かす
			GetTransform()->position += GetTransform()->Forward() * -0.5f;

			// 距離によって誘導をつける
			if (HomingCheck())
			{
				homingBullet->SetTargetMs(GetTargetMs());
			}

			// 撃った
			bazooka->isShot = true;
		}

		// 射撃アニメーションが終われば射撃状態を解除する
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			// アニメーションを再生
			if (anim->GetAnimationClip()->name == "Bazooka.Shot")
			{
				anim->SetAnimation("Idle.Rifle");
				anim->Play();
				rb->isGravity = true;
			}
			BoostCheck();
			bazooka->isNow = false;
			bazooka->isShot = false;
		}
	}
}

/**
* 攻撃3(ビームサーベル)
*
* @param acttion3Btn アクションボタン3の状態
*/
void Gundam::Action3(bool acttion3Btn)
{
	if (acttion3Btn)
	{
		if (rifle->isNow || bazooka->isNow || moveParamater.step.isNow)
		{
			return;
		}
		if (!sable->isNow)
		{
			// サーベル行動中にする
			sable->isNow = true;
			// 重力を受けなくする
			rb->isGravity = false;
			rb->velocity = Vector3::zero;

			// ブーストエネルギーのチャージをロックする
			boostParamater.chageLock = true;

			// ターゲットとの距離が赤ロック距離なら
			if (HomingCheck())
			{
				// 持っている武装をサーベルにする
				handWeapon = HandWeapon::Sable;

				// サーベル移動状態にする
				sable->move.isNow = true;

				// 攻撃し始めた位置を格納
				sable->move.attackStartPos = GetTransform()->position;

				// 誘導あり
				sable->isHoming = true;

				sable->targetPos = &GetTargetMs()->GetTransform()->position;

				// アニメーションを再生
				anim->SetAnimation("Sable.Move");
				anim->Play();
			}
			else
			{
				// 持っている武器がサーベルじゃなければ
				if (handWeapon != HandWeapon::Sable)
				{
					// 持っている武装をサーベルにする
					handWeapon = HandWeapon::Sable;

					// 範囲外だとサーベル抜刀状態にする
					sable->isGet = true;

					// アニメーションを再生
					anim->SetAnimation("Sable.Get");
					anim->Play();
				}
				else
				{
					// サーベル移動状態にする
					sable->move.isNow = true;

					// 攻撃し始めた位置を格納
					sable->move.attackStartPos = GetTransform()->position;

					// 誘導無し
					sable->isHoming = false;

					sable->targetPos = &GetTargetMs()->GetTransform()->position;

					// アニメーションを再生
					anim->SetAnimation("Sable.Move");
					anim->Play();
				}
			}
		}
		// サーベル行動中
		else
		{
			// アニメーションがコンボ受付時間なら攻撃2につなげる
			if (sable->attack1.isNow && anim->GetAnimationClip()->name == "Sable.Attack1")
			{
				if (anim->time >= 0.2f && anim->time <= 0.5f)
				{
					sable->attack2.isNow = true;
				}
			}
			// アニメーションがコンボ受付時間なら攻撃3につなげる
			else if (sable->attack2.isNow && anim->GetAnimationClip()->name == "Sable.Attack2")
			{
				if (anim->time >= 0.2f && anim->time <= 0.5f)
				{
					sable->attack3.isNow = true;
				}
			}
		}
	}
	// サーベル行動中
	if (sable->isNow)
	{
		// サーベル抜刀状態
		if (sable->isGet)
		{
			// アニメーションが終われば
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// サーベル状態を終了
				sable->isNow = false;
				// サーベル取得状態を終了
				sable->isGet = false;
				// 重力を復活
				rb->isGravity = true;

				// アニメーションを再生
				anim->SetAnimation(Animation::idleSable);
				anim->Play();
			}
		}
		// サーベル移動状態
		else if (sable->move.isNow)
		{
			// 向いてる方向に進む
			GetTransform()->position += sable->move.speed * GetTransform()->Forward() * Time::DeltaTime();

			// エネルギーを消費
			boostParamater.current -= sable->move.useEnergy * Time::DeltaTime();
			boostParamater.chageLock = true;

			// 移動距離を計算
			float moveDistance = Mathf::Abs(Vector3::Distance(GetTransform()->position, sable->move.attackStartPos));

			// 誘導あり
			if (sable->isHoming)
			{
				// ターゲットの方向を取得
				Vector3 directionToTarget = *sable->targetPos - GetTransform()->position;

				// ターゲットの方向を向ける
				GetTransform()->rotation = Quaternion::LookRotation(directionToTarget);

				// 一定以上進むか敵との距離が近ければ攻撃一段階目にする
				if (moveDistance >= sable->move.useHomingDistanceMax || GetDistance() <= sable->move.attackDistance)
				{
					// サーベル移動状態を終了
					sable->move.isNow = false;

					// サーベル攻撃一段階目にする
					sable->attack1.isNow = true;

					// 効果音を鳴らす
					audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::sableAttack);
					audioSources[AudioIndex::otherSound]->Play();

					// アニメーションを再生
					anim->SetAnimation("Sable.Attack1");
					anim->Play();
				}
			}
			else
			{
				// 一定以上進めば攻撃一段階目にする
				if (moveDistance >= sable->move.noHomingDistanceMax)
				{
					// サーベル移動状態を終了
					sable->move.isNow = false;

					// サーベル攻撃一段階目にする
					sable->attack1.isNow = true;

					// 効果音を鳴らす
					audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::sableAttack);
					audioSources[AudioIndex::otherSound]->Play();

					// アニメーションを再生
					anim->SetAnimation("Sable.Attack1");
					anim->Play();
				}

			}
		}
		// サーベル攻撃1段階目中
		else if (sable->attack1.isNow)
		{
			// アニメーションの時間が移動時間内なら
			if (anim->time < sable->attack1.moveTime)
			{
				// 誘導あり
				if (sable->isHoming)
				{
					// 敵との距離が攻撃距離なら
					if (GetDistance() > sable->move.attackDistance)
					{
						// 向いている方向に進む
						GetTransform()->position += sable->attack1.speed * GetTransform()->Forward() * Time::DeltaTime();
					}
				}
				// 誘導無し
				else
				{
					// 向いている方向に進む
					GetTransform()->position += sable->attack1.speed * GetTransform()->Forward() * Time::DeltaTime();
				}
			}

			// アニメーションが攻撃時間なら
			if (anim->time > sable->attack1.slashTime && !sable->attack1.isSlash)
			{
				// 攻撃判定を作成
				auto slashObj = Instantate("Slash", Vector3(0, 0, 10));
				slashObj->GetTransform()->SetParent(GetTransform());
				auto slash = slashObj->AddComponent<BaseSlash>();
				slash->damage = sable->attack1.damage;
				slash->downPower = sable->attack1.downPower;
				slash->destoryTime = sable->attack1.destoryTime;

				// 攻撃判定作った
				sable->attack1.isSlash = true;
			}

			// サーベル攻撃２段階目の状態ならコンボさせる
			if (anim->time >= 0.5f && sable->attack2.isNow)
			{
				// 誘導ありなら
				if (sable->isHoming)
				{
					// ターゲットの方向を取得
					Vector3 directionToTarget = *sable->targetPos - GetTransform()->position;
					GetTransform()->rotation = Quaternion::LookRotation(directionToTarget);
				}
				// サーベル攻撃１状態を解除
				sable->attack1.isNow = false;
				sable->attack1.isSlash = false;

				// 効果音を鳴らす
				audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::sableAttack);
				audioSources[AudioIndex::otherSound]->Play();

				// アニメーションを再生
				anim->SetAnimation("Sable.Attack2");
				anim->Play();

			}

			// アニメーションが終われば
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// サーベル攻撃終了
				SableAttackFailded(sable->attack1);
			}
		}
		// サーベル攻撃2段階目中
		else if (sable->attack2.isNow)
		{
			// アニメーションの時間が移動時間内なら
			if (anim->time < sable->attack2.moveTime)
			{
				// 誘導あり
				if (sable->isHoming)
				{
					// 敵との距離が攻撃距離なら
					if (GetDistance() > sable->move.attackDistance)
					{
						// 向いている方向に進む
						GetTransform()->position += sable->attack2.speed * GetTransform()->Forward() * Time::DeltaTime();
					}
				}
				// 誘導無し
				else
				{
					// 向いている方向に進む
					GetTransform()->position += sable->attack2.speed * GetTransform()->Forward() * Time::DeltaTime();
				}
			}

			// アニメーションが攻撃時間なら
			if (anim->time > sable->attack2.slashTime && !sable->attack2.isSlash)
			{
				// 攻撃判定を作成
				auto slashObj = Instantate("Slash", Vector3(0, 0, 10));
				slashObj->GetTransform()->SetParent(GetTransform());
				auto slash = slashObj->AddComponent<BaseSlash>();
				slash->damage = sable->attack2.damage;
				slash->downPower = sable->attack2.downPower;
				slash->destoryTime = sable->attack2.destoryTime;

				// 攻撃判定作った
				sable->attack2.isSlash = true;
			}

			// サーベル攻撃２段階目の状態ならコンボさせる
			if (anim->time >= 0.5f && sable->attack3.isNow)
			{
				// 誘導状態なら
				if (sable->isHoming)
				{
					// ターゲットの方向を取得
					Vector3 directionToTarget = *sable->targetPos - GetTransform()->position;
					GetTransform()->rotation = Quaternion::LookRotation(directionToTarget);
				}

				// サーベル攻撃2状態を解除
				sable->attack2.isNow = false;
				sable->attack2.isSlash = false;

				// 効果音を鳴らす
				audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::sableAttack);
				audioSources[AudioIndex::otherSound]->Play();

				// アニメーションを再生
				anim->SetAnimation("Sable.Attack3");
				anim->Play();
			}

			// アニメーションが終われば
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// サーベル攻撃終了
				SableAttackFailded(sable->attack2);
			}
		}
		// サーベル攻撃3段階目中
		else if (sable->attack3.isNow)
		{
			// アニメーションの時間が移動時間内なら
			if (anim->time < sable->attack3.moveTime)
			{
				// 誘導あり
				if (sable->isHoming)
				{
					// 敵との距離が攻撃距離なら
					if (GetDistance() > sable->move.attackDistance)
					{
						// 向いている方向に進む
						GetTransform()->position += sable->attack3.speed * GetTransform()->Forward() * Time::DeltaTime();
					}
				}
				// 誘導無し
				else
				{
					// 向いている方向に進む
					GetTransform()->position += sable->attack3.speed * GetTransform()->Forward() * Time::DeltaTime();
				}
			}

			// アニメーションが攻撃時間なら
			if (anim->time > sable->attack3.slashTime && !sable->attack3.isSlash)
			{
				// 攻撃判定を作成
				auto slashObj = Instantate("Slash", Vector3(0, 0, 10));
				slashObj->GetTransform()->SetParent(GetTransform());
				auto slash = slashObj->AddComponent<BaseSlash>();
				slash->damage = sable->attack3.damage;
				slash->downPower = sable->attack3.downPower;
				slash->destoryTime = sable->attack3.destoryTime;

				// 攻撃判定作った
				sable->attack3.isSlash = true;
			}

			// アニメーションが終われば
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// サーベル攻撃終了
				SableAttackFailded(sable->attack3);
			}
		}
	}
}

/*
* ビームサーベル攻撃終了
*/
void Gundam::SableAttackFailded(Sable::Attack& attack)
{
	// サーベル攻撃状態を解除
	sable->isNow = false;

	// 攻撃状態を解除
	attack.isNow = false;

	attack.isSlash = false;

	BoostCheck();
	// 重力を復活
	rb->isGravity = true;

	// 姿勢を正す
	GetTransform()->rotation = Quaternion::LookRotation(GetTransform()->Forward() * Vector3(1, 0, 1));

	// アニメーションを再生
	anim->SetAnimation("Idle.Sable");
	anim->Play();
}

/**
* ステップ
*/
void Gundam::Step(bool stepBtm, const Vector2& moveAxis)
{
	if (stepBtm)
	{
		if (sable->isGet || sable->attack1.isNow || sable->attack2.isNow || sable->attack3.isNow)
		{
			return;
		}

		if (moveAxis != Vector2::zero && !moveParamater.step.isNow)
		{
			moveParamater.step.isNow = true;
			rb->isGravity = false;
			boostParamater.chageLock = true;
			auto cameraTrs = GetCameraTransform();

			// カメラの方向から、X-Z単位ベクトル(正規化)を取得
			Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
			Vector3 moveFoward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

			Vector3 perendicular = Vector3::Cross(moveFoward.Normalized(), GetTransform()->Forward());
			float dot = Vector3::Dot(moveFoward.Normalized(), GetTransform()->Forward());
			// サーベル攻撃状態をだった場合
			if (sable->isNow)
			{
				sable->isNow = false;
				sable->isGet = false;
				sable->attack1.isNow = false;
				sable->attack1.isSlash = false;
				sable->attack2.isNow = false;
				sable->attack2.isSlash = false;
				sable->attack3.isNow = false;
				sable->attack3.isSlash = false;
			}


			if (dot > 0.7f)
			{
				anim->SetAnimation(Animation::stepRifleF);
				anim->Play();
			}
			else if (dot < -0.7f)
			{
				anim->SetAnimation(Animation::stepRifleB);
				anim->Play();
			}
			else
			{
				if (perendicular.y < 0)
				{
					anim->SetAnimation(Animation::stepRifleR);
					anim->Play();
				}
				else if (perendicular.y > 0)
				{
					anim->SetAnimation(Animation::stepRifleL);
					anim->Play();
				}
			}
			moveParamater.step.direction = moveFoward;
		}
	}
	if (moveParamater.step.isNow)
	{

		GetTransform()->position += moveParamater.step.speed * moveParamater.step.direction * Time::DeltaTime();
		boostParamater.current -= moveParamater.step.useEnergy * Time::DeltaTime();
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			moveParamater.step.isNow = false;
			rb->isGravity = true;
			BoostCheck();
			if (handWeapon == HandWeapon::Rifle)
			{
				anim->SetAnimation(Animation::idleRifle);
				anim->Play();
			}
			else
			{
				anim->SetAnimation(Animation::idleSable);
				anim->Play();
			}
		}
	}
}

/**
* ダメージ
*
* @param damage ダメージ情報
*/
void Gundam::Damage(const DamageInfo& damageInfo)
{
	if (blowAway.isNow || isDown || isRespon || isDownCancel)
	{
		return;
	}

	// 与えられたダメージの方向を計算
	Vector3 directionToTarget = damageInfo.direction;
	float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());

	// 体力を減らす
	baseParamater.hp -= static_cast<int>(damageInfo.damage);
	downValue += damageInfo.downPower;

	// ダッシュ状態
	if (moveParamater.dash.isNow)
	{
		moveParamater.dash.isNow = false;
	}
	// ジャンプ状態
	if (moveParamater.jump.isNow)
	{
		moveParamater.jump.isNow = false;
	}
	// ライフル状態だった場合
	if (rifle->isNow)
	{
		rifle->isNow = false;
		rifle->isShot = false;
		rifle->isStopShot = false;
	}
	// バズーカ状態だった場合
	if (bazooka->isNow)
	{
		bazooka->isNow = false;
		bazooka->isShot = false;
	}
	// サーベル攻撃状態をだった場合
	if (sable->isNow)
	{
		sable->isNow = false;
		sable->isGet = false;
		sable->attack1.isNow = false;
		sable->attack1.isSlash = false;
		sable->attack2.isNow = false;
		sable->attack2.isSlash = false;
		sable->attack3.isNow = false;
		sable->attack3.isSlash = false;
	}
	boostParamater.chageLock = false;

	// 通常ダメージアクション
	if (downValue < 100)
	{
		// 前方
		if (dot > 0)
		{
			GetTransform()->rotation = Quaternion::LookRotation(directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * -1.0f;

			anim->SetAnimation("Damage.Rifle.F");
			anim->Play();
		}
		// 後方
		else
		{
			GetTransform()->rotation = Quaternion::LookRotation(-directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * 1.0f;

			anim->SetAnimation("Damage.Rifle.B");
			anim->Play();
		}

		// 重力を無し
		rb->isGravity = false;
		rb->velocity = Vector3::zero;

		// ダメージ状態にする
		isDamage = true;
	}
	// ダウン状態
	else
	{
		// 前方
		if (dot > 0)
		{
			GetTransform()->rotation = Quaternion::LookRotation(directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * -1.0f;

			anim->SetAnimation("BlowAway.Rifle.F");
			anim->Play();
		}
		// 後方
		else
		{
			GetTransform()->rotation = Quaternion::LookRotation(-directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * 1.0f;

			anim->SetAnimation("BlowAway.Rifle.B");
			anim->Play();
		}
		rb->gravityScale = 3;
		rb->isGravity = true;
		blowAway.timer = 0;
		blowAway.isNow = true;
		downValue = 0;
	}

}

/**
* 生き返る
*
* @param removePos	生き返る位置
* @param hpCut		体力のカット率
*/
void Gundam::Respon(const Vector3& removePos, float hpCut)
{
	// 蘇生位置を設定
	GetTransform()->position = removePos;

	// ステータスの設定
	baseParamater.hp = baseParamater.hpMax * hpCut;
	boostParamater.current = boostParamater.max;

	// 武装の初期化
	rifle->Initialize();
	bazooka->Initialize();
	// サーベル攻撃状態をだった場合
	if (sable->isNow)
	{
		sable->isNow = false;
		sable->isGet = false;
		sable->attack1.isNow = false;
		sable->attack1.isSlash = false;
		sable->attack2.isNow = false;
		sable->attack2.isSlash = false;
		sable->attack3.isNow = false;
		sable->attack3.isSlash = false;
	}

	// 死亡状態を解除
	downValue = 0;
	blowAway.isNow = false;
	isDamage = false;
	isDown = false;
	isDeath = false;
	rb->isGravity = true;
	boostParamater.chageLock = false;

	rb->velocity = Vector3::zero;
	renderer->enabled = true;

	// ターゲットの方向を取得
	Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
	Quaternion rot = Quaternion::LookRotation(directionToTarget);
	// 相手の逆方向を向く
	GetTransform()->rotation = Quaternion::LookRotation(directionToTarget * Vector3(1, 0, 1));

	anim->SetAnimation("Idle.Rifle");
	anim->Play();
	responTimer = responTime;
	isRespon = true;
}
