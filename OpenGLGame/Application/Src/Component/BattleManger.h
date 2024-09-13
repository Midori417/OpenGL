/**
* @file BattleManager.h
*/
#ifndef BATTLEMANAGER_H_INCLUDED
#define BATTLEMANAGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
#include "FGEngine/Math/Vector3.h"
using namespace FGEngine;

// 先行宣言
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;
class BaseMs;
using BaseMsPtr = std::shared_ptr<BaseMs>;
class BaseControl;
using BaseControlPtr = std::shared_ptr<BaseControl>;
struct BattleSettingInfo;
using BattleSettingInfoPtr = std::shared_ptr<BattleSettingInfo>;
enum class MsList;

/**
* バトルシーン管理コンポーネント
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
	* Updateが始まる前に一度実行
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

private:

	/**
	* バトルルールを設定する
	*/
	void BattleSetting();

	/**
	* msに対応するコンポーネントをobjに追加する
	*
	* @param obj 追加するオブジェクト
	* @param ms 追加したいコンポーネントに対応するMsList
	*/
	BaseMsPtr SetMs(GameObjectPtr& obj, MsList ms);

	/**
	* チームを設定する
	* 
	* @param control	設定するコントロール
	* @param id			チームID
	*/
	void SetTeum(const BaseControlPtr& control, int id);

public:

	/**
	* リスポーン位置を設定
	* 
	* @param poses 設定したいリスポーン位置配列
	*/
	void SetResponPos(const std::vector<Vector3>& poses);

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

	// バトル時間
	float battleTime = 0;

private:

	// シーン切り替え時のフェードアウトコンポーネント
	FadeOutPtr fadeOut = nullptr;

	// 決定音を鳴らすためのコンポーネント
	AudioSourcePtr audioSource = nullptr;

	// 復帰位置
	// 配列 0=Teum1,1 = Teum2の初期位置
	std::vector<Vector3> responPoses;

private:

	// バトル設定シーンで設定した情報
	BattleSettingInfoPtr battleSettingInfo = nullptr;

	// チーム1体力
	std::shared_ptr<int> teum1Hp = 0;

	// チーム1を体力無限にするか
	bool isTeum1HpInfinity = false;

	// チーム2体力
	std::shared_ptr<int> teum2Hp = 0;

	// チーム2を体力無限にするか
	bool isTeum2HpInfinity = false;

	// コントロールオーナ配列
	std::vector<BaseControlPtr> controls;

	// チーム１コントロール配列
	std::vector<BaseControlPtr> teum1Controls;

	// チーム2コントロール配列
	std::vector<BaseControlPtr> teum2Controls;

private: // UI

	// スタンバイを表示するイメージコンポーネント
	ImagePtr imgStandbay = nullptr;

	// ゴーを表示するイメージコンポーネント
	ImagePtr imgGo = nullptr;
};

#endif // !BATTLEMANGER_H_INCLUDED
