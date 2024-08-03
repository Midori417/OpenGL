/**
* @file InputInterface.h
*/
#ifndef FGENGINE_INPUTINTERFACE_H_INCLUDED
#define FGENGINE_INPUTINTERFACE_H_INCLUDED
#include <memory>

// 先行宣言
struct GLFWwindow;

namespace FGEngine
{
	// 先行宣言
	class InputManager;

	/**
	* 入力デバイスのインターフェイス
	* このクラスが実体化しないためコンストラクタはprotected
	*/
	class InputInterface
	{
		friend InputManager;
	protected:

		/**
		* デフォルトデストラクタ
		*/
		InputInterface() = default;

		/**
		* デフォルトデストラクタ
		*/
		virtual ~InputInterface() = default;

	protected:

		/**
		* 入力の初期化
		* 
		* @retval 0		正常に初期化
		* @retval 0以外	エラー発生
		*/
		virtual int Initialize() = 0;

		/**
		* 入力状態の更新
		*/
		virtual void Update(GLFWwindow* window) = 0;
	};
	using InputInterfacePtr = std::shared_ptr<InputInterface>;
}

#endif // !FGENGINE_INPUTINTERFACE_H_INCLUDED
