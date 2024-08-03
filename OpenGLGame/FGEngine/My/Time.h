/**
* @file Time.h
*/
#ifndef FGENGINE_TIME_H_INCLUDED
#define FGENGINE_TIME_H_INCLUDED
#include "SystemFrd.h"

namespace FGEngine
{
	/**
	* ���ԃN���X
	*/
	class Time
	{
		friend  MainSystem::EngineCore;

	public:

		// �R���X�g���N�^
		Time() = default;

		/**
		* �O��̍X�V����̌o�ߎ��Ԃ��擾
		* 
		* @return �O��̍X�V����̌o�ߎ���
		*/
		static float DeltaTime();

	private:

		/**
		* ���Ԃ��X�V
		*/
		static void Update();

	private:

		// �O��̍X�V����̌b�ʎ���
		static float deltaTime;

		// �O��̍X�V����
		static double previousTime;
	};
}
#endif // !TIME_H_INCLUDED
