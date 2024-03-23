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
* �����C�x���g
*/
void Gundam::Awake()
{
	// �G���W�����擾
	auto engine = GetGameObject()->GetEngine();

	// �R���C�_�[��ǉ�
	auto colllder = GetGameObject()->AddComponent<AabbCollider>();
	colllder->aabb = { Vector3(-1,-6.5f,-1), Vector3(1,1,1) };

	// �v���C���[���͂�ǉ�
	msInput = GetGameObject()->AddComponent<PlayerController>();

	// �����_���[��ǉ�
	renderer = GetGameObject()->AddComponent<GltfAnimatedMeshRenderer>();
	renderer->fileBuffer = engine->GetGltfFileBuffer();
	renderer->file = engine->LoadGltf("Application/Res/Gundam/Model/GundamGL.gltf");

	// �L�����N�^�[���[�u�����g��ǉ�
	characterMovement = GetGameObject()->AddComponent<CharacterMovement>();

	shotParameter.iconfileName = "Application/Res/Gundam/UI/BeumMagunamIcon.tga";
	shotParameter.maxAmo = 7;
	shotParameter.amo = shotParameter.maxAmo;

	numArmer.push_back(&shotParameter);
}

/**
* �X�^�[�g�C�x���g
*/
void Gundam::Start()
{
	// �A�j���[�V������ݒ�
	renderer->SetAnimation("MagunamIdle", false);
	renderer->Play();
	parameter.hpMax = 600;
	parameter.hp = parameter.hpMax;
	parameter.teum = 1;
}

/**
* �X�V�C�x���g 
*/
void Gundam::Update()
{
	auto engine = GetGameObject()->GetEngine();

	// �n�ʃ`���b�N
	GroundCheck();

	// �C���^�[�o���X�V
	IntervalUpdate();

	for (auto x : numArmer)
	{
		x->AmoReloadUpdate();
	}

	// �ړ�����
	Move();

	
	// �n�ʂɂ��Ă�����G�l���M�[��
	if (parameter.boostPower > 0 && state == State::None && isGrond)
	{
		parameter.boostPower -= powerHealSpeed * Time::deltaTime();
	}
	if (moveParameter.moveTimer > 0)
	{
		moveParameter.moveTimer -= Time::deltaTime();
	}

	// �X�e�[�g
	switch (state)
	{
	case Gundam::State::None:
		
		// �����Ԃ��}�O�i���̎�
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
			// �ړ����͂��Ȃ��Ƃ� || �n�ʂɂ��Ă��Ȃ��������
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
		// �����Ԃ��T�[�x���̎�
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

		// �ߐڍU��
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
		
		// �������U��
		if (msInput->shotBtn && shotParameter.timer <= 0 && shotParameter.amo > 0)
		{
			// ������Ԃ��}�O�i���ɂ���
			defaultWeapon = DefaultWeapon::Magunam;

			// �}�O�i���̒e�����炷
			shotParameter.amo -= 1;

			// �G�̈ʒu���擾
			Vector3 pos = playerManager->enemyMs->transform->position;
			auto rot = LookAt(transform->position, pos, Vector3::up);
			// �G�̕���������
			transform->rotation = Quaternion::RotationMatrixToQuaternio(Matrix3x3(rot));
			
			// �ˌ��̃C���^�[�o��
			shotParameter.timer = shotParameter.interval;

			// �e�𐶐�
			auto bullet = engine->Create<GameObject>("Bullet", transform->position + transform->rotation * shotParameter.shotPos, transform->rotation);
			auto magunamBullet = bullet->AddComponent<MagunamBullet>();
			bullet->tag = "PlayerBullet";
			magunamBullet->SetTargetTrs(playerManager->enemyMs->transform);
			magunamBullet->SetTeum(parameter.teum);
			if (playerManager->GetDistance() > attackParameter.shotDistance)
			{
				magunamBullet->SetHoming(false);
			}
			// ��Ԃ��ˌ��ɕύX
			state = State::Shot;
		}

		break;
	case Gundam::State::Jump:

		// �����Ԃ��}�O�i��
		if (defaultWeapon == DefaultWeapon::Magunam)
		{
			if (animState != AnimState::MagunamJump)
			{
				animState = AnimState::MagunamJump;
				renderer->SetAnimation("MagunamJump", false);
				renderer->Play();
			}
		}
		// �����Ԃ��T�[�x��
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

		// �����Ȃ���ˌ�
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
* �ړ�����
*/
void Gundam::Move()
{
	if (!cameraTrs || moveParameter.moveTimer > 0)
	{
		return;
	}
	// �J�����̕�������AX-Z�P�ʃx�N�g��(���K��)���擾
	Vector3 cameraForward = Vector3::Scale(cameraTrs->forward(), Vector3(1, 0, 1)).normalized();
	Vector3 moveForward = cameraForward * msInput->inputAxis.y + cameraTrs->right() * msInput->inputAxis.x;

	if (isGrond) 
	{
		// �i�s�����ɉ�]
		if (moveForward != Vector3::zero)
		{
			transform->rotation = Quaternion::Slerp(transform->rotation, Quaternion::LookRotation(moveForward), moveParameter.rotationSpeed);
		}
		if (msInput->inputAxis != Vector2::zero) 
		{
			// �I�u�W�F�N�g�̌����Ă�����ɐi��
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

		// �d�͂��I�t
		//characterMovement->isGravity = false;
		if (state == State::Jump) 
		{
			// �W�����v����
			Jump(moveForward);
		}
		if (state == State::Dash)
		{
			// �_�b�V������
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
				// �O�񉟂���Ă��Ȃ���Ή����ꂽ���Ƃɂ���
				if (!msInput->jumpBtnPush)
				{
					msInput->jumpBtnPush = true;
					state = State::Jump;
					msInput->jumpBtnTimer = 0;
				}
				else 
				{
					// �������ԓ��ɉ�����Ă���΃_�b�V������
					if (msInput->jumpBtnTimer <= 0.5)
					{
						state = State::Dash;
					}
				}
			}
		}
		else 
		{
			// �����ꂢ�Ȃ�
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
	// �ŏ��̈ړ��L�[�����Ă���Ύ��Ԍv��
	if (msInput->jumpBtnPush)
	{
		// ���Ԍv��
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
		// �����Ă�����ɏ����i��
		transform->position += transform->forward() * (moveParameter.speed / 2) * Time::deltaTime();
	}
	parameter.boostPower += 10.0f * Time::deltaTime();
	characterMovement->velocity.y = moveParameter.jumpPower;

	// �i�s�����ɉ�]
	if (moveForward != Vector3::zero) {
		transform->rotation = Quaternion::Slerp(transform->rotation, Quaternion::LookRotation(moveForward), moveParameter.rotationSpeed / 2);
	}
}

void Gundam::Dash(const Vector3& moveForward)
{
	characterMovement->velocity.y = 0;
	transform->position += transform->forward() * moveParameter.dashSpeed * Time::deltaTime();
	parameter.boostPower += 10.0f * Time::deltaTime();
	// �i�s�����ɉ�]
	if (moveForward != Vector3::zero)
	{
		transform->rotation = Quaternion::Slerp(transform->rotation, Quaternion::LookRotation(moveForward),0.01f);
	}
}

/**
* �C���^�[�o������
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
