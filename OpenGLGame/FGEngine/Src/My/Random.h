/**
* @file Random.h
*/
#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDEC

namespace FGEngine
{

	/**
	* ���������@�\���i�[���閼�O���
	*/
	struct Random
	{

		// ������������
		static void Initialize(int seed);

		// 0.0�`1.0�͈̔͂̈�l�������擾����
		static float Value();

		// �w�肳�ꂽ�͈͂̈�l�������擾����
		static float Range(float min, float max);
	};
}
#endif // !RANDOM_H_INCLUDED
