/**
* @file HumanPilot.h
*/
#ifndef HYUMANPILOT_H_INCLUDED
#define HYUMANPILOT_H_INCLUDED
#include "BasePilot.h"
#include "FGEngine/Asset/Texture.h"

/**
* 人間パイロット
*/
class HumanPilot : public BasePilot
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	HumanPilot() = default;

private:	// イベント

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

private:

	/**
	* ゲーム入力を更新
	*/
	void GameInputUpdate();

};
#endif // !HYUMANPILOT_H_INCLUDED