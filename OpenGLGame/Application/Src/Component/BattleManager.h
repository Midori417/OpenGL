/**
* @file BattleManager.h
*/
#ifndef BATTLEMANAGER_H_INCLUDED
#define BATTLEMANAGER_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

#include "../MsList.h"

// 先行宣言
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class BasePilot;
using BasePilotPtr = std::shared_ptr<BasePilot>;
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
struct BattleInfo;
using BattleInfoPtr = std::shared_ptr<BattleInfo>;

/**
* バトルマネージャ
*/
class BattleManager : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	BattleManager() = default;

private:

	/**
	* 生成時に実行
	*/
	virtual void Awake() override;

	/**
	* 最初に実行
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

public:

	/**
	* バトル情報を設定
	*/
	static void SetBattleInfo(BattleInfoPtr _battleInfo);

	/**
	* リスポーン位置
	*/
	void SetResponPos(const std::vector<Vector3>& poses);

private:

	void BattleSetting();

	/**
	* msに対応するコンポーネントをobjに追加する
	*
	* @param obj 追加するオブジェクト
	* @param ms 追加したいコンポーネントに対応するMsList
	*/
	BaseMsPtr SetMs(GameObjectPtr obj,  MsList ms);

	/**
	* チームを設定する
	*
	* @param control	設定するコントロール
	* @param id			チームID
	*/
	void SetTeum(const BasePilotPtr& control, int id);

private:

	// バトル情報
	static BattleInfoPtr battleInfo;

	// 復帰位置
	// 配列 0=Team1,1 = Teum2の初期位置
	std::vector<Vector3> responPoses;

private:

	/**
	* バトル状態
	*/
	enum class BattleState
	{
		// 準備
		Ready,

		// 待機
		Standbay,

		// スタート
		GO,

		// 戦闘中
		Battle,

		// 勝敗
		Victory,
	};
	BattleState battleState = BattleState::Ready;

	// タイマー
	float timer = 0;

	// 準備時間
	const float readyTime = 1.5f;

	// スタンバイ時間
	const float standbayTime = 2;

	// ゴータイム
	const float goTime = 1;

private:

	// バトルに参加しているパイロット配列
	std::vector<BasePilotPtr> pilots;

	// チーム１のパイロット配列
	std::vector<BasePilotPtr> team1Pilots;

	// チーム2のパイロット配列
	std::vector<BasePilotPtr> team2Pilots;

	// チーム1体力
	std::shared_ptr<int> team1Hp = 0;

	// チーム2体力
	std::shared_ptr<int> team2Hp = 0;

private:

	// スタンバイ
	ImagePtr imgStandbay;

	// ゴー
	ImagePtr imgGo;

	// シーン切り替え時のフェードアウトコンポーネント
	FadeOutPtr fadeOut = nullptr;

	// 決定音を鳴らすためのコンポーネント
	AudioSourcePtr audioSourceSE = nullptr;
};

#endif // !BATTLEMANAGER_H_INCLUDED