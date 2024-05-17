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
	resManager->LoadTga("Gundam/BeumRifleIcon", "Application/Res/Ms/Gundam/UI/BeumRifleIcon.tga");

	// �`��R���|�[�l���g��ǉ�
	auto renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = resManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// �d�͂�ǉ�
	rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->gravityScale = 2;

	// �R���C�_�[��ǉ�
	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = 2.4f;
	col->ceneter = Vector3(0, -2.7f, 0);
	auto col2 = OwnerObject()->AddComponent<SphereCollider>();
	col2->radius = 2.5f;
	col2->ceneter = Vector3(0, -0.4f, -0.2f);
	//col->min = Vector3(-3, -5.2f, -2);
	//col->max = Vector3(3, 2.4f, 2);

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
	moveParamater.speed = 35.0f;
	moveParamater.rotationSpeed = 0.05f;

	// �_�b�V��
	moveParamater.dash.speed = 40.0f;
	moveParamater.dash.rotationSpeed = 0.01f;
	moveParamater.dash.useEnergy = -30.0f;

	// �W�����v
	moveParamater.jump.power = 10.0f;
	moveParamater.jump.speed = 10.0f;
	moveParamater.jump.rotationSpeed = 0.05f;
	moveParamater.jump.useEnergy = -30.0f;

	// ���C�t���̐���
	rifle = std::make_shared<Rifle>();
	rifle->name = "BeumRifle";
	rifle->amoMax = 7;
	rifle->amo = rifle->amoMax;
	rifle->damage = 70.0f;
	rifle->homingPower = 0.05f;
	rifle->speed = 200.0f;
	rifle->reloadTime = 3;
	rifle->iconTexture = resManager->GetTexture("Gundam/BeumRifleIcon");
	rifle->mesh = resManager->GetStaticMesh("Gundam/BeumRifleBullet");
	rifle->shader = resManager->GetShader(DefalutShader::Unlit);
	numWeapons.push_back(rifle);
}

/**
* ���t���[�����s
*/
void Gundam::Update()
{
	// ����ł���Ή������Ȃ�
	if (isDeath)
	{
		return;
	}

	// HP���Ȃ���Ύ��S��Ԃɂ���
	if (hp <= 0)
	{
		anim->SetAnimation("RifleDown");
		anim->Play();

		// ���S��Ԃɂ���
		isDeath = true;
		return;
	}

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

	// �����[�h���X�V
	ReloadUpdate();


}

/**
* �����[�h�X�V
*/
void Gundam::ReloadUpdate()
{
	for (auto x : numWeapons)
	{
		// �e�������Ă���΃����[�h
		if (x->amo < x->amoMax)
		{
			x->reloadTimer += Time::DeltaTime();
			if (x->reloadTimer > x->reloadTime)
			{
				x->reloadTimer = 0;
				x->amo++;
			}
		}
	}
}

/**
* �ړ�
*
* @param moveAxis ���͎�
*/
void Gundam::Move(const Vector2& moveAxis)
{
	// �J�����̈ʒu���擾
	auto cameraTrs = GetCameraTransform();
	// �J�����̈ʒu���擾�ł��Ȃ���Ή������Ȃ�
	if (!cameraTrs)
	{
		return;
	}
	// �W�����v�ƃ_�b�V����ԂȂ牽�����Ȃ�
	if (moveParamater.dash.isNow || moveParamater.jump.isNow)
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
		if (!rifle->isNow)
		{
			if (moveAxis != Vector2::zero)
			{
				// �����A�j���[�V�������Đ�����
				anim->SetAnimation("RifleRun", true);
				anim->Play();
			}
			else
			{
				// �ړ����͂��Ȃ����Idle�A�j���[�V�������Đ�����
				anim->SetAnimation("RifleIdle", true);
				anim->Play();
			}
		}
	}
}

