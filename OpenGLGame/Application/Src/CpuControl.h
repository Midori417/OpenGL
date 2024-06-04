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
	* コントロールをスタートさせる
	*/
	virtual void ControlStart() override;

	/**
	* ゲーム入力を更新
	*/
	virtual void GameInputUpdate() override;

	/**
	* 終了処理
	*/
	virtual void Finish(VictoryState victoryState) override;

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

		// 攻撃
		Attack,

		// 攻撃2
		Attack2,

		// 攻撃3
		Attack3,

		// ダッシュライフル
		DashAttack,

		Max,
	};
	int cpuState = 0;

	// CPU用の仮想軸
	Vector2 cpuMoveAxis = Vector2::zero;

	// 軸配列
	std::vector<Vector2> moveAxiss;

	// ターゲットナンバー
	int targetNum = 0;

	// 次の移動方向を変更タイマー
	float moveTimer = 0;

	// 次の移動方向を変更するまでの時間
	float moveTime = 0;

	// 次の行動を変更タイマー
	float cpuTimer = 0;

	// 次の行動を変更するまでの時間
	float cpuTime = 0;
};

#endif // !CPU_H_INCLUDED
