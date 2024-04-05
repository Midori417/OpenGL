/**
* @file InputManager.h
*/
#ifndef FGENGINE_INPUTMANAGER_H_INCLUDED
#define FGENGINE_INPUTMANAGER_H_INCLUDED
#include "SystemFrd.h"
#include "Singleton.h"
#include <GLFW/glfw3.h>

namespace FGEngine::InputSystem
{
	/**
	* ���͊Ǘ��N���X
	*/
	class InputManager : public Singleton<InputManager>
	{
	private:

		friend MainSystem::EngineCore;
		friend Singleton<InputManager>;

		// �R���X�g���N�^
		InputManager() = default;

		/**
		* ���͂��X�V
		* 
		* @param window �I�u�W�F�N�g�I�u�W�F�N�g
		*/
		void Update(GLFWwindow* window);
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
