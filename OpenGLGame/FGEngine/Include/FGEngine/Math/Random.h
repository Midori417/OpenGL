/**
* @file Random.h
*/
#ifndef FGENGINE_RANDOM_H_INCLUDED
#define FGENGINE_RANDOM_H_INCLUDED

namespace FGEngine
{
	/**
	* �����𐶐�����
	*/
	struct Random
	{
		/**
		* ����������������
		*
		* @param seed �����̎�
		*/
		static void Initialize(int seed);

		/**
		* 0.0�`1.0�͈̔͂̈�l�������擾����
		*
		* @return ������������
		*/
		static float Value();

		/**
		* �w�肳�ꂽ�͈͂̈�l�������擾����
		*
		* @param min �����͈͂̍ŏ��l(float)
		* @param max �����͈͂̍ő�l(float)
		*
		* @return ������������(float)
		*/
		static float Range(float min, float max);

		/**
		* �w�肳�ꂽ�͈͂̈�l�������擾����
		*
		* @param min �����͈͂̍ŏ��l(int)
		* @param max �����͈͂̍ő�l(int)
		*
		* @return ������������(int)
		*/
		static int Range(int min, int max);
	};
}
#endif // !RANDOM_H_INCLUDED
