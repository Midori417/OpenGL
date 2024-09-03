/**
* @file InputKey.cpp
*/
#include "FGEngine/Input/InputKey.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	std::vector<InputKey::KeyState> InputKey::keyState;
	bool InputKey::anyKey = false;

	/**
	* �L�[�{�[�h���X�g�Ή��r�b�g�}�b�v
	*/
	const int KEY_ASSIGN[(int)KeyCode::Max]
	{
		GLFW_KEY_ENTER,

		GLFW_KEY_ESCAPE,
		GLFW_KEY_F1,
		GLFW_KEY_F2,
		GLFW_KEY_F3,
		GLFW_KEY_F4,
		GLFW_KEY_F5,
		GLFW_KEY_F6,
		GLFW_KEY_F7,
		GLFW_KEY_F8,
		GLFW_KEY_F9,
		GLFW_KEY_F10,
		GLFW_KEY_F11,
		GLFW_KEY_F12,

		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_4,
		GLFW_KEY_5,
		GLFW_KEY_6,
		GLFW_KEY_7,
		GLFW_KEY_8,
		GLFW_KEY_9,
		GLFW_KEY_0,

		GLFW_KEY_TAB,
		GLFW_KEY_Q,
		GLFW_KEY_W,
		GLFW_KEY_E,
		GLFW_KEY_R,
		GLFW_KEY_T,
		GLFW_KEY_Y,
		GLFW_KEY_U,
		GLFW_KEY_I,
		GLFW_KEY_O,
		GLFW_KEY_P,

		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_D,
		GLFW_KEY_F,
		GLFW_KEY_G,
		GLFW_KEY_H,
		GLFW_KEY_J,
		GLFW_KEY_K,
		GLFW_KEY_L,
		GLFW_KEY_SEMICOLON,

		GLFW_KEY_LEFT_SHIFT,
		GLFW_KEY_Z,
		GLFW_KEY_X,
		GLFW_KEY_C,
		GLFW_KEY_V,
		GLFW_KEY_B,
		GLFW_KEY_N,
		GLFW_KEY_M,
		GLFW_KEY_COMMA,
		GLFW_KEY_RIGHT_SHIFT,

		GLFW_KEY_LEFT_CONTROL,
		GLFW_KEY_LEFT_ALT,
		GLFW_KEY_SPACE,
		GLFW_KEY_RIGHT_CONTROL,

		GLFW_KEY_UP,
		GLFW_KEY_DOWN,
		GLFW_KEY_LEFT,
		GLFW_KEY_RIGHT,
	};

	/**
	* �L�[�{�[�h���͂�������
	*
	* @retval true	����ɏ�����
	* @retval false	���������s
	*/
	bool FGEngine::InputKey::Initialize()
	{
		// �L�[��Ԕz��𐶐�
		keyState.resize((int)KeyCode::Max);

		return true;
	}

	/**
	* �L�[�{�[�h�̏�Ԃ��X�V
	* 
	* @param window �E�B���h�E�I�u�W�F�N�g
	*/
	void InputKey::Update(GLFWwindow* window)
	{
		anyKey = false;

		for (int i = 0; i < (int)KeyCode::Max; ++i)
		{
			// ������Ă��邩��擾
			const bool now = glfwGetKey(window, KEY_ASSIGN[i]) == GLFW_PRESS;

			// ��ł�������Ă�����true
			if (now)
			{
				anyKey = true;
			}

			// ������Ă��邩
			keyState[i].on = now;

			// ����������������
			// ���݉�����Ă��āA�O�񉟂���Ă��Ȃ�
			keyState[i].down = now && !keyState[i].old;

			// ����������������
			// ���݉�����Ă��Ȃ��A�O�񉟂���Ă���
			keyState[i].up = !now && keyState[i].old;

			// ���ɑO��̏�Ԃ��g�����߂����ő��
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
		return keyState[int(keyCode)].up;
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
		if (keyCode == KeyCode::Max) 
		{
			return false;
		}
		return keyState[int(keyCode)].down;
	}

	/**
	* ��������̃L�[��������Ă��邩�擾
	*
	* @retval true ������Ă���
	* @retval false ������Ă��Ȃ�
	*/
	bool InputKey::AnyKey()
	{
		return anyKey;
	}
}