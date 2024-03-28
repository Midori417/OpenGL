/**
* @file Time.h
*/
#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED
#include "SystemFrd.h"

namespace FGEngine
{
	class Time
	{
		friend  MainSystem::EngineCore;

	public:

		Time() = default;
		~Time() = default;

		// �f���^�^�C�����擾
		static float deltaTime() {
			return _deltaTime;
		}

	private:

		// �X�V����
		static void Update();

	private:

		static float _deltaTime;
		static double previousTime;
	};
}
#endif // !TIME_H_INCLUDED
