/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "HomingBullet.h"
#include "DamageInfo.h"
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;

/**
* �ŏ��Ɏ��s
*/
void Gundam::Awake()
{
	// ���\�[�X�}�l�[�W���[���擾
	auto resManager = ResouceManager::GetInstance();
	if (!isResoueLoad)
	{
		resManager->LoadObj("Gundam/BeumRifleBullet", "Application/Res/Ms/Gundam/Model/BeumRifleBullet.obj");
		resManager->LoadTga("Gundam/BeumRifleIcon", "Application/Res/Ms/Gundam/UI/BeumRifleIcon.tga");
		resManager->LoadObj("Gundam/BazookaBullet", "Application/Res/Ms/Gundam/Model/BazookaBullet.obj");
		resManager->LoadTga("Gundam/BazookaIcon", "Application/Res/Ms/Gundam/UI/BazookaIcon.tga");
		isResoueLoad = true;
	}

	// �`��R���|�[�l���g��ǉ�
	renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = resManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// �d�͂�ǉ�
	rb = OwnerObject()->AddComponent<Rigidbody>();
	rb->gravityScale = 2;

	// �R���C�_�[��ǉ�
	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = 2.4f;
	col->ceneter = Vector3(0, -2.3f, 0);
	auto col2 = OwnerObject()->AddComponent<SphereCollider>();
	col2->radius = 2.5f;
	col2->ceneter = Vector3(0, -0.4f, -0.2f);

	// �A�j���[�^��ǉ�
	anim = OwnerObject()->AddComponent<Animator>();
	anim->animationClips = renderer->glTFfile->animationClips;

	// �ŏ��̃A�j���[�V������ǉ�
	anim->SetAnimation("Idle.Rifle", true);
	anim->Play();

	// ��b�p�����[�^��ݒ�
	baseParamater.hpMax = 600;
	baseParamater.hp = baseParamater.hpMax;
	baseParamater.cost = 2000;

	// �U���̋���
	proximityDistance = 40.0f;
	redLookDistace = 90.0f;

	// �ړ��p�����[�^
	moveParamater.speed = 20.0f;
	moveParamater.rotationSpeed = 0.05f;

	// �_�b�V��
	moveParamater.dash.speed = 40.0f;
	moveParamater.dash.rotationSpeed = 0.01f;
	moveParamater.dash.useEnergy = -30.0f;

	// �W�����v
	moveParamater.jump.power = 30.0f;
	moveParamater.jump.speed = 10.0f;
	moveParamater.jump.rotationSpeed = 0.05f;
	moveParamater.jump.useEnergy = -30.0f;

	// ���C�t���̐���
	{
		rifle = std::make_shared<Rifle>();
		rifle->name = "BeumRifle";
		rifle->amoMax = 7;
		rifle->reloadTime = 3;
		rifle->iconTexture = resManager->GetTexture("Gundam/BeumRifleIcon");
		rifle->amo = rifle->amoMax;

		// �e�̃p�����[�^��ݒ�
		rifle->bullet.damage = 70.0f;
		rifle->bullet.downPower = 40;
		rifle->bullet.homingPower = 0.4f;
		rifle->bullet.speed = 200.0f;
		rifle->bullet.mesh = resManager->GetStaticMesh("Gundam/BeumRifleBullet");
		rifle->bullet.shader = resManager->GetShader(DefalutShader::Unlit);
	}
	{
		// �o�Y�[�J�̐���
		bazooka = std::make_shared<Bazooka>();
		bazooka->name = "Bazooka";
		bazooka->amoMax = 3;
		bazooka->amo = bazooka->amoMax;
		bazooka->reloadTime = 4;
		bazooka->iconTexture = resManager->GetTexture("Gundam/BazookaIcon");

		// �e�̃p�����[�^��ݒ�
		bazooka->bullet.damage = 99.0f;
		bazooka->bullet.downPower = 100;
		bazooka->bullet.homingPower = 0.9f;
		bazooka->bullet.speed = 80.0f;
		bazooka->bullet.mesh = resManager->GetStaticMesh("Gundam/BazookaBullet");
		bazooka->bullet.shader = resManager->GetShader(DefalutShader::Standard3D);
		bazooka->bullet.shadowShader = resManager->GetShader(DefalutShader::Shadow3D);
	}
	uiWeapons.push_back(bazooka);
	uiWeapons.push_back(rifle);

}

