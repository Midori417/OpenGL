/**
* @file GamePad.h
*/
#ifndef GAMEPAD_H_INCLUDED
#define GAMEPAD_H_INCLUDED

namespace FGEngine
{
	struct DpadControl
	{
		bool up = false;
		bool right = false;
		bool down = false;
		bool left = false;
	};

	struct StickControl
	{
		float x = 0;
		float y = 0;
	};

	/**
	* ゲームパッド
	*/
	class GamePad
	{
	private:
		GamePad() = default;
		~GamePad() = default;

	public:

		static void DestoryGamePad();


		static GamePad* GetGamePad();

		static void Update();

		int GetPadId();


		bool leftStickButton();
		bool rightStickButton();
		DpadControl dpad();
		bool leftShoulder();
		bool rightShoulder();
		StickControl leftStick();
		StickControl rightStick();
		bool leftTrigger();
		bool rightTrigger();
		bool aButton();
		bool bButton();
		bool xButton();
		bool yButton();
		bool triangleButton();
		bool squareButton();
		bool circleButton();
		bool crossButton();

	private:

		static GamePad* gamepad;
		static float* axes;
		static unsigned char* buttons;

		static int padId;
	};
}
#endif // !GAMEPAD_H_INCLUDED
