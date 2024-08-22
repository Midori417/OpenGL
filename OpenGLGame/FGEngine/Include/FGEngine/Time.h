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
	public:		// �R���X�g���N�^

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Time() = default;

	public:

		/**
		* �O��̍X�V����̌o�ߎ��Ԃ��擾
		* 
		* @return �O��̍X�V����̌o�ߎ���
		*/
		static float DeltaTime();

		/**
		* FPS���擾
		*/
		static float Fps();

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

		// FPS�p�ϐ�
		static double fpsTime;
		static double fps;
		static int fpsFrames;
	};
}
#endif // !TIME_H_INCLUDED
