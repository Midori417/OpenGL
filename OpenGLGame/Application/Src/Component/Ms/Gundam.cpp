/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/CreateGameObjectType.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/MeshRenderer.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Asset/AnimationClip.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Other/Time.h"

#include "../HomingBullet.h"

/**
* �A�j���[�V�����̖��O
*/
namespace AnimationName
{
	const char IdleRifle[] = "Idle.Rifle";
	const char IdleSable[] = "Idle.Sable";

	const char RunRifle[] = "Run.Rifle";
	const char RunSable[] = "Run.Sable";

	namespace Jump
	{
		const char Rifle[] = "Jump.Rifle";
		const char Sable[] = "Jump.Sable";

		const char GroundRifle[] = "Jump.Rifle.Ground";
		const char GroundSable[] = "Jump.Sable.Ground";
	}
	namespace Dash
	{
		const char Rifle[] = "Dash.Rifle";
		const char Sable[] = "Dash.Sable";
	}
	namespace BeumRifleShot
	{
		namespace Idle
		{
			const char F[] = "Rifle.Shot.Idle.F";
			const char B[] = "Rifle.Shot.Idle.B";
			const char R[] = "Rifle.Shot.Idle.R";
			const char L[] = "Rifle.Shot.Idle.L";
			const char FR[] = "Rifle.Shot.Idle.FR";
			const char FL[] = "Rifle.Shot.Idle.FL";
		}
		namespace Run
		{
			const char F[] = "Rifle.Shot.Run.F";
			const char R[] = "Rifle.Shot.Run.R";
			const char L[] = "Rifle.Shot.Run.L";
			const char FR[] = "Rifle.Shot.Run.FR";
			const char FL[] = "Rifle.Shot.Run.FL";
		}
		namespace Dash
		{
			const char F[] = "Rifle.Shot.Dash.F";
			const char R[] = "Rifle.Shot.Dash.R";
			const char L[] = "Rifle.Shot.Dash.L";
		}
	}
}

/**
* �������Ɏ��s
*/
void Gundam::Awake()
{
	// �A�Z�b�g�}�l�[�W���[���擾
	auto assetManager = AssetManager::GetInstance();

	// �@�̋��ʃR���|�[�l���g���擾
	ComponentGet();

	// �f�t�H���g�̗������x���ƒx���̂ŃO���r�e�B�X�P�[������������
	rb->gravityScale = 2;

	// �`��R���|�[�l���g��ݒ�
	renderer->glTFfile = assetManager->GetGltfFile("Gundam");
	renderer->shader = assetManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = assetManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// �A�j���[�^��ݒ�
	anim->animationClips = renderer->glTFfile->animationClips;
	// �ŏ��ɗ����A�j���[�V������ݒ�
	anim->SetAnimation(AnimationName::IdleRifle, true);
	anim->Play();

	// �R���C�_�[��ǉ�
	SphereColliderPtr col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = 2.4f;
	col->ceneter = Vector3(0, -2.3f, 0);
	SphereColliderPtr col2 = OwnerObject()->AddComponent<SphereCollider>();
	col2->radius = 2.5f;
	col2->ceneter = Vector3(0, -0.4f, -0.2f);

	// ��b�p�����[�^��ݒ�
	{
		paramater.strengthValue = 2000;
		paramater.durabilityMax = 600;
		paramater.durability = paramater.durabilityMax;
	}
	// �ړ��p�����[�^
	{
		move.speed = 20.0f;
		move.rotationSpeed = 0.05f;
	}
	// �_�b�V���p�����[�^
	{
		dash.speed = 30.0f;
		dash.rotationSpeed = 0.01f;
		dash.useBoost = 30.0f;
	}
	// �W�����v�p�����[�^
	{
		jump.power = 20.0f;
		jump.speed = 10.0f;
		jump.rotationSpeed = 0.01f;
		jump.useBoost = 30.0f;
	}
	// ���C�t���p�����[�^
	{
		beumRifle.amoMax = 999;
		beumRifle.amo = beumRifle.amoMax;

		// �e���쐬
		GameObjectPtr bullet = GameObject::Create(CreateObjectType::Empty);

		MeshRendererPtr render = bullet->AddComponent<MeshRenderer>();
		render->mesh = assetManager->GetStaticMesh("Gundam/BeumRifleBullet");
		render->shader = assetManager->GetShader(DefalutShader::Standard3D);

		SphereColliderPtr col = bullet->AddComponent<SphereCollider>();
		col->isTrigger = true;

		auto homing = bullet->AddComponent<HomingBullet>();
		homing->SetParamater(70.0f, 200.0f, 5.0f, 0.4f);

		beumRifle.bullet = bullet;
	}
}

