/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "Bullet.h"
#include "DamageInfo.h"
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
	resManager->LoadTga("Gundam/BeumRifleIcon", "Application/Res/Ms/Gundam/UI/BeumRifleIcon.tga");
	resManager->LoadObj("Gundam/BazookaBullet", "Application/Res/Ms/Gundam/Model/BazookaBullet.obj");
	resManager->LoadTga("Gundam/BazookaIcon", "Application/Res/Ms/Gundam/UI/BazookaIcon.tga");

	// 描画コンポーネントを追加
	auto renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = resManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// 重力を追加
	rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->gravityScale = 2;

	// コライダーを追加
	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = 2.4f;
	col->ceneter = Vector3(0, -2.7f, 0);
	auto col2 = OwnerObject()->AddComponent<SphereCollider>();
	col2->radius = 2.5f;
	col2->ceneter = Vector3(0, -0.4f, -0.2f);

	// アニメータを追加
	anim = OwnerObject()->AddComponent<Animator>();
	anim->animationClips = renderer->glTFfile->animationClips;

	// 最初のアニメーションを追加
	anim->SetAnimation("Idle.Rifle", true);
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
	moveParamater.speed = 20.0f;
	moveParamater.rotationSpeed = 0.05f;

	// ダッシュ
	moveParamater.dash.speed = 40.0f;
	moveParamater.dash.rotationSpeed = 0.01f;
	moveParamater.dash.useEnergy = -30.0f;

	// ジャンプ
	moveParamater.jump.power = 10.0f;
	moveParamater.jump.speed = 10.0f;
	moveParamater.jump.rotationSpeed = 0.05f;
	moveParamater.jump.useEnergy = -30.0f;

	// バズーカの生成
	bazooka = std::make_shared<Bazooka>();
	bazooka->name = "Bazooka";
	bazooka->amoMax = 3;
	bazooka->amo = bazooka->amoMax;
	bazooka->damage = 99.0f;
	bazooka->downPower = 100;
	bazooka->homingPower = 0.9f;
	bazooka->speed = 80.0f;
	bazooka->reloadTime = 4;
	bazooka->iconTexture = resManager->GetTexture("Gundam/BazookaIcon");
	bazooka->mesh = resManager->GetStaticMesh("Gundam/BazookaBullet");
	bazooka->shader = resManager->GetShader(DefalutShader::Standard3D);
	bazooka->shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
	numWeapons.push_back(bazooka);

	// ライフルの生成
	rifle = std::make_shared<Rifle>();
	rifle->name = "BeumRifle";
	rifle->amoMax = 7;
	rifle->amo = rifle->amoMax;
	rifle->damage = 70.0f;
	rifle->downPower = 40;
	rifle->homingPower = 0.09f;
	rifle->speed = 200.0f;
	rifle->reloadTime = 3;
	rifle->iconTexture = resManager->GetTexture("Gundam/BeumRifleIcon");
	rifle->mesh = resManager->GetStaticMesh("Gundam/BeumRifleBullet");
	rifle->shader = resManager->GetShader(DefalutShader::Unlit);
	numWeapons.push_back(rifle);

}

/**
* 毎フレーム実行
*/
void Gundam::Update()
{
	// 死んでいれば何もしない
	if (isDeath)
	{
		return;
	}


	// HPがなければ死亡状態にする
	if (hp <= 0)
	{
		// 死亡状態にする
		isDeath = true;
		return;
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

			// ライフル
			{
				rifle->isNow = false;
				rifle->isShot = false;
				rifle->isStopShot = false;
			}

			// バズーカ
			{
				bazooka->isNow = false;
				bazooka->isShot = false;
			}
			// アニメーションを再生
			if (anim->GetAnimationClip()->name == "Damage.Rifle")
			{
				anim->SetAnimation("Idle.Rifle");
				anim->Play();
			}
		}
	}

	// 地面についているとき
	if (rb->IsGround() && !boostEnergyChageLock)
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
	// ダメージ状態なら何もしない
	if (isDamage)
	{
		return;
	}

	// カメラの位置を取得
	auto cameraTrs = GetCameraTransform();
	if (!cameraTrs)
	{
		return;
	}

	// ジャンプ・ダッシュ・ライフルの移動禁止・バズーカ状態なら移動しない
	if (moveParamater.dash.isNow || moveParamater.jump.isNow || rifle->isStopShot || bazooka->isNow)
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
			if (moveAxis != Vector2::zero)
			{
				// 歩くアニメーションを再生する
				anim->SetAnimation("Run.Rifle", true);
				anim->Play();
			}
			else
			{
				// 移動入力がなければIdleアニメーションを再生する
				anim->SetAnimation("Idle.Rifle", true);
				anim->Play();
			}
		}
	}
}


