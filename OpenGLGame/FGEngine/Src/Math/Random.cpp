/**
* @file Random.cpp
*/
#include "FGEngine/Math/Random.h"
#include <random>

namespace FGEngine
{

	// 乱数生成オブジェクト
	std::random_device rd;
	std::mt19937 randomEngine(rd());

	/**
	* 乱数を初期化する
	*
	* @param seed 乱数の種
	*/
	void Random::Initialize(int seed)
	{
		randomEngine.seed(seed);
	}

	/**
	* 0.0～1.0の範囲の一様乱数を取得する
	*
	* @return 生成した乱数
	*/
	float Random::Value()
	{
		return std::uniform_real_distribution<float>(0, 1)(randomEngine);
	}

	/**
	* 指定された範囲の一様乱数を取得する
	*
	* @param min 生成範囲の最小値(float)
	* @param max 生成範囲の最大値(float)
	*
	* @return 生成した乱数(float)
	*/
	float Random::Range(float min, float max)
	{
		return std::uniform_real_distribution<float>(min, max)(randomEngine);
	}

	/**
	* 指定された範囲の一様乱数を取得する
	*
	* @param min 生成範囲の最小値(int)
	* @param max 生成範囲の最大値(int)
	*
	* @return 生成した乱数(int)
	*/
	int Random::Range(int min, int max)
	{
		return std::uniform_int_distribution<int>(min, max)(randomEngine);
	}
}