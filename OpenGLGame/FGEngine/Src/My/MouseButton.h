/**
* @file MouseButton.h
*/
#ifndef FGENGINE_MOUSEBUTTON_H_INCLUDED
#define FGENGINE_MOUSEBUTTON_H_INCLUDED
#include <GLFW/glfw3.h>

namespace FGEngine::InputSystem
{
	/**
	* マスボタンリスト
	*/
	enum class MouseButton
	{
		// 左マウスボタン
		LeftButton,

		// 右マウスボタン
		RightButton,

		// 真ん中マウスボタン
		CenterButton,

		// マウス登録ボタンマックス
		Max,
	};


	/**
	* マウスボタンリスト対応ビットマップ
	*/
	const int MOUSEBUTTON_ASSIGN[(int)MouseButton::Max]
	{
		GLFW_MOUSE_BUTTON_LEFT,
		GLFW_MOUSE_BUTTON_RIGHT,
		GLFW_MOUSE_BUTTON_MIDDLE,
	};

}

#endif // !FGENGINE_MOUSEBUTTON_H_INCLUDED
