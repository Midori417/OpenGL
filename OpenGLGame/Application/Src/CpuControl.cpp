/**
* @file CpuControl.cpp
*/
#include "CpuControl.h"
#include "BaseMs.h"

void CpuControl::Start()
{
}

void CpuControl::Update()
{
	if (!isStart)
	{
		return;
	}

	// HP���[���ɂȂ�����@�\��~
	if (myMs->GetHP() <= 0)
	{
		return;
	}

	auto targetMs = otherOwner->myMs;

	// ���g��MS�ɑ����Ms�̏���`����
	myMs->SetTargetMS(targetMs.get());

	// Cpu�̈ړ�����
	myMs->CpuMove();
}

void CpuControl::LateUpdate()
{
}
