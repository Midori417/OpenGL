/**
* @file BattleSettingManager.h
*/
#ifndef BATTLESETTINGMANAGER_H_INCLUDED
#define BATTLESETTINGMANAGER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

// 先行宣言
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
struct BattleInfo;
using BattleInfoPtr = std::shared_ptr<BattleInfo>;

/**
* バトル設定マネージャ
*/
class BattleSettingManager : public GameEvent
{
public:

	// コンストラクタ・デストラクタ
	BattleSettingManager() = default;
	virtual ~BattleSettingManager() = default;

private:

	/**
	* 生成時に実行
	*/
	virtual void Awake() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

private:

	/**
	* 選択項目
	*/
	enum class Select
	{
		// バトル開始
		BattleStart,

		// 戻る
		Back,
	};
	Select select = Select::BattleStart;

	// バトル情報
	BattleInfoPtr battleInfo;

	// フェードコンポーネント
	FadeOutPtr fadeOut;

};

#endif // !BATTLESETTINGMANAGER_H_INCLUDED