/**
* CPU�̈ړ�
*/
void Gundam::CpuMove(const Vector2& moveAxis)
{
	//if (rb->IsGrounded())
	//{
	//	// �W�����v�ƃ_�b�V����ԂȂ牽�����Ȃ�
	//	if (moveParamater.dash.isNow || moveParamater.jump.isNow)
	//	{
	//		return;
	//	}

	//	auto targetFoward = GetTargetMs()->GetTransform()->position * Vector3(1, 0, 1);
	//	auto targetRot = Matrix4x4::LookAt(GetTransform()->position * Vector3(1, 0, 1), targetFoward, Vector3::up);

	//	// �^�[�Q�b�g�̕���������
	//	GetTransform()->rotation = GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
	//		Quaternion::RotationMatrixToQuaternion(targetRot), moveParamater.rotationSpeed);

	//	// �O�����ɐi��
	//	GetTransform()->position += moveParamater.speed * GetTransform()->Forward() * Time::DeltaTime();

	//	if (!rifle->isNow)
	//	{
	//		// �����A�j���[�V�������Đ�����
	//		anim->SetAnimation("RifleRun", true);
	//		anim->Play();
	//	}
	//}

	// �J�����̕�������AX-Z�P�ʃx�N�g��(���K��)���擾
	//Vector3 cameraForward = GetTransform()->Forward() * Vector3(1, 0, 1).Normalized();
	Vector3 moveForward = GetTransform()->Forward() * moveAxis.y + GetTransform()->Right() * moveAxis.x;

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
		if (!rifle->isNow)
		{
			if (moveAxis != Vector2::zero)
			{
				// �����A�j���[�V�������Đ�����
				anim->SetAnimation("RifleRun", true);
				anim->Play();
			}
			else
			{
				// �ړ����͂��Ȃ����Idle�A�j���[�V�������Đ�����
				anim->SetAnimation("RifleIdle", true);
				anim->Play();
			}
		}
	}

}

