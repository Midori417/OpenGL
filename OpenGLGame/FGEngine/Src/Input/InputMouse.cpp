/**
* @file InputMouse.cpp
*/
#include "FGEngine/Input/InputMouse.h"
#include "FGEngine/Input/MouseButton.h"
//#include "FGEngine/Time.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	/**
	* �}�E�X�{�^�����X�g�Ή��r�b�g�}�b�v
	*/
	const int MOUSEBUTTON_ASSIGN[(int)MouseButton::Max]
	{
		GLFW_MOUSE_BUTTON_LEFT,
		GLFW_MOUSE_BUTTON_RIGHT,
		GLFW_MOUSE_BUTTON_MIDDLE,
	};

	/**
	* �}�E�X���͂�������
	*
	* @retval 0		����ɏ�����
	* @retval 0�ȊO	�G���[����
	*/
	int InputMouse::Initialize()
	{
		// �}�E�X�{�^���z����m��
		mouseButtonsState.resize((int)MouseButton::Max);

		return 0;
	}

	/**
	* �}�E�X�̏�Ԃ��X�V
	*
	* @param window �E�B���h�E�I�u�W�F�N�g
	*/
	void InputMouse::Update(GLFWwindow* window)
	{
		for (int i = 0; i < (int)MouseButton::Max; ++i)
		{
			// ���݂̃}�E�X�̏�Ԃ��擾����
			const bool now = glfwGetMouseButton(window, MOUSEBUTTON_ASSIGN[i]) == GLFW_PRESS;
			mouseButtonsState[i].on = now;

			// �O��̃t���[���ŉ�����ĂȂ��Č��݂̃t���[���ŉ�����Ă����牟�����������ɂ���
			mouseButtonsState[i].down = now && !mouseButtonsState[i].old;

			// �O��̃t���[����������Ă��Č��݂̃t���[����������ĂȂ���Ή������������ɂ���
			mouseButtonsState[i].up = !now && mouseButtonsState[i].old;

			// ������Ă��鎞�Ԃ��X�V
			if (mouseButtonsState[i].old)
			{
				//mouseButtonsState[i].timer += Time::DeltaTime();
			}
			else
			{
				mouseButtonsState[i].timer = 0;
			}
			// �ȉ��̏��������ׂĖ������ꍇ�̓N���b�N�Ɣ���
			// - �O�t���[���ŉ�����Ă���
			// - ���݂̃t���[���ŉ�����Ă��Ȃ�
			// - ������Ă��鎞�Ԃ�0.3�b�ȉ�
			if (mouseButtonsState[i].old && !mouseButtonsState[i].on && mouseButtonsState[i].timer <= mouseClickSpeed)
			{
				mouseButtonsState[i].click = true;
			}
			else
			{
				mouseButtonsState[i].click = false;
			}

			// �O��̃t���[���̍X�V
			mouseButtonsState[i].old = now;
		}
	}

	/**
	* �}�E�X�̈ʒu���擾
	*/
	Vector2 InputMouse::GetMousePosition()
	{
		return mousePosition;
	}

	/**
	* �}�E�X�̃{�^���������Ă�����擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true	�����Ă���
	* @retval false	�����Ă��Ȃ�
	*/
	bool InputMouse::GetMouseButton(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].on;
	}

	/**
	* �}�E�X�̃{�^�����オ���������擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true	�����������Ă���
	* @retval false	�����グ���Ă��Ȃ�
	*/
	bool InputMouse::GetMouseButtonUp(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].up;
	}

	/**
	* �}�E�X�̃{�^�����������������擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true	������������
	* @retval false	�����������Ă��Ȃ�
	*/
	bool InputMouse::GetMouseButtonDown(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].down;
	}

	/**
	* �}�E�X���N���b�N���������擾
	*
	* @param mouseButton �Ή����Ă���{�^��
	*
	* @retval true �N���b�N����
	* @retval false �N���b�N���Ă��Ȃ�
	*/
	bool InputMouse::GetMouseButtonClick(MouseButton mouseButton)
	{
		if (mouseButton == MouseButton::Max)
		{
			return false;
		}
		return mouseButtonsState[(int)mouseButton].click;
	}

}