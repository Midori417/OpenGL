/**
* @file CpuControl.h
*/
#ifndef CPUCONTROL_H_INCLUDED
#define CPUCONTROL_H_INCLUDED
#include "ControlOwner.h"

/**
* コンピュータ操作
*/
class CpuControl : public ControlOwner
{
public:

	// コンストラクタ・デストラクタ
	CpuControl() = default;
	virtual ~CpuControl() = default;

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* 機体の更新
	*/
	virtual void MsUpdate() override;

	/**
	* 終了
	*/
	virtual void Finish() override;

private:

	/**
	* CPUの行動
	*/
	enum CpuState
	{
		// 何もしない
		None,

		// ダッシュ
		Dash,

		// ジャンプ
		Jump,

		// ライフル
		Attack,

		// ダッシュライフル
		DashAttack,

		Max,
	};
	int cpuState = 0;

	Vector2 cpuMoveAxis = Vector2::zero;

	std::vector<Vector2> moveAxiss;
	float moveTimer = 0;
	float moveTime = 0;

	float cpuTimer = 0;

	// 次の行動を決めるまでの時間
	float cpuTime = 0;
};

#endif // !CPU_H_INCLUDED
