/**
* @file InputKey.cpp
*/
#include "InputKey.h"

namespace FGEngine::InputSystem
{
	// �X�^�e�B�b�N�ϐ��̏���
	InputKey::KeyState InputKey::keyState[] = { InputKey::KeyState() };

	/**
	* �L�[�{�[�h�̏�Ԃ��X�V
	* 
	* @param window �E�B���h�E�I�u�W�F�N�g
	*/
	void InputKey::Update(GLFWwindow* window)
	{
		for (int i = 0; i < (int)KeyCode::Max; ++i)
		{
			const bool now = glfwGetKey(window, KEY_ASSIGN[i]) == GLFW_PRESS;

			keyState[i].on = now;
			keyState[i].down = now && !keyState[i].old;
			keyState[i].up = !now && keyState[i].old;

			keyState[i].old = now;
		}
	}

	/**
	* �L�[��������Ă��邩���擾
	*
	* @param keyCod	�Ή����Ă���L�[
	*
	* @retval true	�����Ă���
	* @retval false	�����Ă��Ȃ�
	*/
	bool InputKey::GetKey(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max)
		{
			return false;
		}
		return keyState[int(keyCode)].on;
	}

	/**
	* �L�[���オ���������擾
	*
	* @param keyCod	�Ή����Ă���L�[
	*
	* @retval true	�����������Ă���
	* @retval false	�����グ���Ă��Ȃ�
	*/
	bool InputKey::GetKeyUp(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max)
		{
			return false;
		}
		return keyState[int(keyCode)].down;
	}

	/**
	* �L�[���������������擾
	*
	* @param keyCod	�Ή����Ă���L�[
	*
	* @retval true	������������
	* @retval false	�����������Ă��Ȃ�
	*/
	bool InputKey::GetKeyDown(KeyCode keyCode)
	{
		if (keyCode == KeyCode::Max) {
			return false;
		}
		return keyState[int(keyCode)].up;
	}
}