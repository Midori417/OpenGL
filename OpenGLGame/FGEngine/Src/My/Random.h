/**
* @file Random.h
*/
#ifndef FGENGINE_RANDOM_H_INCLUDED
#define FGENGINE_RANDOM_H_INCLUDED

namespace FGEngine
{
	/**
	* ランダム関数を管理
	*/
	struct Random
	{
		/**
		* 乱数を初期化する
		*
		* @param seed 乱数の種
		*/
		static void Initialize(int seed);

		/**
		* 0.0～1.0の範囲の一様乱数を取得する
		*
		* @return 生成した乱数
		*/
		static float Value();

		/**
		* 指定された範囲の一様乱数を取得する
		*
		* @param min 生成範囲の最小値
		* @param max 生成範囲の最大値
		*
		* @return 生成した乱数
		*/
		static float Range(float min, float max);

		static int Range(int min, int max);
	};
}
#endif // !RANDOM_H_INCLUDED
