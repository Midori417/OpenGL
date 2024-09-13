/**
* @file BaseControl.h
*/
#ifndef BASECONTROL_H_INCLUDED
#define BASECONTROL_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

#include "../GameInput.h"

// 先行宣言
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class LookOnCamera;
using LookOnCameraPtr = std::shared_ptr<LookOnCamera>;

/**
* MSコントロールの基底コンポーネント
*/
class BaseControl : public GameEvent
{
protected: // このコンポーネント継承先で実体化する

	/**
	* デフォルトコンストラクタ
	*/
	BaseControl() = default;

public:

	/**
	* 開始合図
	*/
	void StartOk();

protected:

	/**
	* コントロールの初期化
	*/
	void Initialize();

	/**
	* 開始されているか取得
	*/
	bool IsStart() const;

	/**
	* ターゲットとの距離を計算
	*/
	bool GetDistance() const;

	/**
	* ターゲットの状態を更新
	*/
	void TargetUpdate();

	/**
	* 機体の操作を更新
	*/
	virtual void GameInputUpdate(){}

protected:

	// 機体の操作入力
	GameInputPtr gameInput = nullptr;

public:

	// 自身のカメラ
	LookOnCameraPtr myCamera = nullptr;

	// 自身の機体
	BaseMsPtr myMs = nullptr;

	// 自チームの別コントロール
	BaseControl* myTeamOtherControl = nullptr;

	// 相手チームのコントローラ配列
	std::vector<BaseControl*> otherTeamControls;

private:

	// 現在のターゲットコントロール
	BaseControl* targetControl = nullptr;

	// 開始したらtrue
	bool isStart = false;
};

#endif // !BASECONTROL_H_INCLUDED
