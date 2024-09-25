/**
* @file Gundam.cpp
*/
#include "Gundam.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Other/Time.h"

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

	}
	// �W�����v�p�����[�^
	{
		jump.power = 20.0f;
		jump.speed = 10.0f;
		jump.rotationSpeed = 0.01f;
		jump.useBoost = 30.0f;
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
	Jump(msInput->moveAxis, msInput->jumpBtn);
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
* �A�C�h����Ԃɂ���
*/
void Gundam::IdleAnimation()
{
	if (handWeapon == HandWeapon::Rifle)
	{
		anim->SetAnimation(AnimationName::IdleRifle, true);
	}
	else
	{
		anim->SetAnimation(AnimationName::IdleSable, true);
	}
	anim->Play();
}

/**
* �ړ��ł��邩�`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::MoveCheck() const
{
	if (jump.isNow)
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
		if(moveFoward != Vector3::zero)
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
* �ړ��A�j���[�V�����̏���
*/
void Gundam::MoveAnimation()
{
	if (handWeapon == HandWeapon::Rifle)
	{
		anim->SetAnimation(AnimationName::RunRifle, true);
	}
	else
	{
		anim->SetAnimation(AnimationName::RunSable, true);
	}
	anim->Play();
}

/**
* �W�����v�\���`�F�b�N
*
* @retval true	�\
* @retval false	�s�\
*/
bool Gundam::JumpCheck() const
{
	return true;
}

/**
* �W�����v����
*/
void Gundam::Jump(const Vector2& moveAxis, bool isBtn)
{
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
		}
	}
}

/**
* �W�����v�A�j���[�V�����̏���
*/
void Gundam::JumpAnimation()
{
	// �W�����v���ĂȂ��ꍇ�̂݃A�j���[�V�������Đ�����
	if (!jump.isNow)
	{
		// �n�ʂɂ��Ă�����
		if (rb->IsGround())
		{
			if (handWeapon == HandWeapon::Rifle)
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
			if (handWeapon == HandWeapon::Rifle)
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
