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

	// HP‚ªƒ[ƒ‚É‚È‚Á‚½‚ç‹@”\’âŽ~
	if (myMs->GetHP() <= 0)
	{
		return;
	}

	auto targetMs = otherOwner->myMs;

	// Ž©g‚ÌMS‚É‘ŠŽè‚ÌMs‚Ìî•ñ‚ð“`‚¦‚é
	myMs->SetTargetMS(targetMs.get());

	// Cpu‚ÌˆÚ“®ˆ—
	myMs->CpuMove();
}

void CpuControl::LateUpdate()
{
}