/**
* ジャンプ
*/
void Gundam::Jump(bool isJump, const Vector2& moveAxis)
{
	// ダメージ状態なら何もしない
	if (isDamage)
	{
		return;
	}

	// ダッシュ・ライフルの移動禁止・バズーカ状態ならジャンプしない
	if (moveParamater.dash.isNow || rifle->isStopShot || bazooka->isNow)
	{
		return;
	}

	// ジャンプ入力があれば
	if (isJump)
	{
		// エネルギーがあればジャンプさせる
		if (boostEnergy > 0)
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

			// ジャンプアニメーションを再生
			if (!moveParamater.jump.isNow)
			{
				if (rb->IsGround())
				{
					anim->SetAnimation("Jump.Rifle.Ground");
				}
				else
				{

					anim->SetAnimation("Jump.Rifle");
				}
				anim->Play();
			}

			// 重力の速度を0にして　
			rb->velocity = Vector3(0);
			// 上昇
			GetTransform()->position.y += moveParamater.jump.power * Time::DeltaTime();
			// エネルギーを消費
			boostEnergy += moveParamater.jump.useEnergy * Time::DeltaTime();

			//ブーストエネルギーの回復をロック
			boostEnergyChageLock = true;

			// ジャンプ状態に変更
			moveParamater.jump.isNow = true;
		}
		else
		{
			// エネルギーがなくなればジャンプ状態を終わる
			if (moveParamater.jump.isNow)
			{
				// エネルギーチャージのロックを解除
				boostEnergyChageLock = false;
				// エネルギーチャージのタイマーを代入
				boostEnergyChageTimer = boostEnergyChageOverHeatStartTime;

				anim->SetAnimation("Idle.Rifle", true);
				anim->Play();

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
			boostEnergyChageLock = false;
			// エネルギーチャージのタイマーを代入
			boostEnergyChageTimer = boostEnergyChageStartTime;

			if (!rifle->isNow)
			{
				// 通常状態のアニメーションに変更
				anim->SetAnimation("Idle.Rifle", true);
				anim->Play();
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
	// ダメージ状態なら何もしない
	if (isDamage)
	{
		return;
	}

	// ライフルの停止・バズーカ状態ならダッシュしない
	if (rifle->isStopShot || bazooka->isNow)
	{
		return;
	}

	if (isDash)
	{
		// エネルギーがあればダッシュさせる
		if (boostEnergy > 0)
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
			boostEnergy += moveParamater.dash.useEnergy * Time::DeltaTime();

			// 射撃状態ならアニメーションをキャンセル
			if (!rifle->isNow)
			{
				if (!moveParamater.dash.isNow || anim->GetAnimationClip()->name != "Dash.Rifle")
				{
					// ダッシュアニメーションを再生
					anim->SetAnimation("Dash.Rifle", true);
					anim->Play();
				}
			}
			// ダッシュ中に変更
			moveParamater.dash.isNow = true;
			// エネルギーチャージをロック
			boostEnergyChageLock = true;
		}
		else
		{
			// エネルギーがなくなればダッシュ状態を終わる
			if (moveParamater.dash.isNow)
			{
				rb->isVelocity = true;
				// エネルギーチャージのロックを解除
				boostEnergyChageLock = false;
				// エネルギーチャージのタイマーを代入
				boostEnergyChageTimer = boostEnergyChageOverHeatStartTime;

				if (!rifle->isNow)
				{
					// 通常状態のアニメーションに変更
					anim->SetAnimation("Idle.Rifle", true);
					anim->Play();
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
			boostEnergyChageLock = false;
			// エネルギーチャージのタイマーを代入
			boostEnergyChageTimer = boostEnergyChageStartTime;

			if (!rifle->isNow)
			{
				// 通常状態のアニメーションに変更
				anim->SetAnimation("Idle.Rifle", true);
				anim->Play();
			}

			// ダッシュ状態を終了
			moveParamater.dash.isNow = false;
		}
	}
}

/**
* 攻撃(ビームライフル)
*/
void Gundam::Attack1(bool attackKey)
{
	// ダメージ状態なら何もしない
	if (isDamage)
	{
		return;
	}

	// 攻撃入力があれば
	if (attackKey)
	{
		// バズーカ攻撃状態ならライフル攻撃をしない
		if (bazooka->isNow)
		{
			return;
		}

		// ビームライフルの弾があれば射撃
		if (rifle->amo > 0 && !rifle->isNow)
		{
			// ターゲットが自分から見てどの方向にいるか調べる
			Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
			Vector3 perendicular = Vector3::Cross(directionToTarget, GetTransform()->Forward());
			float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());

			// アニメーションを再生

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
			else if (anim->GetAnimationClip()->name == "Idle.Rifle" || anim->GetAnimationClip()->name == "Jump.Rifle")
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
			else if (anim->GetAnimationClip()->name == "Run.Rifle")
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

			// 射撃中
			rifle->isNow = true;
		}
	}
	// 射撃状態
	if (rifle->isNow)
	{
		if (anim->time >= 0.2f && !rifle->isShot)
		{
			// 残弾を減らす
			rifle->amo -= 1;

			// ターゲットの方向のトランスフォームを作成
			TransformPtr trs = std::make_shared<Transform>();
			trs->position = GetTransform()->position;
			trs->rotation = GetTransform()->rotation;
			trs->LookAt(GetTargetMs()->GetTransform());

			// 弾の生成位置を計算
			auto pos = GetTransform()->position + (trs->rotation * Vector3(0, 0, 5));

			// 弾を作成
			auto bullet = Instantate("Bullet", pos, trs->rotation);
			auto renderer = bullet->AddComponent<MeshRenderer>();
			renderer->mesh = rifle->mesh;
			renderer->shader = rifle->shader;
			auto bulletMove = bullet->AddComponent<Bullet>();
			bulletMove->downPower = rifle->downPower;
			bulletMove->speed = rifle->speed;
			bulletMove->rotationSpeed = rifle->homingPower;
			bulletMove->damage = rifle->damage;

			// 距離によって誘導をつける
			if (GetDistance() < redLookDistace)
			{
				bulletMove->targetMS = GetTargetMs();
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
void Gundam::Attack2(bool attackKey)
{
	// ダメージ状態なら何もしない
	if (isDamage)
	{
		return;
	}

	// 攻撃入力があれば
	if (attackKey)
	{
		// ライフル攻撃状態ならバズーカ攻撃をしない
		if (rifle->isNow)
		{
			return;
		}

		// バズーカの弾があるなら射撃
		if (bazooka->amo > 0 && !bazooka->isNow)
		{
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
		if (anim->time >= 0.4f && !bazooka->isShot)
		{
			// 残弾を減らす
			bazooka->amo -= 1;

			// ターゲットの方向のトランスフォームを作成
			TransformPtr trs = std::make_shared<Transform>();
			trs->position = GetTransform()->position;
			trs->rotation = GetTransform()->rotation;
			trs->LookAt(GetTargetMs()->GetTransform());

			// 弾の生成位置を計算
			auto pos = GetTransform()->position + (GetTransform()->rotation * Vector3(0.3f, 0, 5));

			// 弾を作成
			auto bullet = Instantate("Bullet", pos, trs->rotation);
			auto renderer = bullet->AddComponent<MeshRenderer>();
			renderer->mesh = bazooka->mesh;
			renderer->shader = bazooka->shader;
			renderer->shadowShader = bazooka->shadowShader;
			auto bulletMove = bullet->AddComponent<Bullet>();
			bulletMove->speed = bazooka->speed;
			bulletMove->downPower = bazooka->downPower;
			bulletMove->rotationSpeed = bazooka->homingPower;
			bulletMove->damage = bazooka->damage;

			// 反動で後ろに動かす
			GetTransform()->position += GetTransform()->Forward() * -0.5f;

			// 距離によって誘導をつける
			if (GetDistance() < redLookDistace)
			{
				bulletMove->targetMS = GetTargetMs();
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
			bazooka->isNow = false;
			bazooka->isShot = false;
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
	// 与えられたダメージの方向を計算
	Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
	float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());

	// 体力を減らす
	hp -= static_cast<int>(damageInfo.damage);

	// 通常ダメージアクション
	if (downValue < 100)
	{
		// 前方
		if (dot > 0)
		{
			GetTransform()->rotation = Quaternion::LookRotation(directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * -0.5f;

			anim->SetAnimation("Damage.Rifle.F");
			anim->Play();
		}
		// 後方
		else
		{
			GetTransform()->rotation = Quaternion::LookRotation(-directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * -0.5f;

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
	}

}

/**
* 生き返る
*
* @param removePos	生き返る位置
* @param hpCut		体力のカット率
*/
void Gundam::Remove(const Vector3& removePos, float hpCut)
{
	// 蘇生位置を設定
	GetTransform()->position = removePos;

	// ステータスの設定
	this->hp = hpMax * hpCut;
	this->boostEnergy = boostEnergyMax;

	// 武装の初期化
	rifle->Initialize();
	bazooka->Initialize();

	// 死亡状態を解除
	isDeath = false;

	rb->velocity = Vector3::zero;

	anim->SetAnimation("Idle.Rifle");
	anim->Play();
}
