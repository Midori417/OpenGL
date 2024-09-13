/**
* @file BattleSettingManager.h
*/
#ifndef BATTLESETTINGMANAGER_H_INCLUDED
#define BATTLESETTINGMANAGER_H_INCLUDED
#include "FGEngine/Component/GameEvent.h"
using namespace FGEngine;

// 先行宣言
class FadeOut;
using FadeOutPtr = std::shared_ptr<FadeOut>;

/**
* バトル設定シーン管理コンポーネント
*/
class BattleSettingManager : public GameEvent
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	BattleSettingManager() = default;

private:

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
	* 選択項目
	*/
	enum Select
	{
		// バトル開始
		BattleStart,

		// 設定シーンに戻る
		Espace,
	};
	Select select = Select::BattleStart;

	// シーン切り替え時のフェードアウトコンポーネント
	FadeOutPtr fadeOut = nullptr;

	// 決定音を鳴らすためのコンポーネント
	AudioSourcePtr audioSource = nullptr;
};

#endif // !BATTLESETTINGMANAGE_H_INCLUDED
