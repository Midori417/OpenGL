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
* �ړ�����
*/
void Gundam::Move(const Vector2& moveAxis)
{
	Vector3 moveFoward = MoveForward(moveAxis);

	if (rb->IsGround())
	{
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