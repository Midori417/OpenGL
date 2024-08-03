/**
* @file MouseButton.h
*/
#ifndef FGENGINE_MOUSEBUTTON_H_INCLUDED
#define FGENGINE_MOUSEBUTTON_H_INCLUDED

namespace FGEngine
{
	/**
	* マウスボタンリスト
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

}

#endif // !FGENGINE_MOUSEBUTTON_H_INCLUDED
