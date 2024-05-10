/**
* @file Gundam.cpp
*/
#include "Gundam.h"
using namespace FGEngine::ResouceSystem;
using namespace FGEngine::InputSystem;

/**
* �ŏ��Ɏ��s
*/
void Gundam::Awake()
{
	// ���\�[�X�}�l�[�W���[���擾
	auto resManager = ResouceManager::GetInstance();

	// �`��R���|�[�l���g��ǉ�
	auto renderer = OwnerObject()->AddComponent<GltfMeshRenderer>();
	renderer->glTFfile = resManager->GetGltfFile("Gundam");
	renderer->shader = resManager->GetShader(DefalutShader::Skeletal3D);
	renderer->shadowShader = resManager->GetShader(DefalutShader::ShadowSkeletal3D);

	// �d�͂�ǉ�
	rb = OwnerObject()->AddComponent<Rigidbody>();

	// �R���C�_�[��ǉ�
	auto col = OwnerObject()->AddComponent<AabbCollider>();
	col->min = Vector3(-1, -5.2f, -1);
	col->max = Vector3(1, 2.4f, 1);

	// �A�j���[�^��ǉ�
	anim = OwnerObject()->AddComponent<Animator>();
	anim->animationClips = renderer->glTFfile->animationClips;

	// �ŏ��̃A�j���[�V������ǉ�
	anim->SetAnimation("MagunamIdle", true);
	anim->Play();

	// �X�e�[�^�X��ݒ�
	hpMax = 600;
	hp = hpMax;
	cost = 2000;

	// �ړ��p�����[�^
	moveParamater.speed = 30.0f;
	moveParamater.rotationSpeed = 0.05f;
	moveParamater.dash.speed = 35.0f;
	moveParamater.dash.rotationSpeed = 0.01f;
	moveParamater.jump.power = 10.0f;
}

/**
* ���t���[�����s
*/
void Gundam::Update()
{
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

			// �����A�j���[�V������������
			anim->SetAnimation("MagunamRun", true);
			anim->Play();
		}
		else
		{
			anim->SetAnimation("MagunamIdle", true);
			anim->Play();
		}
	}
}

/**
* CPU�̈ړ�
*/
void Gundam::CpuMove()
{
}

/**
* �W�����v
*/
void Gundam::Jump(bool isJump)
{
	if (moveParamater.dash.isNow)
	{
		return;
	}
	if (isJump)
	{
		rb->velocity.y = 0;
		GetTransform()->position.y += moveParamater.jump.power * Time::DeltaTime();

		if (!moveParamater.jump.isNow)
		{
			moveParamater.jump.isNow = true;
			anim->SetAnimation("MagunamJump");
			anim->Play();
		}
	}
	else
	{
		if (moveParamater.jump.isNow)
		{
			moveParamater.jump.isNow = false;
			anim->SetAnimation("MagunamIdle", true);
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

		if (!moveParamater.dash.isNow)
		{
			// �����A�j���[�V������������
			anim->SetAnimation("MagunamDash", true);
			anim->Play();
		}
		moveParamater.dash.isNow = true;
	}
	else
	{
		if (moveParamater.dash.isNow)
		{
			moveParamater.dash.isNow = false;
			anim->SetAnimation("MagunamIdle", true);
			anim->Play();
		}
	}
}
