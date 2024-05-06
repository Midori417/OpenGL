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

	public:

		/**
		* Axisを取得
		* 
		* @parma axis アクシズ名
		*/
		static float GetAxis(const std::string& axis);

	private:

		// axis配列
		std::unordered_map<std::string, float> axisList;
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