/**
* �W�����v
*/
void Gundam::Jump(bool isJump, const Vector2& moveAxis)
{
	// �_�b�V����ԂȂ牽�����Ȃ�
	if (moveParamater.dash.isNow)
	{
		return;
	}
	if (isJump)
	{
		// �G�l���M�[������΃W�����v������
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

			// �G�l���M�[������
			boostEnergy += moveParamater.jump.useEnergy * Time::DeltaTime();

			// �W�����v�A�j���[�V�������Đ�
			if (!moveParamater.jump.isNow)
			{
				anim->SetAnimation("RifleJump");
				anim->Play();
			}

			//�u�[�X�g�G�l���M�[�̉񕜂����b�N
			boostEnergyChageLock = true;

			// �W�����v��ԂɕύX
			moveParamater.jump.isNow = true;
		}
		else
		{
			// �G�l���M�[���Ȃ��Ȃ�΃W�����v��Ԃ��I���
			if (moveParamater.jump.isNow)
			{
				// �G�l���M�[�`���[�W�̃��b�N������
				boostEnergyChageLock = false;
				// �G�l���M�[�`���[�W�̃^�C�}�[����
				boostEnergyChageTimer = boostEnergyChageOverHeatStartTime;

				anim->SetAnimation("RifleIdle", true);
				anim->Play();

				// �W�����v��Ԃ��I��
				moveParamater.jump.isNow = false;
			}
		}
	}
	else
	{
		if (moveParamater.jump.isNow)
		{
			// �G�l���M�[�`���[�W�̃��b�N������
			boostEnergyChageLock = false;
			// �G�l���M�[�`���[�W�̃^�C�}�[����
			boostEnergyChageTimer = boostEnergyChageStartTime;

			if (!rifle->isNow)
			{
				// �ʏ��Ԃ̃A�j���[�V�����ɕύX
				anim->SetAnimation("RifleIdle", true);
				anim->Play();
			}

			// �W�����v��Ԃ��I��
			moveParamater.jump.isNow = false;
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
		// �G�l���M�[������΃_�b�V��������
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

			// �G�l���M�[������
			boostEnergy += moveParamater.dash.useEnergy * Time::DeltaTime();

			// �ˌ���ԂȂ�A�j���[�V�������L�����Z��
			if (!rifle->isNow)
			{
				if (!moveParamater.dash.isNow || anim->GetAnimationClip()->name != "RifleDash")
				{
					// �_�b�V���A�j���[�V�������Đ�
					anim->SetAnimation("RifleDash", true);
					anim->Play();
				}
			}
			// �_�b�V�����ɕύX
			moveParamater.dash.isNow = true;
			// �G�l���M�[�`���[�W�����b�N
			boostEnergyChageLock = true;
		}
		else
		{
			// �G�l���M�[���Ȃ��Ȃ�΃_�b�V����Ԃ��I���
			if (moveParamater.dash.isNow)
			{
				// �G�l���M�[�`���[�W�̃��b�N������
				boostEnergyChageLock = false;
				// �G�l���M�[�`���[�W�̃^�C�}�[����
				boostEnergyChageTimer = boostEnergyChageOverHeatStartTime;

				if (!rifle->isNow)
				{
					// �ʏ��Ԃ̃A�j���[�V�����ɕύX
					anim->SetAnimation("RifleIdle", true);
					anim->Play();
				}

				// �_�b�V����Ԃ��I��
				moveParamater.dash.isNow = false;
			}
		}
	}
	else
	{
		if (moveParamater.dash.isNow)
		{
			// �G�l���M�[�`���[�W�̃��b�N������
			boostEnergyChageLock = false;
			// �G�l���M�[�`���[�W�̃^�C�}�[����
			boostEnergyChageTimer = boostEnergyChageStartTime;

			if (!rifle->isNow)
			{
				// �ʏ��Ԃ̃A�j���[�V�����ɕύX
				anim->SetAnimation("RifleIdle", true);
				anim->Play();
			}

			// �_�b�V����Ԃ��I��
			moveParamater.dash.isNow = false;
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
		if (rifle->amo > 0 && !rifle->isNow)
		{
			// �c�e�����炷
			rifle->amo -= 1;

			// �^�[�Q�b�g�����Ă��炻���������
			if (GetTargetMs())
			{
				GetTransform()->LookAt(GetTargetMs()->GetTransform());
			}

			// �e�̐����ʒu���v�Z
			auto pos = GetTransform()->position + (GetTransform()->rotation * Vector3(0.5f, 0.8f, 8.0f));

			// �e���쐬
			auto bullet = Instantate("Bullet", pos, GetTransform()->rotation);
			auto renderer = bullet->AddComponent<MeshRenderer>();
			renderer->mesh = rifle->mesh;
			renderer->shader = rifle->shader;
			auto bulletMove = bullet->AddComponent<Bullet>();
			bulletMove->speed = rifle->speed;
			bulletMove->rotationSpeed = rifle->homingPower;
			bulletMove->damage = rifle->damage;
			if (GetDistance() < redLookDistace)
			{
				bulletMove->targetMS = GetTargetMs();
			}

			// �A�j���[�V�������Đ�
			if (anim->GetAnimationClip()->name == "RifleRun" || anim->GetAnimationClip()->name == "SableRun")
			{
				anim->SetAnimation("RunRifleShot");
				anim->Play();
			}
			else if (anim->GetAnimationClip()->name == "RifleDash")
			{
				anim->SetAnimation("DashRifleShot");
				anim->Play();
			}
			else
			{
				anim->SetAnimation("RifleShot");
				anim->Play();
			}


			rifle->isNow = true;
		}
	}
	if (rifle->isNow)
	{
		// �ˌ��A�j���[�V�������I���Ύˌ���Ԃ���������
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			// �A�j���[�V�������Đ�
			if (anim->GetAnimationClip()->name == "RunRifleShot")
			{
				anim->SetAnimation("RifleRun", true);
				anim->Play();
			}
			else if (anim->GetAnimationClip()->name == "DashRifleShot")
			{
				anim->SetAnimation("RifleDash");
				anim->Play();
			}
			else
			{
				anim->SetAnimation("RifleIdle");
				anim->Play();
			}

			rifle->isNow = false;
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
}

/**
* �����Ԃ�
*/
void Gundam::Remove(const Vector3& removePos, float hp)
{
	// �h���ʒu��ݒ�
	GetTransform()->position = removePos;

	// �X�e�[�^�X�̐ݒ�
	this->hp = hpMax * hp;

	// �����̏�����
	rifle->Initialize();

	// ���S��Ԃ�����
	isDeath = false;
	anim->SetAnimation("RifleIdle");
}
