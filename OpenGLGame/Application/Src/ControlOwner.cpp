#include "ControlOwner.h"
#include "BaseMs.h"

void ControlOwner::TeumHpSud()
{
	*myTeumHp -= myMs->GetCost();
}
