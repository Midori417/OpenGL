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
	* 入力管理クラス
	*/
	class InputManager : public Singleton<InputManager>
	{
	private:

		friend MainSystem::EngineCore;
		friend Singleton<InputManager>;

		// コンストラクタ
		InputManager() = default;

		/**
		* 入力を更新
		* 
		* @param window オブジェクトオブジェクト
		*/
		void Update(GLFWwindow* window);
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
