/**
* @file InputManager.h
*/
#ifndef FGENGINE_INPUTMANAGER_H_INCLUDED
#define FGENGINE_INPUTMANAGER_H_INCLUDED
#include "SystemFrd.h"
#include "Singleton.h"
#include <string>
#include <unordered_map>

struct GLFWwindow;

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

	public:

		/**
		* Axis���擾
		* 
		* @parma axis �A�N�V�Y��
		*/
		static float GetAxis(const std::string& axis);

	private:

		// axis�z��
		std::unordered_map<std::string, float> axisList;
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
