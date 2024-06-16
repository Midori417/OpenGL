/**
* @file SmokeEffect.h
*/
#ifndef SMOKEEFFECT_H_INCLUDED
#define SMOKEEFFECT_H_INCLUDED
#include "FGEngine.h"
using namespace FGEngine;

class SmokeEffect : public MonoBehaviour
{
public:

	SmokeEffect() = default;
	virtual ~SmokeEffect() = default;

	virtual void Start() override;

	virtual void LateUpdate() override;

	ParticleParameter pp;
	ParticleEmitterParameter ep;
};

#endif // !SMOKEEFFECT_H_INCLUDED