/**
* ���t���[�����s
*/
void Gundam::Update()
{
	if (!Check())
	{
		return;
	}

	Move(msInput->moveAxis);
	Dash(msInput->moveAxis, msInput->dashBtn);
	Jump(msInput->moveAxis, msInput->jumpBtn);
	BeumRifleShot(msInput->action1Btn);
}

/**
* �K�v�ȃR���|�[�l���g�A�ϐ����擾�ł��Ă��邩�`�F�b�N
*
* @retval true	�擾�ł��Ă���
* @retval false	�K�v�Ȃ��̂�����Ă��Ȃ�
*/
bool Gundam::Check()
{
	if (!rb)
	{
		return false;
	}
	if (!renderer)
	{
		return false;
	}
	if (!anim)
	{
		return false;
	}
	if (!msInput)
	{
		return false;
	}
	if (!GetTrsCamera())
	{
		return false;
	}

	return true;
}

/**
* �A�C�h���A�j���[�V�������Đ��\���`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::IdleAnimationCheck() const
{
	if (beumRifle.isNow)
	{
		return false;
	}
	return true;
}

/**
* �A�C�h����Ԃɂ���
*/
void Gundam::IdleAnimation() const
{
	if (!IdleAnimationCheck())
	{
		return;
	}
	if (handArmed == HandArmed::Rifle)
	{
		anim->SetAnimation(AnimationName::IdleRifle, true);
	}
	else
	{
		anim->SetAnimation(AnimationName::IdleSable, true);
	}
	anim->Play();
}

#pragma region Move

/**
* �ړ��ł��邩�`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::MoveCheck() const
{
	if (jump.isNow || dash.isNow)
	{
		return false;
	}
	return true;
}

/**
* �ړ�����
*/
void Gundam::Move(const Vector2& moveAxis)
{
	Vector3 moveFoward = MoveForward(moveAxis);

	if (rb->IsGround())
	{
		// �ړ������ł��邩�`�F�b�N
		if (!MoveCheck())
		{
			return;
		}

		// �g�����X�t�H�[�����擾
		TransformPtr transform = GetTransform();

		// �i�s�����ɕ�Ԃ��Ȃ����]
		if (moveFoward != Vector3::zero)
		{
			transform->rotation = Quaternion::Slerp(transform->rotation,
				Quaternion::LookRotation(moveFoward), move.rotationSpeed);
			transform->position += transform->Forward() * move.speed * Time::DeltaTime();

			MoveAnimation();
		}
		else
		{
			IdleAnimation();
		}
	}
}

/**
* �ړ��A�j���[�V�������Đ��\���`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::MoveAnimationCheck() const
{
	if (!beumRifle.isNow)
	{
		return false;
	}
	return true;
}

/**
* �ړ��A�j���[�V�����̏���
*/
void Gundam::MoveAnimation() const
{
	if (MoveAnimationCheck())
	{
		return;
	}

	if (handArmed == HandArmed::Rifle)
	{
		anim->SetAnimation(AnimationName::RunRifle, true);
	}
	else
	{
		anim->SetAnimation(AnimationName::RunSable, true);
	}
	anim->Play();
}

#pragma endregion

#pragma region Dash

/**
* �_�b�V���ł��邩�`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::DashCheck() const
{
	return true;
}

/**
* �_�b�V������
*/
void Gundam::Dash(const Vector2& moveAxis, bool isBtn)
{
	// �_�b�V�����͂������
	if (isBtn)
	{
		// �_�b�V���\���`�F�b�N
		if (!DashCheck())
		{
			return;
		}
		if (boost.current > 0)
		{
			// �g�����X�t�H�[�����擾
			TransformPtr transform = GetTransform();

			// �d�͂𖳌���
			rb->isGravity = false;

			// �ړ��������擾
			Vector3 moveFoward = MoveForward(moveAxis);

			// �i�s�����ɕ�Ԃ��Ȃ����]
			if (moveFoward != Vector3::zero)
			{
				transform->rotation = Quaternion::Slerp(transform->rotation,
					Quaternion::LookRotation(moveFoward), dash.rotationSpeed);
			}
			transform->position += transform->Forward() * dash.speed * Time::DeltaTime();

			// �A�j���[�V�����؂�ւ�
			DashAnimation();

			// �_�b�V����Ԃɂ���
			dash.isNow = true;
		}
	}
	else
	{
		if (dash.isNow)
		{
			// �d�͂�L��
			rb->isGravity = true;

			// �_�b�V����Ԃ�����
			dash.isNow = false;

			// �A�j���[�V�����؂�ւ�
			IdleAnimation();
		}
	}
}

