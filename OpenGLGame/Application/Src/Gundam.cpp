/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "Bullet.h"
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;

/**
* �ŏ��Ɏ��s
*/
void Gundam::Awake()
{
	// ���\�[�X�}�l�[�W���[���擾
	auto resManager = ResouceManager::GetInstance();
	resManager->LoadObj("Gundam/BeumRifleBullet", "Application/Res/Ms/Gundam/Model/BeumRifleBullet.obj");

	// �`��R���|�[�l���g��ǉ�
	auto renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = resManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// �d�͂�ǉ�
	rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->gravityScale = 2;

	// �R���C�_�[��ǉ�
	auto col = OwnerObject()->AddComponent<AabbCollider>();
	col->min = Vector3(-1, -5.2f, -1);
	col->max = Vector3(1, 2.4f, 1);

	// �A�j���[�^��ǉ�
	anim = OwnerObject()->AddComponent<Animator>();
	anim->animationClips = renderer->glTFfile->animationClips;

	// �ŏ��̃A�j���[�V������ǉ�
	anim->SetAnimation("RifleIdle", true);
	anim->Play();

	// �X�e�[�^�X��ݒ�
	hpMax = 600;
	hp = hpMax;
	cost = 2000;
	boostEnergy = boostEnergyMax;

	// �U���̋���
	proximityDistance = 40.0f;
	redLookDistace = 90.0f;

	// �ړ��p�����[�^
	moveParamater.speed = 30.0f;
	moveParamater.rotationSpeed = 0.05f;

	// �_�b�V��
	moveParamater.dash.speed = 35.0f;
	moveParamater.dash.rotationSpeed = 0.01f;
	moveParamater.dash.useEnergy = -30.0f;

	// �W�����v
	moveParamater.jump.power = 10.0f;
	moveParamater.jump.speed = 10.0f;
	moveParamater.jump.rotationSpeed = 0.05f;
	moveParamater.jump.useEnergy = -30.0f;

	// �c�e�����ǉ�
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
* ���t���[�����s
*/
void Gundam::Update()
{
	// �n�ʂɂ��Ă���Ƃ�
	if (rb->IsGrounded() && !boostEnergyChageLock)
	{
		if (boostEnergyChageTimer <= 0)
		{
			// �u�[�X�g�G�l���M�[�������Ă�����
			if (boostEnergy < boostEnergyMax)
			{
				boostEnergy += boostEnergyChage * Time::DeltaTime();
			}
		}
		else
		{
			// �G�l���M�[�`���[�W�J�n�^�C�}�[�����炷
			boostEnergyChageTimer -= Time::DeltaTime();
		}
	}
	boostEnergy = Mathf::Clamp(boostEnergy, 0.0f, boostEnergyMax);
}

/**
* �ړ�
*
* @param moveAxis ���͎�
*/
void Gundam::Move(const Vector2& moveAxis)
{
	auto cameraTrs = GetCameraTransform();
	// �J�����̈ʒu��ݒ肳��Ă��Ȃ�
	if (!cameraTrs || moveParamater.dash.isNow || moveParamater.jump.isNow)
	{
		return;
	}

	// �J�����̕�������AX-Z�P�ʃx�N�g��(���K��)���擾
	Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
	Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

	if (rb->IsGrounded())
	{
		// �i�s�����ɉ�]
		if (moveForward != Vector3::zero)
		{
			GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
				Quaternion::LookRotation(moveForward), moveParamater.rotationSpeed);
		}
		if (moveAxis != Vector2::zero)
		{
			// �I�u�W�F�N�g�̌����Ă�����ɐi��
			GetTransform()->position += GetTransform()->Forward() * moveParamater.speed * Time::DeltaTime();

		}
		if (!rifle->isShot)
		{
			if (moveAxis != Vector2::zero)
			{
				// �����A�j���[�V������������
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
* CPU�̈ړ�
*/
void Gundam::CpuMove()
{
	if (rb->IsGrounded())
	{
		auto targetFoward = GetTargetMs()->GetTransform()->position * Vector3(1, 0, 1);
		auto targetRot = Matrix4x4::LookAt(GetTransform()->position * Vector3(1, 0, 1), targetFoward, Vector3::up);

		// �^�[�Q�b�g�̕������擾
		auto rot = GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
			Quaternion::RotationMatrixToQuaternion(targetRot), moveParamater.rotationSpeed);

		GetTransform()->rotation = Quaternion(rot.x, rot.y, rot.z, rot.w);

		// �O�����ɐi��
		GetTransform()->position += moveParamater.speed * GetTransform()->Forward() * Time::DeltaTime();

		// �����A�j���[�V������������
		anim->SetAnimation("RifleRun", true);
		anim->Play();
	}
}

/**
* �W�����v
*/
void Gundam::Jump(bool isJump, const Vector2& moveAxis)
{
	if (moveParamater.dash.isNow)
	{
		return;
	}
	if (isJump)
	{
		// �G�l���M�[�������
		if (boostEnergy > 0)
		{
			// �d�͂̑��x��0�ɂ��ā@
			rb->velocity.y = 0;

			auto cameraTrs = GetCameraTransform();
			// �J�����̕�������AX-Z�P�ʃx�N�g��(���K��)���擾
			Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
			Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

			// �i�s�����ɉ�]
			if (moveForward != Vector3::zero)
			{
				GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
					Quaternion::LookRotation(moveForward), moveParamater.jump.rotationSpeed);
			}
			if (moveAxis != Vector2::zero)
			{
				// �I�u�W�F�N�g�̌����Ă�����ɐi��
				GetTransform()->position += GetTransform()->Forward() * moveParamater.jump.speed * Time::DeltaTime();
			}

			// �㏸
			GetTransform()->position.y += moveParamater.jump.power * Time::DeltaTime();

			boostEnergy += moveParamater.jump.useEnergy * Time::DeltaTime();

			// �W�����v�����ŏ��ɃA�j���[�V������������
			if (!moveParamater.jump.isNow)
			{
				anim->SetAnimation("RifleJump");
				anim->Play();
			}
			moveParamater.jump.isNow = true;

			//�u�[�X�g�G�l���M�[�̉񕜂����b�N
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
* �_�b�V��
*/
void Gundam::Dash(bool isDash, const Vector2& moveAxis)
{
	if (isDash)
	{
		if (boostEnergy > 0)
		{
			rb->velocity.y = 0;
			auto cameraTrs = GetCameraTransform();
			// �J�����̈ʒu��ݒ肳��Ă��Ȃ�
			if (!cameraTrs)
			{
				return;
			}

			// �J�����̕�������AX-Z�P�ʃx�N�g��(���K��)���擾
			Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
			Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

			// �i�s�����ɉ�]
			if (moveForward != Vector3::zero)
			{
				GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
					Quaternion::LookRotation(moveForward), moveParamater.dash.rotationSpeed);
			}
			// �I�u�W�F�N�g�̌����Ă�����ɐi��
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
* �U��(�r�[�����C�t��)
*/
void Gundam::Attack1(bool attackKey)
{
	if (attackKey)
	{
		// �r�[�����C�t���̒e������Ƃ������ł�
		if (rifle->amo > 0 && !rifle->isShot)
		{
			// �c�e�����炷
			rifle->amo -= 1;

			// �^�[�Q�b�g�����Ă��炻���������
			if (GetTargetMs())
			{
				GetTransform()->LookAt(GetTargetMs()->GetTransform());
			}
			auto pos = GetTransform()->position + (GetTransform()->rotation * Vector3(0.5f, 0.8f, 11.0f));

			// �e���쐬
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
* �_���[�W
* 
* @param damage �^����_���[�W
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
