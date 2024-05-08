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


};

#endif // !CPU_H_INCLUDED
