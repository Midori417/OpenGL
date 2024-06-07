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
* ���ʉ��ݒ�
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
* �ŏ��Ɏ��s
*/
void Gundam::Awake()
{
	// �^�O��Ms�ɂ���
	OwnerObject()->tag = "Ms";

	// ���\�[�X�}�l�[�W���[���擾
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
	anim->SetAnimation(Animation::idleRifle, true);
	anim->Play();

	// �T�E���h
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

	// ��b�p�����[�^��ݒ�
	baseParamater.hpMax = 600;
	baseParamater.hp = baseParamater.hpMax;
	baseParamater.cost = 2000;

	// �U���̋���
	proximityDistance = 40.0f;
	redLookDistaceXZ = 100.0f;
	redLookDistanceMinY = -100.0f;
	redLookDistanceMaxY = 10.0f;

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

	// �X�e�b�v
	moveParamater.step.speed = 30.0f;
	moveParamater.step.useEnergy = 20.0f;

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
	// �T�[�x��
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

	// UI�����z��ɒǉ�
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
		if (!isDeath)
		{
			audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::dead);
			audioSources[AudioIndex::otherSound]->Play();
			// ���S��Ԃɂ���
			isDeath = true;
		}
		return;
	}

	// ������я���
	if (blowAway.isNow && !isDown)
	{
		blowAway.timer += Time::DeltaTime();

		// �A�j���[�V�����ɂ���Đ�����ԕ�����ς���
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

		// �o�O�΍�
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

	// �_�E���L�����Z����ԂȂ�
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

	// �_�E�����
	if (isDown)
	{
		// �_�E�����Ԃ𑝉�
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

			// �A�j���[�V�������Đ�
			if (anim->GetAnimationClip()->name == "Damage.Rifle")
			{
				anim->SetAnimation("Idle.Rifle");
				anim->Play();
			}
		}
	}

	// ���X�|�[�����
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
		if (!isDamage && !blowAway.isNow && !isDown && !isDownCancel)
		{
			Step(gameInput->stepBtn, gameInput->moveAxis);
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
			// �U��(�T�[�x��)
			Action3(gameInput->action3Btn);
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
	if (moveParamater.dash.isNow || moveParamater.jump.isNow || moveParamater.step.isNow ||
		rifle->isStopShot || bazooka->isNow || sable->isNow)
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
			// �ړ����͂�����Ε����A�j���[�V�������Đ�
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
			// �ړ����͂��Ȃ���΃A�C�h���A�j���[�V�������Đ�
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
* �W�����v
*/
void Gundam::Jump(bool isJump, const Vector2& moveAxis)
{
	// �_�b�V���E���C�t���̈ړ��֎~�E�o�Y�[�J��ԂȂ�W�����v���Ȃ�
	if (moveParamater.dash.isNow || rifle->isStopShot || bazooka->isNow || sable->isNow || moveParamater.step.isNow)
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
				if (handWeapon == HandWeapon::Rifle)
				{
					anim->SetAnimation("Idle.Rifle", true);
				}
				else
				{
					anim->SetAnimation("Idle.Sable", true);
				}
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
	if (rifle->isStopShot || bazooka->isNow || sable->isNow || moveParamater.step.isNow)
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
					if (handWeapon == HandWeapon::Rifle)
					{
						anim->SetAnimation("Idle.Rifle", true);
					}
					else
					{
						anim->SetAnimation("Idle.Sable", true);
					}
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
				if (handWeapon == HandWeapon::Rifle)
				{
					anim->SetAnimation("Idle.Rifle", true);
				}
				else
				{
					anim->SetAnimation("Idle.Sable", true);
				}
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
		if (bazooka->isNow || sable->isNow || moveParamater.step.isNow)
		{
			return;
		}

		// �r�[�����C�t���̒e������Ύˌ�
		if (rifle->amo > 0 && !rifle->isNow)
		{
			// �����Ă��镐�������C�t���ɂ���
			handWeapon = HandWeapon::Rifle;

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
			else if (anim->GetAnimationClip()->name == "Run.Rifle" && rb->IsGround())
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
			else
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

			// �ˌ���
			rifle->isNow = true;
		}
	}
	// �ˌ����
	if (rifle->isNow)
	{
		if (anim->time >= 0.2f && !rifle->isShot)
		{
			auto msPos = GetTransform()->position;

			audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::beumRifleShot);
			audioSources[AudioIndex::otherSound]->Play();

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
			if (HomingCheck())
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
		if (rifle->isNow || sable->isNow || moveParamater.step.isNow)
		{
			return;
		}

		// �o�Y�[�J�̒e������Ȃ�ˌ�
		if (bazooka->amo > 0 && !bazooka->isNow)
		{
			// �����Ă��镐�������C�t���ɂ���
			handWeapon = HandWeapon::Rifle;

			// �^�[�Q�b�g�������
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
		if (!bazooka->isShot)
		{
			boostParamater.chageLock = true;
			boostParamater.current -= 30 * Time::DeltaTime();
		}
		if (anim->time >= 0.4f && !bazooka->isShot)
		{

			audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::bazookaShot);
			audioSources[AudioIndex::otherSound]->Play();

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
			if (HomingCheck())
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
			BoostCheck();
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
		if (rifle->isNow || bazooka->isNow || moveParamater.step.isNow)
		{
			return;
		}
		if (!sable->isNow)
		{
			// �T�[�x���s�����ɂ���
			sable->isNow = true;
			// �d�͂��󂯂Ȃ�����
			rb->isGravity = false;
			rb->velocity = Vector3::zero;

			// �u�[�X�g�G�l���M�[�̃`���[�W�����b�N����
			boostParamater.chageLock = true;

			// �^�[�Q�b�g�Ƃ̋������ԃ��b�N�����Ȃ�
			if (HomingCheck())
			{
				// �����Ă��镐�����T�[�x���ɂ���
				handWeapon = HandWeapon::Sable;

				// �T�[�x���ړ���Ԃɂ���
				sable->move.isNow = true;

				// �U�����n�߂��ʒu���i�[
				sable->move.attackStartPos = GetTransform()->position;

				// �U������
				sable->isHoming = true;

				sable->targetPos = &GetTargetMs()->GetTransform()->position;

				// �A�j���[�V�������Đ�
				anim->SetAnimation("Sable.Move");
				anim->Play();
			}
			else
			{
				// �����Ă��镐�킪�T�[�x������Ȃ����
				if (handWeapon != HandWeapon::Sable)
				{
					// �����Ă��镐�����T�[�x���ɂ���
					handWeapon = HandWeapon::Sable;

					// �͈͊O���ƃT�[�x��������Ԃɂ���
					sable->isGet = true;

					// �A�j���[�V�������Đ�
					anim->SetAnimation("Sable.Get");
					anim->Play();
				}
				else
				{
					// �T�[�x���ړ���Ԃɂ���
					sable->move.isNow = true;

					// �U�����n�߂��ʒu���i�[
					sable->move.attackStartPos = GetTransform()->position;

					// �U������
					sable->isHoming = false;

					sable->targetPos = &GetTargetMs()->GetTransform()->position;

					// �A�j���[�V�������Đ�
					anim->SetAnimation("Sable.Move");
					anim->Play();
				}
			}
		}
		// �T�[�x���s����
		else
		{
			// �A�j���[�V�������R���{��t���ԂȂ�U��2�ɂȂ���
			if (sable->attack1.isNow && anim->GetAnimationClip()->name == "Sable.Attack1")
			{
				if (anim->time >= 0.2f && anim->time <= 0.5f)
				{
					sable->attack2.isNow = true;
				}
			}
			// �A�j���[�V�������R���{��t���ԂȂ�U��3�ɂȂ���
			else if (sable->attack2.isNow && anim->GetAnimationClip()->name == "Sable.Attack2")
			{
				if (anim->time >= 0.2f && anim->time <= 0.5f)
				{
					sable->attack3.isNow = true;
				}
			}
		}
	}
	// �T�[�x���s����
	if (sable->isNow)
	{
		// �T�[�x���������
		if (sable->isGet)
		{
			// �A�j���[�V�������I����
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// �T�[�x����Ԃ��I��
				sable->isNow = false;
				// �T�[�x���擾��Ԃ��I��
				sable->isGet = false;
				// �d�͂𕜊�
				rb->isGravity = true;

				// �A�j���[�V�������Đ�
				anim->SetAnimation(Animation::idleSable);
				anim->Play();
			}
		}
		// �T�[�x���ړ����
		else if (sable->move.isNow)
		{
			// �����Ă�����ɐi��
			GetTransform()->position += sable->move.speed * GetTransform()->Forward() * Time::DeltaTime();

			// �G�l���M�[������
			boostParamater.current -= sable->move.useEnergy * Time::DeltaTime();
			boostParamater.chageLock = true;

			// �ړ��������v�Z
			float moveDistance = Mathf::Abs(Vector3::Distance(GetTransform()->position, sable->move.attackStartPos));

			// �U������
			if (sable->isHoming)
			{
				// �^�[�Q�b�g�̕������擾
				Vector3 directionToTarget = *sable->targetPos - GetTransform()->position;

				// �^�[�Q�b�g�̕�����������
				GetTransform()->rotation = Quaternion::LookRotation(directionToTarget);

				// ���ȏ�i�ނ��G�Ƃ̋������߂���΍U����i�K�ڂɂ���
				if (moveDistance >= sable->move.useHomingDistanceMax || GetDistance() <= sable->move.attackDistance)
				{
					// �T�[�x���ړ���Ԃ��I��
					sable->move.isNow = false;

					// �T�[�x���U����i�K�ڂɂ���
					sable->attack1.isNow = true;

					// ���ʉ���炷
					audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::sableAttack);
					audioSources[AudioIndex::otherSound]->Play();

					// �A�j���[�V�������Đ�
					anim->SetAnimation("Sable.Attack1");
					anim->Play();
				}
			}
			else
			{
				// ���ȏ�i�߂΍U����i�K�ڂɂ���
				if (moveDistance >= sable->move.noHomingDistanceMax)
				{
					// �T�[�x���ړ���Ԃ��I��
					sable->move.isNow = false;

					// �T�[�x���U����i�K�ڂɂ���
					sable->attack1.isNow = true;

					// ���ʉ���炷
					audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::sableAttack);
					audioSources[AudioIndex::otherSound]->Play();

					// �A�j���[�V�������Đ�
					anim->SetAnimation("Sable.Attack1");
					anim->Play();
				}

			}
		}
		// �T�[�x���U��1�i�K�ڒ�
		else if (sable->attack1.isNow)
		{
			// �A�j���[�V�����̎��Ԃ��ړ����ԓ��Ȃ�
			if (anim->time < sable->attack1.moveTime)
			{
				// �U������
				if (sable->isHoming)
				{
					// �G�Ƃ̋������U�������Ȃ�
					if (GetDistance() > sable->move.attackDistance)
					{
						// �����Ă�������ɐi��
						GetTransform()->position += sable->attack1.speed * GetTransform()->Forward() * Time::DeltaTime();
					}
				}
				// �U������
				else
				{
					// �����Ă�������ɐi��
					GetTransform()->position += sable->attack1.speed * GetTransform()->Forward() * Time::DeltaTime();
				}
			}

			// �A�j���[�V�������U�����ԂȂ�
			if (anim->time > sable->attack1.slashTime && !sable->attack1.isSlash)
			{
				// �U��������쐬
				auto slashObj = Instantate("Slash", Vector3(0, 0, 10));
				slashObj->GetTransform()->SetParent(GetTransform());
				auto slash = slashObj->AddComponent<BaseSlash>();
				slash->damage = sable->attack1.damage;
				slash->downPower = sable->attack1.downPower;
				slash->destoryTime = sable->attack1.destoryTime;

				// �U����������
				sable->attack1.isSlash = true;
			}

			// �T�[�x���U���Q�i�K�ڂ̏�ԂȂ�R���{������
			if (anim->time >= 0.5f && sable->attack2.isNow)
			{
				// �U������Ȃ�
				if (sable->isHoming)
				{
					// �^�[�Q�b�g�̕������擾
					Vector3 directionToTarget = *sable->targetPos - GetTransform()->position;
					GetTransform()->rotation = Quaternion::LookRotation(directionToTarget);
				}
				// �T�[�x���U���P��Ԃ�����
				sable->attack1.isNow = false;
				sable->attack1.isSlash = false;

				// ���ʉ���炷
				audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::sableAttack);
				audioSources[AudioIndex::otherSound]->Play();

				// �A�j���[�V�������Đ�
				anim->SetAnimation("Sable.Attack2");
				anim->Play();

			}

			// �A�j���[�V�������I����
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// �T�[�x���U���I��
				SableAttackFailded(sable->attack1);
			}
		}
		// �T�[�x���U��2�i�K�ڒ�
		else if (sable->attack2.isNow)
		{
			// �A�j���[�V�����̎��Ԃ��ړ����ԓ��Ȃ�
			if (anim->time < sable->attack2.moveTime)
			{
				// �U������
				if (sable->isHoming)
				{
					// �G�Ƃ̋������U�������Ȃ�
					if (GetDistance() > sable->move.attackDistance)
					{
						// �����Ă�������ɐi��
						GetTransform()->position += sable->attack2.speed * GetTransform()->Forward() * Time::DeltaTime();
					}
				}
				// �U������
				else
				{
					// �����Ă�������ɐi��
					GetTransform()->position += sable->attack2.speed * GetTransform()->Forward() * Time::DeltaTime();
				}
			}

			// �A�j���[�V�������U�����ԂȂ�
			if (anim->time > sable->attack2.slashTime && !sable->attack2.isSlash)
			{
				// �U��������쐬
				auto slashObj = Instantate("Slash", Vector3(0, 0, 10));
				slashObj->GetTransform()->SetParent(GetTransform());
				auto slash = slashObj->AddComponent<BaseSlash>();
				slash->damage = sable->attack2.damage;
				slash->downPower = sable->attack2.downPower;
				slash->destoryTime = sable->attack2.destoryTime;

				// �U����������
				sable->attack2.isSlash = true;
			}

			// �T�[�x���U���Q�i�K�ڂ̏�ԂȂ�R���{������
			if (anim->time >= 0.5f && sable->attack3.isNow)
			{
				// �U����ԂȂ�
				if (sable->isHoming)
				{
					// �^�[�Q�b�g�̕������擾
					Vector3 directionToTarget = *sable->targetPos - GetTransform()->position;
					GetTransform()->rotation = Quaternion::LookRotation(directionToTarget);
				}

				// �T�[�x���U��2��Ԃ�����
				sable->attack2.isNow = false;
				sable->attack2.isSlash = false;

				// ���ʉ���炷
				audioSources[AudioIndex::otherSound]->SetSoundFilename(SE::sableAttack);
				audioSources[AudioIndex::otherSound]->Play();

				// �A�j���[�V�������Đ�
				anim->SetAnimation("Sable.Attack3");
				anim->Play();
			}

			// �A�j���[�V�������I����
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// �T�[�x���U���I��
				SableAttackFailded(sable->attack2);
			}
		}
		// �T�[�x���U��3�i�K�ڒ�
		else if (sable->attack3.isNow)
		{
			// �A�j���[�V�����̎��Ԃ��ړ����ԓ��Ȃ�
			if (anim->time < sable->attack3.moveTime)
			{
				// �U������
				if (sable->isHoming)
				{
					// �G�Ƃ̋������U�������Ȃ�
					if (GetDistance() > sable->move.attackDistance)
					{
						// �����Ă�������ɐi��
						GetTransform()->position += sable->attack3.speed * GetTransform()->Forward() * Time::DeltaTime();
					}
				}
				// �U������
				else
				{
					// �����Ă�������ɐi��
					GetTransform()->position += sable->attack3.speed * GetTransform()->Forward() * Time::DeltaTime();
				}
			}

			// �A�j���[�V�������U�����ԂȂ�
			if (anim->time > sable->attack3.slashTime && !sable->attack3.isSlash)
			{
				// �U��������쐬
				auto slashObj = Instantate("Slash", Vector3(0, 0, 10));
				slashObj->GetTransform()->SetParent(GetTransform());
				auto slash = slashObj->AddComponent<BaseSlash>();
				slash->damage = sable->attack3.damage;
				slash->downPower = sable->attack3.downPower;
				slash->destoryTime = sable->attack3.destoryTime;

				// �U����������
				sable->attack3.isSlash = true;
			}

			// �A�j���[�V�������I����
			if (anim->time >= anim->GetAnimationClip()->totalTime)
			{
				// �T�[�x���U���I��
				SableAttackFailded(sable->attack3);
			}
		}
	}
}

