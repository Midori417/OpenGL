/**
* @file Texture.cpp
*/
#include "FGEngine/Other/Time.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	float Time::deltaTime = 0;
	double Time::previousTime = 0;
	double Time::fps = 0;
	double Time::fpsTime = 0;
	int Time::fpsFrames = 0;

	/**
	* �O��̍X�V����̌o�ߎ��Ԃ��擾
	*
	* @return �O��̍X�V����̌o�ߎ���
	*/
	float Time::DeltaTime()
	{
		return deltaTime;
	}

	/**
	* FPS���擾
	*/
	float Time::Fps()
	{
		return static_cast<float>(fps);
	}

	/**
	* ���Ԃ��X�V
	*/
	void Time::Update()
	{
		// �f���^�^�C��(�O��̍X�V����̌o�ߎ��Ԃ��v�Z)
		// glfwGetTime()�v���O�����N�����Ă���̌o�ߎ���
		const double currentTime = glfwGetTime(); 

		// deltaTime = ���݂̎��� - �O��X�V���̎���
		deltaTime = static_cast<float>(currentTime - previousTime);
		previousTime = currentTime;

		// 1�b���Ƃ�FPS���v�Z����
		const double diffTime = currentTime - fpsTime;
		++fpsFrames;
		if (diffTime >= 1)
		{
			fps = fpsFrames / diffTime;
			fpsFrames = 0;
			fpsTime = currentTime;
		}

		// �o�ߎ��Ԃ���������ꍇ�͓K���ɒZ������(��Ƀf�o�b�N�΍�)
		if (deltaTime >= 0.5f)
		{
			deltaTime = 1.0f / 60.0f;
		}
	}
}