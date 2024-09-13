/**
* @file HyumanControl.h
*/
#ifndef HYUMANCONTROL_H_INCLUDED
#define HYUMANCONTROL_H_INCLUDED
#include "BaseControl.h"

/**
* 人間が操作
*/
class HyumanControl : public BaseControl
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	HyumanControl() = default;

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
	* 機体の操作を更新
	*/
	virtual void GameInputUpdate() override;

};

#endif // !HYUMANCONTROL_H_INCLUDED