/*
* �r�[���T�[�x���U���I��
*/
void Gundam::SableAttackFailded(Sable::Attack& attack)
{
	// �T�[�x���U����Ԃ�����
	sable->isNow = false;

	// �U����Ԃ�����
	attack.isNow = false;

	attack.isSlash = false;

	BoostCheck();
	// �d�͂𕜊�
	rb->isGravity = true;

	// �p���𐳂�
	GetTransform()->rotation = Quaternion::LookRotation(GetTransform()->Forward() * Vector3(1, 0, 1));

	// �A�j���[�V�������Đ�
	anim->SetAnimation("Idle.Sable");
	anim->Play();
}

/**
* �X�e�b�v
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

			// �J�����̕�������AX-Z�P�ʃx�N�g��(���K��)���擾
			Vector3 cameraForward = cameraTrs->Forward() * Vector3(1, 0, 1).Normalized();
			Vector3 moveFoward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

			Vector3 perendicular = Vector3::Cross(moveFoward.Normalized(), GetTransform()->Forward());
			float dot = Vector3::Dot(moveFoward.Normalized(), GetTransform()->Forward());
			// �T�[�x���U����Ԃ��������ꍇ
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
* �_���[�W
*
* @param damage �_���[�W���
*/
void Gundam::Damage(const DamageInfo& damageInfo)
{
	if (blowAway.isNow || isDown || isRespon || isDownCancel)
	{
		return;
	}

	// �^����ꂽ�_���[�W�̕������v�Z
	Vector3 directionToTarget = damageInfo.direction;
	float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());

	// �̗͂����炷
	baseParamater.hp -= static_cast<int>(damageInfo.damage);
	downValue += damageInfo.downPower;

	// �_�b�V�����
	if (moveParamater.dash.isNow)
	{
		moveParamater.dash.isNow = false;
	}
	// �W�����v���
	if (moveParamater.jump.isNow)
	{
		moveParamater.jump.isNow = false;
	}
	// ���C�t����Ԃ������ꍇ
	if (rifle->isNow)
	{
		rifle->isNow = false;
		rifle->isShot = false;
		rifle->isStopShot = false;
	}
	// �o�Y�[�J��Ԃ������ꍇ
	if (bazooka->isNow)
	{
		bazooka->isNow = false;
		bazooka->isShot = false;
	}
	// �T�[�x���U����Ԃ��������ꍇ
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
		blowAway.timer = 0;
		blowAway.isNow = true;
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
	// �T�[�x���U����Ԃ��������ꍇ
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

	// ���S��Ԃ�����
	downValue = 0;
	blowAway.isNow = false;
	isDamage = false;
	isDown = false;
	isDeath = false;
	rb->isGravity = true;
	boostParamater.chageLock = false;

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
