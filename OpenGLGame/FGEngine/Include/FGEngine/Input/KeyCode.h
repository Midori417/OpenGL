/**
* @file KeyCode.h
*/
#ifndef FGENGINE_KEYCODE_H_INCLUDED
#define FGENGINE_KEYCODE_H_INCLUDED
#include <GLFW/glfw3.h>

namespace FGEngine::InputSystem
{
	/**
	* キーボードリスト
	*/
	enum class KeyCode
	{
		Enter,

		Escape,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		F11,
		F12,
		Alpha1,
		Alpha2,
		Alpha3,
		Alpha4,
		Alpha5,
		Alpha6,
		Alpha7,
		Alpha8,
		Alpha9,
		Alpha0,

		Tab,
		Q,
		W,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,

		A,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		Semiclon,

		LeftShift,
		Z,
		X,
		C,
		V,
		B,
		N,
		M,
		Comma,
		RightShift,

		LeftControl,
		LeftAlt,
		Space,
		RightControl,

		UpArrow,
		DownArrow,
		LeftArrow,
		RightArrow,

		Max,

	};

	/**
	* キーボードリスト対応ビットマップ
	*/
	const int KEY_ASSIGN[(int)KeyCode::Max]
	{
		GLFW_KEY_ENTER,

		GLFW_KEY_ESCAPE,
		GLFW_KEY_F1,
		GLFW_KEY_F2,
		GLFW_KEY_F3,
		GLFW_KEY_F4,
		GLFW_KEY_F5,
		GLFW_KEY_F6,
		GLFW_KEY_F7,
		GLFW_KEY_F8,
		GLFW_KEY_F9,
		GLFW_KEY_F10,
		GLFW_KEY_F11,
		GLFW_KEY_F12,

		GLFW_KEY_1,
		GLFW_KEY_2,
		GLFW_KEY_3,
		GLFW_KEY_4,
		GLFW_KEY_5,
		GLFW_KEY_6,
		GLFW_KEY_7,
		GLFW_KEY_8,
		GLFW_KEY_9,
		GLFW_KEY_0,

		GLFW_KEY_TAB,
		GLFW_KEY_Q,
		GLFW_KEY_W,
		GLFW_KEY_E,
		GLFW_KEY_R,
		GLFW_KEY_T,
		GLFW_KEY_Y,
		GLFW_KEY_U,
		GLFW_KEY_I,
		GLFW_KEY_O,
		GLFW_KEY_P,

		GLFW_KEY_A,
		GLFW_KEY_S,
		GLFW_KEY_D,
		GLFW_KEY_F,
		GLFW_KEY_G,
		GLFW_KEY_H,
		GLFW_KEY_J,
		GLFW_KEY_K,
		GLFW_KEY_L,
		GLFW_KEY_SEMICOLON,

		GLFW_KEY_LEFT_SHIFT,
		GLFW_KEY_Z,
		GLFW_KEY_X,
		GLFW_KEY_C,
		GLFW_KEY_V,
		GLFW_KEY_B,
		GLFW_KEY_N,
		GLFW_KEY_M,
		GLFW_KEY_COMMA,
		GLFW_KEY_RIGHT_SHIFT,

		GLFW_KEY_LEFT_CONTROL,
		GLFW_KEY_LEFT_ALT,
		GLFW_KEY_SPACE,
		GLFW_KEY_RIGHT_CONTROL,

		GLFW_KEY_UP,
		GLFW_KEY_DOWN,
		GLFW_KEY_LEFT,
		GLFW_KEY_RIGHT,

	};

}
#endif // !KEYCODE_H_INCLUDED
