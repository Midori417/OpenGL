/**
* @file Random.cpp
*/
#include "Random.h"
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
	* @param min �����͈͂̍ŏ��l
	* @param max �����͈͂̍ő�l
	*
	* @return ������������
	*/
	float Random::Range(float min, float max)
	{
		return std::uniform_real_distribution<float>(min, max)(randomEngine);
	}
}