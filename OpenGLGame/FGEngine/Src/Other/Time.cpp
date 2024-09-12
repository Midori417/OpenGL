/**
* @file Texture.cpp
*/
#include "FGEngine/Other/Time.h"
#include <GLFW/glfw3.h>

namespace FGEngine
{
	// 静的変数の初期化
	float Time::deltaTime = 0;
	double Time::previousTime = 0;
	double Time::fps = 0;
	double Time::fpsTime = 0;
	int Time::fpsFrames = 0;

	/**
	* 前回の更新からの経過時間を取得
	*
	* @return 前回の更新からの経過時間
	*/
	float Time::DeltaTime()
	{
		return deltaTime;
	}

	/**
	* FPSを取得
	*/
	float Time::Fps()
	{
		return static_cast<float>(fps);
	}

	/**
	* 時間を更新
	*/
	void Time::Update()
	{
		// デルタタイム(前回の更新からの経過時間を計算)
		// glfwGetTime()プログラム起動してからの経過時間
		const double currentTime = glfwGetTime(); 

		// deltaTime = 現在の時刻 - 前回更新時の時刻
		deltaTime = static_cast<float>(currentTime - previousTime);
		previousTime = currentTime;

		// 1秒ごとにFPSを計算する
		const double diffTime = currentTime - fpsTime;
		++fpsFrames;
		if (diffTime >= 1)
		{
			fps = fpsFrames / diffTime;
			fpsFrames = 0;
			fpsTime = currentTime;
		}

		// 経過時間が長すぎる場合は適当に短くする(主にデバック対策)
		if (deltaTime >= 0.5f)
		{
			deltaTime = 1.0f / 60.0f;
		}
	}
}