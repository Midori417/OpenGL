/**
* @file Time.h
*/
#ifndef FGENGINE_TIME_H_INCLUDED
#define FGENGINE_TIME_H_INCLUDED
#include "SystemFrd.h"

namespace FGEngine
{
	/**
	* 時間クラス
	*/
	class Time
	{
		friend  MainSystem::EngineCore;

	public:

		// コンストラクタ
		Time() = default;

		/**
		* 前回の更新からの経過時間を取得
		* 
		* @return 前回の更新からの経過時間
		*/
		static float DeltaTime();

	private:

		/**
		* 時間を更新
		*/
		static void Update();

	private:

		// 前回の更新からの恵果時間
		static float deltaTime;

		// 前回の更新時間
		static double previousTime;
	};
}
#endif // !TIME_H_INCLUDED
