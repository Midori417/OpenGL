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
* パイロット情報
*/
struct PilotInfo
{
	// チームId
	// 0 = 出場無し, 1 = チーム１, 2 = チーム2
	int teamId = 0;

	// PlayerId
	// 0 = 人間 , 1 = CPU
	int playerId = -1;

	// 使う機体
	MsList ms;
};

/**
* バトル情報
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

	// パイロット情報
	std::vector<PilotInfo> pilotInfos;
};

#endif // !GLOBAL_H_INCLUDED