/**
* @file ParticleSystem.h
*/
#ifndef FGENGINE_PARTICLESYSTEM_H_INCLUDED
#define FGENGINE_PARTICLESYSTEM_H_INCLUDED
#include "MonoBehaviour.h"
#include "Particle.h"

namespace FGEngine
{
	/**
	* パーティクル管理コンポーネント
	*/
	class ParticleSystem : public Component
	{
	public:

		friend ObjectSystem::ObjectManager;

		// コンストラクタ・デストラクタ
		ParticleSystem() = default;
		virtual ~ParticleSystem() = default;

		/**
		* スタート処理
		*/
		void Start();

		/**
		* 更新処理
		*/
		void Update();

		/**
		* 破壊時の処理
		*/
		void OnDestory();

		struct Parameter
		{
			Parameter() = default;
			ParticleEmitterParameter ep;
			ParticleParameter pp;
			ParticleEmitterPtr emitter;
 		};
		std::vector<Parameter> emitters;

	private:

		ObjectSystem::ObjectManager* objManager = nullptr;

		bool isStart = false;
	};
	using ParticleSystemPtr = std::shared_ptr<ParticleSystem>;
}

#endif // !FGENGINE_PARTICLESYSTEM_H_INCLUDED
