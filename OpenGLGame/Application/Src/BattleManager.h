/**
* @file BattleManager.h
*/
#ifndef BATTLEMANAGER_H_INCLUDED
#define BATTLEMANAGER_H_INCLUDED
#include "FGEngine.h"
#include "MsLilst.h"
using namespace FGEngine;
using namespace FGEngine::UI;

// 先行宣言
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class ControlOwner;
using ControlOwnerPtr = std::shared_ptr<ControlOwner>;
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
struct BattleInfo;
using BattleInfoPtr = std::shared_ptr<BattleInfo>;

/**
* バトルマネージャ
*/
class BattleManager : public MonoBehaviour

{
public:

	// コンストラクタ・デストラクタ
	BattleManager() = default;
	virtual ~BattleManager() = default;

	/**
	* バトル情報を設定
	*/
	static void SetBattleInfo(BattleInfoPtr _battleInfo);

	/**
	* リスポーン位置
	*/
	void SetResponPos(const Vector3& pos);
	void SetResponPos(const std::vector<Vector3>& poses);

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
	* msに対応するコンポーネントをobjに追加する
	*
	* @param obj 追加するオブジェクト
	* @param ms 追加したいコンポーネントに対応するMsList
	*/
	BaseMsPtr SetMs(GameObjectPtr obj,  MsList ms);

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

	// バトル情報
	static BattleInfoPtr battleInfo;

	std::vector<ControlOwnerPtr> controlOwners;

	// チーム１コントロール配列
	std::vector<ControlOwnerPtr> teum1ControlOwners;

	// チーム2コントロール配列
	std::vector<ControlOwnerPtr> teum2ControlOwners;
	
	// チーム1体力
	std::shared_ptr<int> teum1Hp = 0;

	// チーム2体力
	std::shared_ptr<int> teum2Hp = 0;

	// 復帰位置
	// 配列 0=Teum1,1 = Teum2の初期位置
	std::vector<Vector3> responPoses;

	// バトルタイム
	float battleTimer = 0;

	// === UI === //

	// スタンバイ
	ImagePtr imgStandbay;

	// ゴー
	ImagePtr imgGo;

	// ゴーの背景
	ImagePtr imgGoBack;

	AudioSourcePtr audioSource;
};


#endif // !BATTLEMANAGER_H_INCLUDED
