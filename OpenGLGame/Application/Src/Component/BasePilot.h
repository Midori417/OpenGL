/**
* @file BasePilot.h
*/
#ifndef BASEPILOT_H_INCLUDED
#define BASEPILOT_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

#include "../GameInput.h"

// 先行宣言
class BasePilot;
using BasePilotPtr = std::shared_ptr<BasePilot>;
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class CameraManager;
using CameraManagerPtr = std::shared_ptr<CameraManager>;

/**
* パイロットの基底コンポーネント
*/
class BasePilot : public GameEvent
{
protected: // 派生先で生成する

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

protected:

	/**
	* 初期化
	*/
	void Initialize();

public: // セッター

	/**
	* パートナーパイロットを設定
	* 
	* @param 設定するパートナーパイロット
	*/
	void SetPartnerPilot(const BasePilotPtr& pilot);

	/**
	* 相手チームのパイロットを設定
	* 
	* @param 設定する相手チームのパイロット
	*/
	void SetOtherTeamPilot(const BasePilotPtr& pilot);

protected: // パートナー関係

	/**
	* パートナーパイロットを取得
	*/
	BasePilot* GetPartnerPilot() const;

	/**
	* パートナーの機体を取得
	*/
	BaseMsPtr GetPartnerMs() const;

protected: // 相手チーム関係

	/**
	* 相手チームのパイロットを取得
	* 
	* @param index パイロット番号
	*/
	BasePilot* GetOtherTeamPilot(size_t index) const;

	/**
	* 相手チームの機体を取得
	*
	* @param index パイロット番号
	*/
	BaseMsPtr GetOtherTeamMs(size_t index) const;

	/**
	* 相手チームのパイロットの数を取得
	*/
	size_t GetOtherTeamPilotSize() const;

protected: // ターゲット関係

	/**
	* ターゲットパイロットを取得
	*/
	BasePilot* GetTargetPilot() const;

	/**
	* ターゲット機体を取得
	*/
	BaseMsPtr GetTargetMs() const;

public:

	// カメラ管理マネージャー
	CameraManagerPtr myCamera = nullptr;

	// 自分の機体
	BaseMsPtr myMs = nullptr;

	// 復活位置配列
	std::vector<Vector3> responPoss;

protected:

	// ゲーム入力
	GameInputPtr gameInput;

private:

	// 現在のターゲットパイロット
	BasePilot* targetPilot = nullptr;

	// パートナーパイロット
	BasePilot* partnerPilot = nullptr;

	// 相手チームパイロット配列
	std::vector<BasePilot*> otherTeamPilots;
};

#endif // !BASEPILOT_H_INCLUDED
