/**
* @file ParticleSystem.cpp
*/
#include "ParticleSystem.h"
#include "ObjectManager.h"

namespace FGEngine
{
	void ParticleSystem::Start()
	{
		objManager = ObjectSystem::ObjectManager::GetInstance().get();
	}

	void ParticleSystem::Update()
	{
		for (auto& e : emitters)
		{
			if (!e.emitter)
			{
				e.emitter = objManager->AddParticleEmitter(e.ep, e.pp);
			}
			auto& parameter = e.emitter->GetEmitterParameter();
			parameter.objTransform = GetTransform()->GetWorldTransformMatrix();
			parameter.position = e.ep.position;
		}

		auto itr = std::partition(emitters.begin(), emitters.end(),
			[](const Parameter& p) {
				return !p.emitter->IsDead();
			});
		emitters.erase(itr, emitters.end());

		// 全てのエミッターが死んだらゲームオブジェクトを消す
		if (emitters.empty())
		{
			Destroy(OwnerObject());
		}
	}

	void ParticleSystem::OnDestory()
	{
		for (auto& e : emitters)
		{
			e.emitter->Die();
		}
	}
}