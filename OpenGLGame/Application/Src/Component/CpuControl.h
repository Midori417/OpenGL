/**
* @file CpuControl.h
*/
#ifndef CPUCONTROL_H_INCLUDED
#define CPUCONTROL_H_INCLUDED
#include "BaseControl.h"

/**
* CPU操作コンポーネント
*/
class CpuControl : public BaseControl
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	CpuControl() = default;

private:

	/**
	* Updateが始まる前に一度実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* 特にクローンする予定がないので何も書かない
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

private:

	/**
	* 機体の操作を更新
	*/
	virtual void GameInputUpdate() override;

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

#endif // !CPUCONTROL_H_INCLUDED
