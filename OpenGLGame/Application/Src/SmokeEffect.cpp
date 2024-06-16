#include "SmokeEffect.h"

void SmokeEffect::Start()
{
}

void SmokeEffect::LateUpdate()
{
	auto rot = GetTransform()->rotation;
	auto pos = GetTransform()->position;
	auto p = Instantate("p", pos, rot);
	auto ps = p->AddComponent<ParticleSystem>();
	ps->emitters.resize(1);
	auto& emi = ps->emitters[0];
	emi.ep.texture = ep.texture;
	emi.ep.duration = 0.5f;
	emi.ep.emissionsPerSecond = 50;
	emi.ep.gravity = 0;
	emi.pp.scale.Set(Vector3(5), Vector3(1));
	emi.pp.color.Set(Color::gree, Color::lighGree);
	emi.pp.lifeTime = 0.3f;

}
