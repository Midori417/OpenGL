/**
* @file InputHelper.h
*/
#ifndef INPUTHELPER_H_INCLUDED
#define INPUTHELPER_H_INCLUDED

namespace FGEngine
{
	/// <summary>
	/// キーの状態
	/// </summary>
	struct StKeyState
	{
	public:

		bool old = false;
		bool down = false;
		bool on = false;
		bool up = false;

		float timer = 0;		// ボタンが押されている時間
		bool push = false;
	};

	/// <summary>
	/// マウスボタンの状態
	/// </summary>
	struct MouseButtonState
	{
	public:
		bool old = false;
		bool down = false;
		bool on = false;
		bool up = false;

		bool current = false;	// 現在フレームのボタンの状態
		bool previous = false;	// 前フレームのボタンの状態
		bool click = false;		// クリックの状態
		float timer = 0;		// ボタンが押されている時間
	};
}
#endif // !INPUTHELPER_H_INCLUDED
