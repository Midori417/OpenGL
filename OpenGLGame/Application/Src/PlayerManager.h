/**
* @file PlayerManager.h
*/
#ifndef PLAYERMANAGER_H_INCLUDED
#define PLAYERMANAGER_H_INCLUDEED
#include "FGEngineSub.h"
using namespace FGEngine;

// 先行宣言
class BaseMS;
using BaseMSPtr = std::shared_ptr<BaseMS>;
class CameraMove;
using CameraMovePtr = std::shared_ptr<CameraMove>;

/**
* プレイヤー管理クラス
*/
class PlayerManager : public MonoBehaviour
{
public:

	// コンストラクタ
	PlayerManager() = default;

	// デストラクタ
	virtual ~PlayerManager() = default;

	// 生成イベント
	virtual void Awake() override;

	// 距離の取得
	float GetDistance() const;

private:

	// イベント
	virtual void Start() override;
	virtual void Update() override;

public:

	BaseMSPtr myMs;				// ガンダムコンポーネント
	BaseMSPtr enemyMs;		// ターゲットコンポーネント
	CameraMovePtr cameraMove;	// カメラの挙動コンポーネント

	// UI
	ImagePtr imgHpBack;			// Hpの背景
	TextPtr txtHp;
	ImagePtr imgBoostbarBack;	// Boostbarの背景
	ImagePtr imgBoostbar;		// boostbar
	ImagePtr imgTargetMark;		// ターゲットカーソル
	ImagePtr imgTargetMsInfo;	// ターゲット情報
	ImagePtr imgTargetMSHpBar;
	std::vector<ImagePtr> imgWeaponBacks;		
	std::vector<ImagePtr> imgWeaponIcons;		
	std::vector<TextPtr> txtWeapons;
};

#endif // !PLAYERMANAGER_H_INCLUDED
