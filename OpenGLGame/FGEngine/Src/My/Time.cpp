/**
* @file Texture.cpp
*/
#include "Time.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// �X�^�e�B�b�N�ϐ��̏�����
	float Time::deltaTime = 0;
	double Time::previousTime = 0;

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

		// �o�ߎ��Ԃ���������ꍇ�͓K���ɒZ������(��Ƀf�o�b�N�΍�)
		if (deltaTime >= 0.5f)
		{
			deltaTime = 1.0f / 60.0f;
		}
	}
}