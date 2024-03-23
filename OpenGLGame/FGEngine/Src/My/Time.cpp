/**
* @file Texture.cpp
*/
#include "Time.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{

	float Time::_deltaTime = 0;
	double Time::previousTime = 0;

	/// <summary>
	/// 更新処理
	/// </summary>
	void Time::Update()
	{
		// デルタタイム(前回の更新からの経過時間を計算)
		// glfwGetTime()プログラム起動してからの経過時間
		const double currentTime = glfwGetTime(); // 現在の時刻
		// deltaTime = 現在の時刻 - 前回更新時の時刻
		_deltaTime = static_cast<float>(currentTime - previousTime);
		previousTime = currentTime;

		// 経過時間が長すぎる場合は適当に短くする(主にデバック対策)
		if (_deltaTime >= 0.5f)
		{
			_deltaTime = 1.0f / 60.0f;
		}
	}
}