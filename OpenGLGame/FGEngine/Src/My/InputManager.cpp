/**
* @file InputManager.cpp
*/
#include "InputManager.h"
#include "InputKey.h"
#include "InputMouse.h"

namespace FGEngine::InputSystem
{
	/**
	* �C���v�b�g�}�l�[�W�����X�V
	* 
	* @param window �E�B���h�E�I�u�W�F�N�g
	*/
	void InputManager::Update(GLFWwindow* window)
	{
		// �L�[�{�[�h�̍X�V
		InputKey::Update(window);

		// �}�E�X���X�V
		InputMouse::Update(window);
	}
}