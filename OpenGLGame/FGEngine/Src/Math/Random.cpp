/**
* @file Random.cpp
*/
#include "FGEngine/Math/Random.h"
#include <random>

namespace FGEngine
{

	// ���������I�u�W�F�N�g
	std::random_device rd;
	std::mt19937 randomEngine(rd());

	/**
	* ����������������
	*
	* @param seed �����̎�
	*/
	void Random::Initialize(int seed)
	{
		randomEngine.seed(seed);
	}

	/**
	* 0.0�`1.0�͈̔͂̈�l�������擾����
	*
	* @return ������������
	*/
	float Random::Value()
	{
		return std::uniform_real_distribution<float>(0, 1)(randomEngine);
	}

	/**
	* �w�肳�ꂽ�͈͂̈�l�������擾����
	*
	* @param min �����͈͂̍ŏ��l(float)
	* @param max �����͈͂̍ő�l(float)
	*
	* @return ������������(float)
	*/
	float Random::Range(float min, float max)
	{
		return std::uniform_real_distribution<float>(min, max)(randomEngine);
	}

	/**
	* �w�肳�ꂽ�͈͂̈�l�������擾����
	*
	* @param min �����͈͂̍ŏ��l(int)
	* @param max �����͈͂̍ő�l(int)
	*
	* @return ������������(int)
	*/
	int Random::Range(int min, int max)
	{
		return std::uniform_int_distribution<int>(min, max)(randomEngine);
	}
}