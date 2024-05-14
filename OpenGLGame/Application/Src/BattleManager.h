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
class PlayerControl;
using PlayerControlPtr = std::shared_ptr<PlayerControl>;

class CpuControl;
using CpuControlPtr = std::shared_ptr<CpuControl>;

class BattleManager : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	BattleManager() = default;
	virtual ~BattleManager() = default;

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
	};
	GameState state = GameState::GO;

	// タイマー
	float timer = 0;

	float readyTime = 1.5f;

	// スタンバイ時間
	const float standbayTime = 2;

	// ゴータイム
	const float goTime = 1;


	// プレイヤー
	PlayerControlPtr playerControl;

	// 敵
	CpuControlPtr cpuControl;

	// UI
	ImagePtr imgStandbay;
	ImagePtr imgGo;
	ImagePtr imgGoBack;
};


#endif // !BATTLEMANAGER_H_INCLUDED
