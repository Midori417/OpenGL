/**
* @file HumanControl.h
*/
#ifndef HYUMANCONTROL_H_INCLUDED
#define HYUMANCONTROL_H_INCLUDED
#include "ControlOwner.h"
using namespace FGEngine::UI;

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class ImageBlinking;
using ImageBlinkingPtr = std::shared_ptr<ImageBlinking>;
class ImageNum;
using ImageNumPtr = std::shared_ptr<ImageNum>;

/**
* 人間が操作
*/
class HumanControl : public ControlOwner
{
public:

	// コンストラクタ・デストラクタ
	HumanControl() = default;
	virtual ~HumanControl() = default;


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
	* ゲーム入力を更新
	*/
	virtual void GameInputUpdate() override;

	/**
	* UI処理の更新
	*/
	void UIUpdate();

	/**
	* 終了処理
	*/
	virtual void Finish(VictoryState victoryState) override;

private:

	// 自身の情報背景
	ImagePtr imgMyInfoBack;

	// 自身の機体の体力
	ImageNumPtr inMyMsHp;

	// ブーストバー
	ImagePtr imgBoostBar;

	// ブーストバーの背景
	ImagePtr imgBoostBarBack;

	// ブーストバーのオーバーヒート
	ImagePtr imgBoostBarOverHeat;

	// ブーストバーオーバーヒートーの点滅
	ImageBlinkingPtr ibBoostBarOverHeat;

	// 覚醒バー
	ImagePtr imgBurstBar;

	// 覚醒バーの背景
	ImagePtr imgBurstBarBack;

	// 武器アイコンの背景
	std::vector<ImagePtr> imgWeaponBacks;

	// 武器の残弾
	std::vector<ImageNumPtr> inWeaponAmos;

	// 武器の残弾バー
	std::vector<ImagePtr> imgWeaponBars;

	// 武器のアイコン
	std::vector<ImagePtr> imgWeapnIcons;

	// ターゲットマーク
	ImagePtr imgTargetMark;

	// ターゲットマークのテクスチャ
	TexturePtr texTargetMark01;
	TexturePtr texTargetMark02;
	TexturePtr texTargetMark03;

	// ターゲットの情報
	std::vector<ImagePtr> imgOtherTeumMsInfoBacks;

	// ターゲットの体力バー
	std::vector<ImagePtr> imgOtherTeumMsHpBars;

	ImagePtr imgMyTeumOtherMsInfo;
	ImagePtr imgMyTeumOtherMsHpBar;

	// パートナー機体体力波形
	ImagePtr imgPartnerHpBack;

	// パートナー機体体力
	ImageNumPtr inPartnerMsHp;

	// 時間
	ImagePtr imgTimer;

	// チーム体力のフレーム
	ImagePtr imgTeamHpFrame;

	// 自チームの体力バー
	ImagePtr imgMyTeamHpBar;

	// 相手チームの体力バー
	ImagePtr imgOtherTeamHpBar;

	// 勝利
	ImagePtr imgWin;

	// 敗北
	ImagePtr imgLose;
};


#endif // !PLAYER_H_INCLUDED
