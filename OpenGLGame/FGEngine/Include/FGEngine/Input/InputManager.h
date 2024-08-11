/**
* @file InputManager.h
*/
#ifndef FGENGINE_INPUTMANAGER_H_INCLUDED
#define FGENGINE_INPUTMANAGER_H_INCLUDED
#include "FGEngine/SystemFrd.h"
#include "FGEngine/Singleton.h"
#include <string>
#include <unordered_map>

struct GLFWwindow;

enum class Axis
{
	Horizontal,

	Vertical,
};

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
		* インプットマネージャーを初期化
		*/
		int Initialize();

		/**
		* 入力を更新
		* 
		* @param window オブジェクトオブジェクト
		*/
		void Update(GLFWwindow* window);

		/**
		* Axisの更新
		*/
		static void AxisUpdate();

	public:

		/**
		* Axisを取得
		* 
		* @parma axis アクシズ名
		*/
		static float GetAxis(Axis axis);

	private:

		// axis配列
		static std::unordered_map<Axis, float> axisList;
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
