/**
* @file Gndam.h
*/
#include "Gundam.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/GltfMeshRenderer.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Component/Animator.h"
#include "FGEngine/Asset/AssetManager.h"
#include "FGEngine/Other/Time.h"

#include "../GameInput.h"

// �T�E���h�̖��O
namespace Sound
{

}

// �I�E�f�B�I�\�[�X�̔ԍ�
namespace AudioIndex
{

}

// �A�j���[�V�����̖��O
namespace Animation
{
	const char idleRifle[] = "Idle.Rifle";
	const char idleSable[] = "Idle.Sable";
	const char runRifle[] = "Run.Rifle";
	const char runSable[] = "Run.Sable";
}

/**
* �������Ɏ��s
*/
void Gundam::Awake()
{
	// �A�Z�b�g�}�l�[�W���[���擾
	auto assetManager = AssetManager::GetInstance();

	OwnerObject()->name = "Gundam";
	OwnerObject()->tag = "MS";

	meshRender = OwnerObject()->AddComponent<GltfMeshRenderer>();
	meshRender->glTFfile = assetManager->GetGltfFile("Gundam");
	meshRender->shader = assetManager->GetShader(DefalutShader::Skeletal3D);
	meshRender->shadowShader = assetManager->GetShader(DefalutShader::ShadowSkeletal3D);

	rb = OwnerObject()->AddComponent<Rigidbody>();
	// �������x���グ�����̂�2�ɂ���
	rb->gravityScale = 2;

	auto col = OwnerObject()->AddComponent<SphereCollider>();
	col->radius = 2.4f;
	col->ceneter = Vector3(0, -2.3f, 0);
	auto col2 = OwnerObject()->AddComponent<SphereCollider>();
	col2->radius = 2.5f;
	col2->ceneter = Vector3(0, -0.4f, -0.2f);

	anim = OwnerObject()->AddComponent<Animator>();
	anim->animationClips = meshRender->glTFfile->animationClips;

	// �p�����[�^��ݒ�
	paramater.hpMax = 600;
	paramater.hp = paramater.hpMax;
	paramater.cost = 2000;

	// �ړ�
	move.speed = 40.0f;
	move.rotationSpeed = 0.05f;

	// �W�����v
	jump.power = 30.0f;
	jump.speed = 10.0f;
	jump.rotationSpeed = 0.05f;
	jump.useEnergy = 30.0f;

	// �_�b�V��
	dash.speed = 40.0f;
	dash.rotationSpeed = 0.01f;
	dash.useEnergy = -30.0f;

	// �����̒ǉ�
	{
		// �r�[�����C�t��
		{

		}
		// �o�Y�[�J
		{

		}
	}
}

/**
* Update���n�܂�O�Ɉ�x���s
*/
void Gundam::Start()
{
	// �ŏ��ɍĐ�����A�j���V���[����ݒ�
	anim->SetAnimation(Animation::idleRifle, true);
	anim->Play();
}

/**
* ���t���[�����s
*/
void Gundam::Update()
{
	// �j�󂳂�Ă����牽�����Ȃ�
	if (IsDestroy())
	{
		return;
	}

	// �j��`�F�b�N
	if (DestroyCheck())
	{
		if (!IsDestroy())
		{
			Destroy();
		}
		return;
	}

	if (gameInput)
	{
		Move(gameInput->moveAxis);
	}
}

/**
* �K���_���R���|�[�l���g���N���[��������
*
* @return �N���[�����ꂽ�K���_���R���|�[�l���g
*/
ComponentPtr Gundam::Clone() const
{
	return ComponentPtr();
}

/**
* �ړ�
*
* @param moveAxis �ړ�����
*/
void Gundam::Move(const Vector2& moveAxis)
{
	// �J�����̈ʒu���擾
	auto cameraTrs = GetCameraTransform();
	if (!cameraTrs)
	{
		return;
	}
	\
		// �J�����̕�������AX-Z�P�ʃx�N�g��(���K��)���擾
		Vector3 cameraForward = Vector3::Normalize(cameraTrs->Forward() * Vector3(1, 0, 1));
	Vector3 moveForward = cameraForward * moveAxis.y + cameraTrs->Right() * moveAxis.x;

	if (rb->IsGround())
	{
		// �i�s�����ɉ�]
		if (moveForward != Vector3::zero)
		{
			GetTransform()->rotation = Quaternion::Slerp(GetTransform()->rotation,
				Quaternion::LookRotation(moveForward), move.rotationSpeed);
		}
		if (moveAxis != Vector2::zero)
		{
			// �I�u�W�F�N�g�̌����Ă�����ɐi��
			GetTransform()->position += GetTransform()->Forward() * move.speed * Time::DeltaTime();

		}
		// �ړ����͂�����Ε����A�j���[�V�������Đ�
		if (moveAxis != Vector2::zero)
		{
			switch (handWeapon)
			{
			case Gundam::HandWeapon::Rifle:
				anim->SetAnimation(Animation::runRifle, true);
				anim->Play();
				break;
			case Gundam::HandWeapon::Sable:
				anim->SetAnimation(Animation::runSable, true);
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
				anim->SetAnimation(Animation::idleRifle, true);
				anim->Play();
				break;
			case Gundam::HandWeapon::Sable:
				anim->SetAnimation(Animation::idleSable, true);
				anim->Play();
				break;
			}
		}
	}
}

