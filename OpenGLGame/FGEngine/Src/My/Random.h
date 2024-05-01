/**
* @file Random.h
*/
#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDEC

/**
* ���������@�\���i�[���閼�O���
*/
namespace Random
{

	// ������������
	void Initialize(int seed);

	// 0.0�`1.0�͈̔͂̈�l�������擾����
	float Value();

	// �w�肳�ꂽ�͈͂̈�l�������擾����
	float Range(float min, float max);
}

#endif // !RANDOM_H_INCLUDED