/**
* �_�b�V���A�j���[�V�������Đ��\���`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::DashAnimationCheck() const
{
	if (beumRifle.isNow)
	{
		return false;
	}
	return true;
}

/**
* �_�b�V���A�j���[�V�����̏���
*/
void Gundam::DashAnimation() const
{
	if (DashAnimationCheck())
	{
		return;
	}
	// �_�b�V�����Ă��Ȃ��Ƃ��ɃA�j���[�V��������
	if (!dash.isNow)
	{
		if (handArmed == HandArmed::Rifle)
		{
			anim->SetAnimation(AnimationName::Dash::Rifle);
		}
		else
		{
			anim->SetAnimation(AnimationName::Dash::Sable);
		}
		anim->Play();
	}
}

#pragma endregion

#pragma region Jump

/**
* �W�����v�\���`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::JumpCheck() const
{
	if (dash.isNow)
	{
		return false;
	}
	return true;
}

/**
* �W�����v����
*/
void Gundam::Jump(const Vector2& moveAxis, bool isBtn)
{
	// �W�����v�\���`�F�b�N
	if (!JumpCheck())
	{
		return;
	}

	// �W�����v���͂������
	if (isBtn)
	{
		if (boost.current > 0)
		{
			// �g�����X�t�H�[�����擾
			TransformPtr transform = GetTransform();

			// �d�͂𖳌���
			rb->velocity = Vector3::zero;
			rb->isGravity = false;

			// �ړ��������擾
			Vector3 moveFoward = MoveForward(moveAxis);

			// �i�s�����ɕ�Ԃ��Ȃ����]
			if (moveFoward != Vector3::zero)
			{
				transform->rotation = Quaternion::Slerp(transform->rotation,
					Quaternion::LookRotation(moveFoward), jump.rotationSpeed);
				transform->position += transform->Forward() * jump.speed * Time::DeltaTime();
			}

			// �㏸
			transform->position.y += jump.power * Time::DeltaTime();

			// �A�j���[�V�����؂�ւ�
			JumpAnimation();

			// �W�����v��Ԃɂ���
			jump.isNow = true;
		}
	}
	else
	{
		// �W�����v���������ꍇ
		if (jump.isNow)
		{
			// �d�͂�L��
			rb->isGravity = true;

			// �W�����v��Ԃ�����
			jump.isNow = false;

			// �A�j���[�V�����؂�ւ�
			IdleAnimation();
		}
	}
}

/**
* �W�����v�A�j���[�V�������Đ��\���`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::JumpAnimationCheck() const
{
	if (beumRifle.isNow)
	{
		return false;
	}
	return true;
}

/**
* �W�����v�A�j���[�V�����̏���
*/
void Gundam::JumpAnimation() const
{
	if (!JumpAnimationCheck())
	{
		return;
	}

	// �W�����v���ĂȂ��ꍇ�̂݃A�j���[�V�������Đ�����
	if (!jump.isNow)
	{
		// �n�ʂɂ��Ă�����
		if (rb->IsGround())
		{
			if (handArmed == HandArmed::Rifle)
			{
				anim->SetAnimation(AnimationName::Jump::GroundRifle);
			}
			else
			{
				//anim->SetAnimation(AnimationName::Jump::GroundSable);
				anim->SetAnimation(AnimationName::Jump::GroundRifle);
			}
		}
		else
		{
			if (handArmed == HandArmed::Rifle)
			{
				anim->SetAnimation(AnimationName::Jump::Rifle);
			}
			else
			{
				anim->SetAnimation(AnimationName::Jump::Sable);
			}
		}
		anim->Play();
	}
}

#pragma endregion

#pragma region BeumRifleShot