/**
* ���t���[�����s
*/
void Gundam::Update()
{
	// ��~��ԂȂ牽�����Ȃ�
	if (isStop)
	{
		return;
	}

	// ���S�`�F�b�N�A����ł���Ή������Ȃ�
	if (DeadChaeck())
	{
		return;
	}

	// ������я���
	if (isBlowAway && !isDown)
	{
		blowAwayTimer += Time::DeltaTime();
		if (anim->GetAnimationClip()->name == "BlowAway.Rifle.F")
		{
			GetTransform()->position -= blowPower * GetTransform()->Forward() * Time::DeltaTime();
		}
		else if (anim->GetAnimationClip()->name == "BlowAway.Rifle.B")
		{
			GetTransform()->position += blowPower * GetTransform()->Forward() * Time::DeltaTime();
		}
		if (blowAwayTimer > blowAwayTime && rb->IsGround())
		{
			isBlowAway = false;

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
		if (blowAwayTimer > 5)
		{
			rb->gravityScale = 2;
			isBlowAway = false;
		}
	}

	// �_�E�����
	if (isDown)
	{
		// �_�E�����Ԃ𑝉�
		downTimer += Time::DeltaTime();

		// �ړ����������邩�A�_�E�����Ԃ���肽�ĂΗ����オ�点��
		if (gameInput->moveAxis != Vector2::zero || downTimer >= downStandUpTime)
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
		// �����グ��A�j���[�V��������
		if (anim->GetAnimationClip()->name == "StandUp.Rifle.F" || 
			anim->GetAnimationClip()->name == "StandUp.Rifle.B")
		{
			// �A�j���[�V�������I����
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// �_�E����Ԃ��I��
				isDown = false;
				anim->SetAnimation("Idle.Rifle");
				anim->Play();
			}
		}
	}

	// �_���[�W��ԂȂ�
	if (isDamage)
	{
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			// �_���[�W�A�j���[�V�������I���΃_���[�W��Ԃ�����
			isDamage = false;

			// ���ꂼ��̏�Ԃ����ɖ߂�
			rb->isGravity = true;

			// ���C�t��
			{
				rifle->isNow = false;
				rifle->isShot = false;
				rifle->isStopShot = false;
			}
			// �o�Y�[�J
			{
				bazooka->isNow = false;
				bazooka->isShot = false;
			}
			// �A�j���[�V�������Đ�
			if (anim->GetAnimationClip()->name == "Damage.Rifle")
			{
				anim->SetAnimation("Idle.Rifle");
				anim->Play();
			}
		}
	}

	if (isRespon)
	{
		responTimer -= Time::DeltaTime();
		if (responTimer <= 0)
		{
			isRespon = false;
		}
	}

	// MS�̓��͍s��
	if (gameInput && !isRespon)
	{
		// �_���[�W��ԂȂ牽�����Ȃ�
		if (!isDamage && !isBlowAway && !isDown)
		{
			// �ړ�
			Move(gameInput->moveAxis);
			// �W�����v
			Jump(gameInput->jumpBtn, gameInput->moveAxis);
			// �_�b�V��
			Dash(gameInput->dashBtn, gameInput->moveAxis);
			// �U��(�r�[�����C�t��)
			Action1(gameInput->action1Btn);
			// �U��2(�o�Y�[�J)
			Action2(gameInput->action2Btn);
		}
	}

	// �u�[�X�g�G�l���M�[���X�V
	BoostEnergyUpdate();

	// �����[�h���X�V
	ReloadUpdate();
}

