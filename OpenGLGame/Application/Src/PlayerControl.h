/**
* @file Player.h
*/
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "ControlOwner.h"
using namespace FGEngine::UI;

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class ImageBlinking;
using ImageBlinkingPtr = std::shared_ptr<ImageBlinking>;
class ImageNum;
using ImageNumPtr = std::shared_ptr<ImageNum>;

/**
* プレイヤー操作
*/
class PlayerControl : public ControlOwner
{
public:

	// コンストラクタ・デストラクタ
	PlayerControl() = default;
	virtual ~PlayerControl() = default;


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
	* 毎フレーム実行(Updateより後)
	*/
	virtual void LateUpdate() override;

	/**
	* 機体の更新
	*/
	virtual void MsUpdate() override;

	/**
	* UI処理の更新
	*/
	void UIUpdate();

	/**
	* 終了
	*/
	virtual void Finish() override;

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
	ImagePtr imgTargetInfo;

	// ターゲットの体力バー
	ImagePtr imgTargetHPBar;

	// 時間
	ImagePtr imgTimer;

	// チーム体力のフレーム
	ImagePtr imgTeumHpFrame;

	// 自チームの体力バー
	ImagePtr imgMyTeumHpBar;

	// 相手チームの体力バー
	ImagePtr imgEnemyTeumHpBar;

};


#endif // !PLAYER_H_INCLUDED
