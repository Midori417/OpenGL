/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "BaseMS.h"

// ��s�錾
class PlayerManager;
class PlayerController;
using PlayerControllerPtr = std::shared_ptr<PlayerController>;


/**
* �K���_��
*/
class Gundam : public BaseMS
{
public:

	// �R���X�g���N�^
	Gundam() = default;

	// �f�X�g���N�^
	virtual ~Gundam() = default;

	virtual void Awake() override;
	
private:

	// �C�x���g
	virtual void Start() override;
	virtual void Update() override;

	void Move();

	void Jump(const Vector3& moveForward);

	void Dash(const Vector3& moveForward);

	void IntervalUpdate();

private:


	// ���̓R���|�[�l���g
	PlayerControllerPtr msInput;

	// �ړ��p�����[�^
	struct MoveParameter
	{
		float speed = 10.0f;				// �ړ����x
		float rotationSpeed = 0.02f;		// �ړ����񑬓x
		float jumpPower = 7.0f;				// �W�����v��
		float dashSpeed = 13.0f;			// �_�b�V���ړ����x
		float moveTimer = 0;
	};
	MoveParameter moveParameter;

	// �ˌ��p�����[�^
	struct ShotParameter : NumArmer
	{
		float shotAnimTimer = 0;
		float timer = 0;
		float interval = 1;
		Vector3 shotPos = Vector3(0.6f, 0.8f, -0.8f);
	};
	ShotParameter shotParameter;

	// �ߐڍU��
	struct SableParameter
	{
		float timer = 0;
		float interval = 0.3f;
		float moveTimer = 0;
		Vector3 sablePos = Vector3(0, 0, -1.0f);
	};
	SableParameter sableParameter;

	// �X�e�[�g
	enum class State
	{
		None,
		SableMove,
		SableAttack,
		SableAttack02,
		SableAttack03,
		Shot,
		Jump,
		Dash
	};
	State state = State::None;

	// �A�j���[�V�����̏��
	enum class AnimState
	{
		MagunamIdle,
		SableIdle,
		MagunamRun,
		SableRun,
		RunMagunamShot,
		MagunamShot,
		MagunamJump,
		MagunamDash,
		SableJump,
		SableDash,

		SalbeAttackMove,
		SableAttack01,
		SableAttack02,
		SableAttack03

	};
	AnimState animState = AnimState::MagunamIdle;

	// �f�t�H������
	enum class DefaultWeapon
	{
		Magunam,
		Sable,
	};
	DefaultWeapon defaultWeapon = DefaultWeapon::Magunam;


	// �L�����N�^�[�R���|�[�l���g
	RigidbodyPtr characterMovement;
	GltfAnimatedMeshRendererPtr renderer;

};
#endif // !GUNDAM_H_INCLUDED