/**
* �����[�h�X�V
*/
void Gundam::ReloadUpdate()
{
	// �r�[�����C�t���̃����[�h
	{
		// �e�������Ă���΃����[�h
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
	// �o�Y�[�J�̃����[�h
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
* �ړ�
*
* @param moveAxis ���͎�
*/
void Gundam::Move(const Vector2& moveAxis)
{
	// �J�����̈ʒu���擾
	auto cameraTrs = GetCameraTransform();
	if (!cameraTrs)
	{
		return;
	}

	// �W�����v�E�_�b�V���E���C�t���̈ړ��֎~�E�o�Y�[�J��ԂȂ�ړ����Ȃ�
	if (moveParamater.dash.isNow || moveParamater.jump.isNow || rifle->isStopShot || bazooka->isNow)
	{
		return;
	}

	// �J�����̕�������AX-Z�P�ʃx�N�g��(���K��)���擾
	Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
	Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

	if (rb->IsGround())
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
		if (!rifle->isNow && !bazooka->isNow)
		{
			if (moveAxis != Vector2::zero)
			{
				// �����A�j���[�V�������Đ�����
				anim->SetAnimation("Run.Rifle", true);
				anim->Play();
			}
			else
			{
				// �ړ����͂��Ȃ����Idle�A�j���[�V�������Đ�����
				anim->SetAnimation("Idle.Rifle", true);
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
	// �_�b�V���E���C�t���̈ړ��֎~�E�o�Y�[�J��ԂȂ�W�����v���Ȃ�
	if (moveParamater.dash.isNow || rifle->isStopShot || bazooka->isNow)
	{
		return;
	}

	// �W�����v���͂������
	if (isJump)
	{
		// �G�l���M�[������΃W�����v������
		if (boostParamater.current > 0)
		{
			// �J�������擾
			auto cameraTrs = GetCameraTransform();
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
					Quaternion::LookRotation(moveForward), moveParamater.jump.rotationSpeed);
			}
			if (moveAxis != Vector2::zero)
			{
				// �I�u�W�F�N�g�̌����Ă�����ɐi��
				GetTransform()->position += GetTransform()->Forward() * moveParamater.jump.speed * Time::DeltaTime();
			}

			// �ˌ���ԂȂ�A�j���[�V�������L�����Z��
			if (!rifle->isNow)
			{
				// �W�����v�A�j���[�V�������Đ�
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
			}

			// �d�͂̑��x��0�ɂ��ā@
			rb->velocity = Vector3(0);
			// �㏸
			GetTransform()->position.y += moveParamater.jump.power * Time::DeltaTime();

			// �G�l���M�[������
			boostParamater.current += moveParamater.jump.useEnergy * Time::DeltaTime();

			//�u�[�X�g�G�l���M�[�̉񕜂����b�N
			boostParamater.chageLock = true;

			// �W�����v��ԂɕύX
			moveParamater.jump.isNow = true;
		}
		else
		{
			// �G�l���M�[���Ȃ��Ȃ�΃W�����v��Ԃ��I���
			if (moveParamater.jump.isNow)
			{
				// �G�l���M�[�`���[�W�̃��b�N������
				boostParamater.chageLock = false;
				// �G�l���M�[�`���[�W�̃^�C�}�[����
				boostParamater.chageStartTimer = boostParamater.overHeatChageStartTime;

				// �ˌ���ԂȂ�A�j���[�V�������L�����Z��
				if (!rifle->isNow)
				{
					anim->SetAnimation("Idle.Rifle", true);
					anim->Play();
				}
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
			boostParamater.chageLock = false;
			// �G�l���M�[�`���[�W�̃^�C�}�[����
			boostParamater.chageStartTimer = boostParamater.chageStartTime;

			if (!rifle->isNow)
			{
				// �ʏ��Ԃ̃A�j���[�V�����ɕύX
				anim->SetAnimation("Idle.Rifle", true);
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
	// ���C�t���̒�~�E�o�Y�[�J��ԂȂ�_�b�V�����Ȃ�
	if (rifle->isStopShot || bazooka->isNow)
	{
		return;
	}

	if (isDash)
	{
		// �G�l���M�[������΃_�b�V��������
		if (boostParamater.current > 0)
		{
			rb->isVelocity = false;

			rb->velocity.y = 0;
			// �J�������擾
			auto cameraTrs = GetCameraTransform();
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
			rb->velocity = GetTransform()->Forward() * moveParamater.dash.speed;

			// �G�l���M�[������
			boostParamater.current += moveParamater.dash.useEnergy * Time::DeltaTime();

			// �ˌ���ԂȂ�A�j���[�V�������L�����Z��
			if (!rifle->isNow)
			{
				if (!moveParamater.dash.isNow || anim->GetAnimationClip()->name != "Dash.Rifle")
				{
					// �_�b�V���A�j���[�V�������Đ�
					anim->SetAnimation("Dash.Rifle", true);
					anim->Play();
				}
			}
			// �_�b�V�����ɕύX
			moveParamater.dash.isNow = true;
			// �G�l���M�[�`���[�W�����b�N
			boostParamater.chageLock = true;
		}
		else
		{
			// �G�l���M�[���Ȃ��Ȃ�΃_�b�V����Ԃ��I���
			if (moveParamater.dash.isNow)
			{
				rb->isVelocity = true;
				// �G�l���M�[�`���[�W�̃��b�N������
				boostParamater.chageLock = false;
				// �G�l���M�[�`���[�W�̃^�C�}�[����
				boostParamater.chageStartTimer = boostParamater.overHeatChageStartTime;

				if (!rifle->isNow)
				{
					// �ʏ��Ԃ̃A�j���[�V�����ɕύX
					anim->SetAnimation("Idle.Rifle", true);
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
			rb->isVelocity = true;
			// �G�l���M�[�`���[�W�̃��b�N������
			boostParamater.chageLock = false;
			// �G�l���M�[�`���[�W�̃^�C�}�[����
			boostParamater.chageStartTimer = boostParamater.chageStartTime;


			if (!rifle->isNow)
			{
				// �ʏ��Ԃ̃A�j���[�V�����ɕύX
				anim->SetAnimation("Idle.Rifle", true);
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
void Gundam::Action1(bool attackKey)
{
	// �U�����͂������
	if (attackKey)
	{
		// �o�Y�[�J�U����ԂȂ烉�C�t���U�������Ȃ�
		if (bazooka->isNow)
		{
			return;
		}

		// �r�[�����C�t���̒e������Ύˌ�
		if (rifle->amo > 0 && !rifle->isNow)
		{
			// �^�[�Q�b�g���������猩�Ăǂ̕����ɂ��邩���ׂ�
			Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
			Vector3 perendicular = Vector3::Cross(directionToTarget, GetTransform()->Forward());
			float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());

			// �������ˌ���������
			if (dot < -0.5f)
			{
				// �������~�߂�
				rifle->isStopShot = true;
				// �d�͂��g��Ȃ�
				rb->isGravity = false;
				rb->velocity = Vector3(0);

				// ����̋t����������
				GetTransform()->rotation = Quaternion::LookRotation(-directionToTarget * Vector3(1, 0, 1));

				anim->SetAnimation("Rifle.Shot.Idle.B");
				anim->Play();
			}
			// �A�C�h���E�W�����v���
			else if (anim->GetAnimationClip()->name == "Idle.Rifle" || 
				anim->GetAnimationClip()->name == "Jump.Rifle" || anim->GetAnimationClip()->name == "Jump.Rifle.Ground")
			{
				rb->velocity = Vector3(0, 1, 0);
				// �������~�߂�
				rifle->isStopShot = true;

				// �O��
				if (dot > 0.9f)
				{
					anim->SetAnimation("Rifle.Shot.Idle.F");
					anim->Play();
				}
				// �E��
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
				// ����
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
			// �������
			else if (anim->GetAnimationClip()->name == "Run.Rifle")
			{
				// �O��
				if (dot > 0.9f)
				{
					anim->SetAnimation("Rifle.Shot.Run.F");
					anim->Play();
				}
				// �E��
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
				// ����
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
			// �_�b�V�����
			else if (anim->GetAnimationClip()->name == "Dash.Rifle")
			{
				// �O��
				if (dot > 0.9f)
				{
					anim->SetAnimation("Rifle.Shot.Dash.F");
					anim->Play();
				}
				// �E��
				else if (perendicular.y < 0)
				{
					anim->SetAnimation("Rifle.Shot.Dash.R");
					anim->Play();
				}
				// ��
				else if (perendicular.y > 0)
				{
					anim->SetAnimation("Rifle.Shot.Dash.L");
					anim->Play();
				}
			}

			// �ˌ���
			rifle->isNow = true;
		}
	}
	// �ˌ����
	if (rifle->isNow)
	{
		if (anim->time >= 0.2f && !rifle->isShot)
		{
			// �c�e�����炷
			rifle->amo -= 1;

			// �^�[�Q�b�g�̕������擾
			Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
			Quaternion rot = Quaternion::LookRotation(directionToTarget);

			// �e�̐����ʒu���v�Z
			auto pos = GetTransform()->position + (rot * Vector3(0, 0, 5));

			// �e���쐬
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

			// �����ɂ���ėU��������
			if (GetDistance() < redLookDistace)
			{
				homingBullet->SetTargetMs(GetTargetMs());
			}

			// ������
			rifle->isShot = true;
		}

		// �ˌ��A�j���[�V�������I���Ύˌ���Ԃ���������
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			// �A�j���[�V�������Đ�
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
* �U��2(�o�Y�[�J)
*/
void Gundam::Action2(bool attackKey)
{
	// �U�����͂������
	if (attackKey)
	{
		// ���C�t���U����ԂȂ�o�Y�[�J�U�������Ȃ�
		if (rifle->isNow)
		{
			return;
		}

		// �o�Y�[�J�̒e������Ȃ�ˌ�
		if (bazooka->amo > 0 && !bazooka->isNow)
		{
			if (GetTargetMs())
			{
				// �^�[�Q�b�g���������猩�Ăǂ̕����ɂ��邩���ׂ�
				Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
				float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());

				// �d�͂��g��Ȃ�
				rb->isGravity = false;
				rb->velocity = Vector3(0);

				// ����̋t����������
				GetTransform()->rotation = Quaternion::LookRotation(directionToTarget * Vector3(1, 0, 1));
			}

			// �A�j���[�V�������Đ�
			anim->SetAnimation("Bazooka.Shot");
			anim->Play();

			// �ˌ���
			bazooka->isNow = true;
		}
	}
	// �ˌ���
	if (bazooka->isNow)
	{
		if (anim->time >= 0.4f && !bazooka->isShot)
		{
			// �c�e�����炷
			bazooka->amo -= 1;

			// �e�̐����ʒu���v�Z
			auto pos = GetTransform()->position + (GetTransform()->rotation * Vector3(0.3f, 0, 5));

			// �e���쐬
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

			// �����Ō��ɓ�����
			GetTransform()->position += GetTransform()->Forward() * -0.5f;

			// �����ɂ���ėU��������
			if (GetDistance() < redLookDistace)
			{
				homingBullet->SetTargetMs(GetTargetMs());
			}

			// ������
			bazooka->isShot = true;
		}

		// �ˌ��A�j���[�V�������I���Ύˌ���Ԃ���������
		if (anim->time >= anim->GetAnimationClip()->totalTime)
		{
			// �A�j���[�V�������Đ�
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
* �U��3(�r�[���T�[�x��)
*
* @param acttion3Btn �A�N�V�����{�^��3�̏��
*/
void Gundam::Action3(bool acttion3Btn)
{
	if (acttion3Btn)
	{
		
	}
}

/**
* �_���[�W
*
* @param damage �_���[�W���
*/
void Gundam::Damage(const DamageInfo& damageInfo)
{
	if (isBlowAway || isDown || isRespon)
	{
		return;
	}
	// �^����ꂽ�_���[�W�̕������v�Z
	Vector3 directionToTarget = damageInfo.direction;
	float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());

	// �̗͂����炷
	baseParamater.hp -= static_cast<int>(damageInfo.damage);
	downValue += damageInfo.downPower;

	// �ʏ�_���[�W�A�N�V����
	if (downValue < 100)
	{
		// �O��
		if (dot > 0)
		{
			GetTransform()->rotation = Quaternion::LookRotation(directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * -1.0f;

			anim->SetAnimation("Damage.Rifle.F");
			anim->Play();
		}
		// ���
		else
		{
			GetTransform()->rotation = Quaternion::LookRotation(-directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * 1.0f;

			anim->SetAnimation("Damage.Rifle.B");
			anim->Play();
		}

		// �d�͂𖳂�
		rb->isGravity = false;
		rb->velocity = Vector3::zero;

		// �_���[�W��Ԃɂ���
		isDamage = true;
	}
	// �_�E�����
	else
	{
		// �O��
		if (dot > 0)
		{
			GetTransform()->rotation = Quaternion::LookRotation(directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * -1.0f;

			anim->SetAnimation("BlowAway.Rifle.F");
			anim->Play();
		}
		// ���
		else
		{
			GetTransform()->rotation = Quaternion::LookRotation(-directionToTarget * Vector3(1, 0, 1));
			GetTransform()->position += GetTransform()->Forward() * 1.0f;

			anim->SetAnimation("BlowAway.Rifle.B");
			anim->Play();
		}
		rb->gravityScale = 3;
		rb->isGravity = true;
		blowAwayTimer = 0;
		isBlowAway = true;
		downValue = 0;
	}

}

/**
* �����Ԃ�
*
* @param removePos	�����Ԃ�ʒu
* @param hpCut		�̗͂̃J�b�g��
*/
void Gundam::Respon(const Vector3& removePos, float hpCut)
{
	// �h���ʒu��ݒ�
	GetTransform()->position = removePos;

	// �X�e�[�^�X�̐ݒ�
	baseParamater.hp = baseParamater.hpMax * hpCut;
	boostParamater.current = boostParamater.max;

	// �����̏�����
	rifle->Initialize();
	bazooka->Initialize();

	// ���S��Ԃ�����
	downValue = 0;
	isBlowAway = false;
	isDamage = false;
	isDown = false;
	isDeath = false;
	rb->isGravity = true;

	rb->velocity = Vector3::zero;
	renderer->enabled = true;

	// �^�[�Q�b�g�̕������擾
	Vector3 directionToTarget = Vector3(GetTargetMs()->GetTransform()->position - GetTransform()->position).Normalized();
	Quaternion rot = Quaternion::LookRotation(directionToTarget);
	// ����̋t����������
	GetTransform()->rotation = Quaternion::LookRotation(directionToTarget * Vector3(1, 0, 1));

	anim->SetAnimation("Idle.Rifle");
	anim->Play();
	responTimer = responTime;
	isRespon = true;
}
