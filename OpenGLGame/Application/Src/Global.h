/**
* @file Global.h
*/
#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include "MsList.h"
#include <memory>
#include <vector>

// チーム最大体力
static const int teamMaxHp = 6000;

// 最大プレイヤー数
static const int playerMax = 4;

/**
* 勝敗状態
*/
enum class VictoryState
{
	// 何もなし
	None,

	// 勝利
	Win,

	// 敗北
	Lose,

	// 引き分け
	Drow,
};

/**
* コントロール情報
*/
struct ControlInfo
{
	// チームId
	// 0 = 出場無し, 1 = チーム１, 2 = チーム2
	int teamId = -1;

	// PlayerId
	// 0 = 人間 , 1 = CPU
	int playerId = -1;

	// 使うMS
	MsList ms;
};
using ControlInfoPtr = std::shared_ptr<ControlInfo>;

/**
* バトル前情報
*/
struct BattleInfo
{
	// チーム1体力
	// -1 = ∞
	int team1Hp = teamMaxHp;

	// チーム2体力
	// -1 = ∞
	int team2Hp = teamMaxHp;

	// ゲーム時間
	// -1 = ∞
	float time = 0;

	// コントロール情報配列
	std::vector<ControlInfoPtr> controlInfo;
};

#endif // !GLOBAL_H_INCLUDED
