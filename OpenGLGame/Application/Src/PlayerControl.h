/**
* @file Player.h
*/
#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "ControlOwner.h"
using namespace FGEngine::UI;

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;
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
	* MSの更新
	*/
	void MsUpdate();

	/**
	* UI処理の更新
	*/
	void UIUpdate();

public:
	
	// カメラ
	LookOnCameraPtr lookOnCamera;

private:

	ImagePtr imgPlayerInfo;
	ImageNumPtr numPlayerImage;
	ImagePtr imgBoostBar;
	ImagePtr imgBoostBarBack;
	ImagePtr imgBoostBarOverHeat;
	ImageBlinkingPtr ibBoostBarOverHeat;
	ImagePtr imgBurstBar;
	ImagePtr imgBurstBarBack;
	std::vector<ImagePtr> imgWeaponBack;
	ImagePtr imgTargetMark;
	TexturePtr texTargetMark01;
	TexturePtr texTargetMark02;
	TexturePtr texTargetMark03;
	ImagePtr imgTargetInfo;
	ImagePtr imgTargetHPBar;
	ImagePtr imgTimer;
	ImagePtr imgTeumFrame;
	ImagePtr imgTeumHpBar;
	ImagePtr imgTeumEnemyBar;

	// 距離
	float distance = 0;
};


#endif // !PLAYER_H_INCLUDED
