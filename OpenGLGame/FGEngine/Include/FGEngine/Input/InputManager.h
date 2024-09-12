/**
* @file InputManager.h
*/
#ifndef FGENGINE_INPUTMANAGER_H_INCLUDED
#define FGENGINE_INPUTMANAGER_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include <unordered_map>

// 先行宣言
struct GLFWwindow;

/**
* 仮想軸
*/
enum class Axis
{
	Horizontal,

	Vertical,
};

namespace FGEngine
{
	/**
	* 入力管理クラス
	*/
	class InputManager : public Singleton<InputManager>
	{
		friend Singleton<InputManager>;
		friend class EngineCore;
	private:

		/**
		* デフォルトコンストラクタ
		*/
		InputManager() = default;

	private: // EngineCoreでしか呼ばない

		/**
		* インプットマネージャーを初期化
		* 
		* @param window ウィンドウオブジェクト
		*
		* @retval true	正常に初期化
		* @retval false	初期化失敗
		*/
		bool Initialize(GLFWwindow* window);

		/**
		* インプットマネージャーの状態を更新
		*/
		void Update();

	private:

		/**
		* Axisの更新
		*/
		void AxisUpdate();

	public:

		/**
		* Axisを取得
		*
		* @parma axis アクシズ名
		*/
		static float GetAxis(Axis axis);

	private:	// 入力管理

		// キー入力管理
		static std::shared_ptr<class InputKey> inputKey;

		// マウス入力管理
		static std::shared_ptr<class InputMouse> inputMouse;

	private:

		// axis配列
		static std::unordered_map<Axis, float> axisList;

		// ウィンドウオブジェクト
		GLFWwindow* window = nullptr;
	};
}

#endif // !FGENGINE_INPUTMANAGER_H_INCLUDED
