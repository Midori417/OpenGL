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
	* �p�[�e�B�N���Ǘ��R���|�[�l���g
	*/
	class ParticleSystem : public Component
	{
	public:

		friend ObjectSystem::ObjectManager;

		// �R���X�g���N�^�E�f�X�g���N�^
		ParticleSystem() = default;
		virtual ~ParticleSystem() = default;

		/**
		* �X�^�[�g����
		*/
		void Start();

		/**
		* �X�V����
		*/
		void Update();

		/**
		* �j�󎞂̏���
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
