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

private:	// バトルセッティング

	/**
	* バトルセッティングで決めた情報をもとにバトルルールを決める
	*/
	void BattleSetting();

	/**
	* オブジェクトを生成しmsに対応したコンポーネントを追加する
	*
	* @param ms 追加したいコンポーネントに対応するMsList
	*/
	BaseMsPtr CreateMs(MsList ms);

	/**
	* チームを設定する
	*
	* @param control	設定するコントロール
	* @param id			チームID
	*/
	void SetTeum(const BasePilotPtr& control, int id);

	/**
	* バトルスタート位置を設定する
	* 
	* @param pilots	配置するパイロット
	* @param id		チームID
	*/
	void SetBattlePosition(const std::vector<BasePilotPtr>& pilots, int id);

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
	BattleState battleState = BattleState::Battle;

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
	int team1Hp = 0;

	// チーム2体力
	int team2Hp = 0;

private:

	// スタンバイ
	ImagePtr imgStandbay;

	// ゴー
	ImagePtr imgGo;

	// シーン切り替え時のフェードアウトコンポーネント
	FadeOutPtr fadeOut = nullptr;

	// BGMを鳴らすコンポーネント
	AudioSourcePtr audioBGM = nullptr;

	// 決定音を鳴らすためのコンポーネント
	AudioSourcePtr audioSE = nullptr;
};

#endif // !BATTLEMANAGER_H_INCLUDED