/**
* @file BattleSettingInfo.h
*/
#ifndef BATTLESETTINGINFO_H_INCLUDED
#define BATTLESETTINGINFO_H_INCLUDED
#include "MSList.h"
#include <memory>
#include <vector>

// チーム最大体力
static const int teumMaxHp = 6000;

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
	int teumId = -1;

	// PlayerId
	// 0 = 人間 , 1 = CPU
	int playerId = -1;

	// 使うMS
	MsList ms;
};
using ControlInfoPtr = std::shared_ptr<ControlInfo>;

/**
* バトル設定情報
*/
struct BattleSettingInfo
{
	// チーム1体力
	// -1 = ∞
	int teum1Hp = teumMaxHp;

	// チーム2体力
	// -1 = ∞
	int teum2Hp = teumMaxHp;

	// ゲーム時間
	// -1 = ∞
	float time = 0;

	// コントロール情報配列
	std::vector<ControlInfoPtr> controlInfo;
};
using BattleSettingInfoPtr = std::shared_ptr<BattleSettingInfo>;

#endif // !BATTLESETTINGINF_H_INCLUDED