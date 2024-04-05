/**
* @file InputGamePad.h
*/
#ifndef FGENGINE_INPUTGAMEPAD_H_INCLUDED
#define FGENGINE_INPUTGAMEPAD_H_INCLUDED

namespace FGEngine::InputSystem
{
	/**
	* ゲームパパッドの入力
	*/
	class InputGamePad
	{
	public:

		// コンストラクタ・デストラクタ
		InputGamePad() = default;
		~InputGamePad() = default;

	private:

		/**
		* ゲームパッドの状態を更新
		*/
		static void Update();

	private:

	};
}
#endif // !FGENGINE_INPUTGAMEPAD_H_INCOLUDED
