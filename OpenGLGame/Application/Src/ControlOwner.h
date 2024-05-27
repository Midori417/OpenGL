/**
* @file ControlOwner.h
*/
#ifndef CONTROLOWNER_H_INCLUDED
#define CONTROLOWNER_H_INCLUDED
#include "FGEngine.h"
#include "MsLilst.h"
using namespace FGEngine;

// 先行宣言
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;
enum class VictoryState;
struct GameInput;
using GameInputPtr = std::shared_ptr<GameInput>;

/**
* 操作
*/
class ControlOwner : public MonoBehaviour
{
public:

	// コンストラクタ・デストラクタ
	ControlOwner() = default;
	virtual ~ControlOwner() = default;

	/**
	* コントロールをスタートさせる
	*/
	void StartOk();

	/**
	* 自チームと相手チームの体力を設定
	* 
	* @param myTeumHp		自チームの体力ポインター
	* @param otherTeumHp	相手チームの体力ポインター
	*/
	void SetTeumHP(int* myTeumHp, int* otherTeumHp);

	/**
	* 終了
	*/
	virtual void Finish(VictoryState victoryState){}


protected:

	/**
	* コントロールの初期化
	*/
	void Initialize();

	/**
	* ゲーム入力を更新
	*/
	virtual void GameInputUpdate(){}


	/**
	* 自チームの体力を取得
	*/
	int& MyTeumHp() const;

	/**
	* 相手チームの体力を取得
	*/
	int& OtherTeumHp() const;

	/**
	* チーム体力を減らす
	*/
	void TeumHpSud();

	/**
	* 距離を取得
	*/
	float GetDistance();

public:

	// カメラ
	LookOnCameraPtr myCamera = nullptr;

	// 自分の機体
	BaseMsPtr myMs = nullptr;

	// 自チームの別オーナ
	ControlOwner* myTeumOtherOwner = nullptr;

	// 相手チームのオーナ配列
	std::vector<ControlOwner*> otherTeumOwner;

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
	ControlOwner* targetOwner = nullptr;

	// Msの操作できるか
	bool isMsControl = true;

	// 復活タイマー
	float responTimer = 0;

	// 復活するまでの時間
	float responTime = 3.0f;

private:

	// 自チームの体力
	int* myTeumHp = 0;

	// 相手チームの体力
	int* otherTeumHp = 0;

};


#endif // !CONTROLOWNER_H_INCLUDED
