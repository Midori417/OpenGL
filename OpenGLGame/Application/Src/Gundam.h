/**
* @file Gundam.h
*/
#ifndef GUNDAM_H_INCLUDED
#define GUNDAM_H_INCLUDED
#include "BaseMS.h"

// 先行宣言
class PlayerManager;
class PlayerController;
using PlayerControllerPtr = std::shared_ptr<PlayerController>;


/**
* ガンダム
*/
class Gundam : public BaseMS
{
public:

	// コンストラクタ
	Gundam() = default;

	// デストラクタ
	virtual ~Gundam() = default;

	virtual void Awake() override;
	
private:

	// イベント
	virtual void Start() override;
	virtual void Update() override;

	void Move();

	void Jump(const Vector3& moveForward);

	void Dash(const Vector3& moveForward);

	void IntervalUpdate();

private:


	// 入力コンポーネント
	PlayerControllerPtr msInput;

	// 移動パラメータ
	struct MoveParameter
	{
		float speed = 10.0f;				// 移動速度
		float rotationSpeed = 0.02f;		// 移動旋回速度
		float jumpPower = 7.0f;				// ジャンプ力
		float dashSpeed = 13.0f;			// ダッシュ移動速度
		float moveTimer = 0;
	};
	MoveParameter moveParameter;

	// 射撃パラメータ
	struct ShotParameter : NumArmer
	{
		float shotAnimTimer = 0;
		float timer = 0;
		float interval = 1;
		Vector3 shotPos = Vector3(0.6f, 0.8f, -0.8f);
	};
	ShotParameter shotParameter;

	// 近接攻撃
	struct SableParameter
	{
		float timer = 0;
		float interval = 0.3f;
		float moveTimer = 0;
		Vector3 sablePos = Vector3(0, 0, -1.0f);
	};
	SableParameter sableParameter;

	// ステート
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

	// アニメーションの状態
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

	// デフォ武器状態
	enum class DefaultWeapon
	{
		Magunam,
		Sable,
	};
	DefaultWeapon defaultWeapon = DefaultWeapon::Magunam;


	// キャラクターコンポーネント
	RigidbodyPtr characterMovement;
	GltfAnimatedMeshRendererPtr renderer;

};
#endif // !GUNDAM_H_INCLUDED