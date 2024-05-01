/**
* @file SableAttack.h
*/
#ifndef SABLEATTACK_H_INCLUDED
#define SABLEATTACK_H_INCLUDED
#include "MyEngine.h"

/**
* ‹ßÚUŒ‚
*/
class SableAttack : public Component
{
public:

	SableAttack() = default;
	virtual ~SableAttack() = default;

	virtual void Awake() override;
	virtual void Update() override;
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other) override;

private:

	float atk = 20.0f;
	float destroyTimer = 0;
	float destoryTime = 0.5f;
	int teum = -1;

public:

	void SetAtk(float atk)
	{
		this->atk = atk;
	}
	void SetTeum(int value)
	{
		teum = value;
	}

};

#endif // !SABLEATTACK_H_INCLUDED
