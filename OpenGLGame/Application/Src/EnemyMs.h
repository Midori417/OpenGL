/**
* @file EnemyMs.h
*/
#ifndef ENEMYMS_H_INCLUDED
#define ENEMYMS_H_INCLUDED
#include "BaseMS.h"

class EnemyMs : public BaseMS
{
public:

	EnemyMs() = default;
	virtual ~EnemyMs() = default;

	virtual void Awake() override;
	virtual void Damage(float damage) override;

private:

	virtual void Start() override;
	virtual void Update() override;
	virtual void OnCollision(const ComponentPtr& self, const ComponentPtr& other) override;

};
#endif // !ENEMYMS_H_INCLUDED
