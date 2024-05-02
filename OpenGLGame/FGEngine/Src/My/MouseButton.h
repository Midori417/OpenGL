/**
* @file MouseButton.h
*/
#ifndef FGENGINE_MOUSEBUTTON_H_INCLUDED
#define FGENGINE_MOUSEBUTTON_H_INCLUDED
#include <GLFW/glfw3.h>

namespace FGEngine::InputSystem
{
	/**
	* �}�X�{�^�����X�g
	*/
	enum class MouseButton
	{
		// ���}�E�X�{�^��
		LeftButton,

		// �E�}�E�X�{�^��
		RightButton,

		// �}�E�X�o�^�{�^���}�b�N�X
		Max,
	};


	/**
	* �}�E�X�{�^�����X�g�Ή��r�b�g�}�b�v
	*/
	const int MOUSEBUTTON_ASSIGN[(int)MouseButton::Max]
	{
		GLFW_MOUSE_BUTTON_LEFT,
		GLFW_MOUSE_BUTTON_RIGHT,
	};

}

#endif // !FGENGINE_MOUSEBUTTON_H_INCLUDED
