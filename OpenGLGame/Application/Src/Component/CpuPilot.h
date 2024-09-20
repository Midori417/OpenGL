/**
* @file CpuPilot.h
*/
#ifndef CPUPILOT_H_INCLUDED
#define CPUPILOT_H_INCLUDED
#include "BasePilot.h"
#include "FGEngine/Math/Vector2.h"

/**
* コンピュータパイロット
*/
class CpuPilot : public BasePilot
{
public:

	/**
	* デフォルトコンストラクタ
	*/
	CpuPilot() = default;

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
};

#endif // !CPUPILOT_H_INCLUDED