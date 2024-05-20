/**
* @file BattleManager.h
*/
#ifndef BATTLEMANAGER_H_INCLUDED
#define BATTLEMANAGER_H_INCLUDED
#include "FGEngine.h"
#include "MsLilst.h"
using namespace FGEngine;
using namespace FGEngine::UI;

class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;

class ControlOwner;
using ControlOwnerPtr = std::shared_ptr<ControlOwner>;

class BattleManager : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	BattleManager() = default;
	virtual ~BattleManager() = default;


	/**
	* 生成時に実行
	*/
	virtual void Awake() override;

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
	* msに対応するコンポーネントをobjに追加する
	*
	* @param obj 追加するオブジェクト
	* @param ms 追加したいコンポーネントに対応するMsList
	*/
	BaseMsPtr SetMs(GameObjectPtr obj,  MsList ms);

public:

	// マップの大きさ横
	float mapX;

	// マップの大きさ縦
	float mapZ;

private:

	// ゲーム状態
	enum class GameState
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
	GameState state = GameState::Ready;

	// タイマー
	float timer = 0;

	float readyTime = 1.5f;

	// スタンバイ時間
	const float standbayTime = 2;

	// ゴータイム
	const float goTime = 1;

	// プレイヤー
	ControlOwnerPtr playerControl;

	// 敵
	ControlOwnerPtr cpuControl;

	// チーム1体力
	std::shared_ptr<int> teum1Hp = 0;

	// チーム2体力
	std::shared_ptr<int> teum2Hp = 0;

	// UI
	ImagePtr imgStandbay;
	ImagePtr imgGo;
	ImagePtr imgGoBack;
	ImagePtr imgWin;
	ImagePtr imgLose;
};


#endif // !BATTLEMANAGER_H_INCLUDED
