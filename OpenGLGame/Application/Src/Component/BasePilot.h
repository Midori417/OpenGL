/**
* @file BasePilot.h
*/
#ifndef BASEPILOT_H_INCLUDED
#define BASEPILOT_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;


// 先行宣言
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class CameraManager;
using CameraManagerPtr = std::shared_ptr<CameraManager>;
enum class VictoryState;
struct GameInput;
using GameInputPtr = std::shared_ptr<GameInput>;

/**
* パイロットの基底コンポーネント
*/
class BasePilot : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	BasePilot() = default;

private: // イベント

	/**
	* 特にクローンする予定がないので何も書かない
	*/
	virtual ComponentPtr Clone() const override
	{
		return nullptr;
	}

public:

	/**
	* コントロールをスタートさせる
	*/
	virtual void ControlStart(){}

	/**
	* 自チームと相手チームの体力を設定
	* 
	* @param myTeamHp		自チームの体力ポインター
	* @param otherTeamHp	相手チームの体力ポインター
	*/
	void SetTeamHP(int* myTeumHp, int* otherTeumHp);

	/**
	* 終了
	*/
	virtual void Finish(VictoryState victoryState){}

	/**
	* チーム体力を無限にする
	*/
	void TeamHPInivinit();

protected:

	/**
	* コントロールの初期化
	*/
	void Initialize();

	/**
	* 自身の機が死亡しときの処理
	*/
	void MyMsDeadUpdate();

	/**
	* ゲーム入力を更新
	*/
	virtual void GameInputUpdate(){}

	/**
	* ターゲットの処理
	*/
	void TargetUpdate();

	/**
	* 自チームの体力を取得
	*/
	int& MyTeamHp() const;

	/**
	* 相手チームの体力を取得
	*/
	int& OtherTeamHp() const;

	/**
	* チーム体力を減らす
	*/
	void TeumHpSud();

	/**
	* 距離を取得
	*/
	float GetDistance();

	/**
	* チーム体力が無限かどうか
	*/
	bool GetTeumHPInifinit() const;

public:

	// カメラ管理マネージャー
	CameraManagerPtr myCamera = nullptr;

	// 自分の機体
	BaseMsPtr myMs = nullptr;

	// 自チームの別オーナ
	BasePilot* myTeamOtherOwner = nullptr;

	// 相手チームのオーナ配列
	std::vector<BasePilot*> otherTeamOwner;

	// 復活位置配列
	std::vector<Vector3> responPoss;

protected:

	// ゲーム入力
	GameInputPtr gameInput;

	// コントロールのスタートの有無
	bool isStart = false;

	// 自分のMSの死亡の有無
	bool isMsDeath = false;

	// 現在のターゲットオーナー
	BasePilot* targetOwner = nullptr;

	// 入力を更新するか
	bool isInputUpdate = true;

	// 復活タイマー
	float responTimer = 0;

	// 復活するまでの時間
	float responTime = 3.0f;

private:

	// 自チームの体力
	int* myTeamHp = 0;

	// 相手チームの体力
	int* otherTeamHp = 0;

	// true = チーム体力∞
	bool isTeamHpInfinit = false;
};

#endif // !BASEPILOT_H_INCLUDED
