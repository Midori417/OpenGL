/**
* @file Texture.cpp
*/
#include "Time.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{

	float Time::_deltaTime = 0;
	double Time::previousTime = 0;

	/// <summary>
	/// �X�V����
	/// </summary>
	void Time::Update()
	{
		// �f���^�^�C��(�O��̍X�V����̌o�ߎ��Ԃ��v�Z)
		// glfwGetTime()�v���O�����N�����Ă���̌o�ߎ���
		const double currentTime = glfwGetTime(); // ���݂̎���
		// deltaTime = ���݂̎��� - �O��X�V���̎���
		_deltaTime = static_cast<float>(currentTime - previousTime);
		previousTime = currentTime;

		// �o�ߎ��Ԃ���������ꍇ�͓K���ɒZ������(��Ƀf�o�b�N�΍�)
		if (_deltaTime >= 0.5f)
		{
			_deltaTime = 1.0f / 60.0f;
		}
	}
}