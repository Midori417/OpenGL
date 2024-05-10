/**
* @file CpuControl.h
*/
#ifndef CPUCONTROL_H_INCLUDED
#define CPUCONTROL_H_INCLUDED
#include "ControlOwner.h"

/**
* コンピュータ操作
*/
class CpuControl : public ControlOwner
{
public:

	// コンストラクタ・デストラクタ
	CpuControl() = default;
	virtual ~CpuControl() = default;

private:

	/**
	* 最初に実行
	*/
	virtual void Start() override;

	/**
	* 毎フレーム実行
	*/
	virtual void Update() override;

	/**
	* 毎フレーム実行(Updateより後)
	*/
	virtual void LateUpdate() override;

};

#endif // !CPU_H_INCLUDED