/**
* �r�[�����C�t���ˌ����ł��邩�`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::BeumRifleShotCheck() const
{
	if (beumRifle.isNow)
	{
		return false;
	}

	return true;
}

/**
* �r�[�����C�t���ˌ�����
*/
void Gundam::BeumRifleShot(bool isBtn)
{
	// �ˌ����͂�����ꍇ
	if (isBtn)
	{
		if (!BeumRifleShotCheck())
		{
			return;
		}

		// �r�[�����C�t���ɒe������Ύˌ�����
		if (beumRifle.amo > 0)
		{
			beumRifle.isNow = true;
			// �n���h���������C�t���ɂ���
			handArmed = HandArmed::Rifle;
		}
	}

	// �ˌ���
	if (beumRifle.isNow)
	{
		BeumRifleShotAnimaion();

		// ���܂��ɒe���ł���ĂȂ��ăA�j���[�V�����̍Đ����Ԃ����ˎ��ԂɂȂ�����e�𔭎�
		if (anim->time > beumRifle.shotTime && !beumRifle.isShot)
		{
			// �c�e�����炷
			beumRifle.amo -= 1;

			TransformPtr trs = GetTransform();

			// �^�[�Q�b�g�̕������擾
			Vector3 directionToTarget;
			if (GetTarget())
			{
				directionToTarget = Vector3::Normalize(GetTarget()->GetTransform()->position - trs->position);
			}
			else
			{
				directionToTarget = trs->Forward();
			}

			Quaternion rot = Quaternion::LookRotation(directionToTarget);
			// �e�̐����ʒu���v�Z
			Vector3 pos = trs->position + rot * beumRifle.shotPos;

			// �e���쐬
			GameObjectPtr bullet = Instantate(beumRifle.bullet, pos, rot);
			auto homing = bullet->GetComponent<HomingBullet>();
			homing->SetTarget(GetTarget());

			// ������
			beumRifle.isShot = true;
		}
	}
	// �A�j���[�V�������I�������
	if (anim->time >= anim->GetAnimationClip()->totalTime)
	{
		beumRifle.isNow = false;
		beumRifle.isShot = false;
		beumRifle.isBackShot = false;
	}
}

/**
* �r�[�����C�t���ˌ��A�j���[�V�����̏���
*
* @param perY	����Y
* @param dot	����
*/
void Gundam::BeumRifleShotAnimaion()
{
	// �^�[�Q�b�g���������猩�Ăǂ̕����ɂ��邩���ׂ�
	Vector3 directionToTarget = Vector3::Normalize(GetTarget()->GetTransform()->position - GetTransform()->position);
	const float perendicularY = Vector3::Cross(directionToTarget, GetTransform()->Forward()).y;
	const float dot = Vector3::Dot(directionToTarget, GetTransform()->Forward());
	if (dot < -0.5f && !beumRifle.isBackShot)
	{
		beumRifle.isBackShot = true;
		anim->SetAnimation(AnimationName::BeumRifleShot::Idle::B);
		anim->Play();
	}

	if (!beumRifle.isBackShot)
	{
		// ����
		if (msInput->moveAxis != Vector2::zero)
		{
			// �O��
			if (dot > 0.9f)
			{
				if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::F)
				{
					const float time = anim->time;
					anim->SetAnimation(AnimationName::BeumRifleShot::Run::F);
					anim->time = time;
					anim->Play();
				}
			}
			// �E��
			else if (perendicularY < 0)
			{
				if (dot > 0.6f)
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::FR)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Run::FR);
						anim->time = time;
						anim->Play();
					}
				}
				else
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::R)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Run::R);
						anim->time = time;
						anim->Play();
					}
				}
			}
			// ����
			else if (perendicularY > 0)
			{
				if (dot > 0.6f)
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::FL)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Run::FL);
						anim->time = time;
						anim->Play();
					}
				}
				else
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Run::L)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Run::L);
						anim->time = time;
						anim->Play();
					}
				}
			}
		}
		// �A�C�h��
		else
		{
			// �O��
			if (dot > 0.9f)
			{
				if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::F)
				{
					const float time = anim->time;
					anim->SetAnimation(AnimationName::BeumRifleShot::Idle::F);
					anim->time = time;
					anim->Play();
				}
			}
			// �E��
			else if (perendicularY < 0)
			{
				if (dot > 0.6f)
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::FR)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Idle::FR);
						anim->time = time;
						anim->Play();
					}
				}
				else
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::R)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Idle::R);
						anim->time = time;
						anim->Play();
					}
				}
			}
			// ����
			else if (perendicularY > 0)
			{
				if (dot > 0.6f)
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::FL)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Idle::FL);
						anim->time = time;
						anim->Play();
					}
				}
				else
				{
					if (anim->GetAnimationClip()->name != AnimationName::BeumRifleShot::Idle::L)
					{
						const float time = anim->time;
						anim->SetAnimation(AnimationName::BeumRifleShot::Idle::L);
						anim->time = time;
						anim->Play();
					}
				}
			}
		}
	}
}

#pragma endregion