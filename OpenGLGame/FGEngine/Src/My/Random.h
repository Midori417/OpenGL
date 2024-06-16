/**
* @file Random.h
*/
#ifndef FGENGINE_RANDOM_H_INCLUDED
#define FGENGINE_RANDOM_H_INCLUDED

namespace FGEngine
{
	/**
	* �����_���֐����Ǘ�
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
		* @param min �����͈͂̍ŏ��l
		* @param max �����͈͂̍ő�l
		*
		* @return ������������
		*/
		static float Range(float min, float max);

		static int Range(int min, int max);
	};
}
#endif // !RANDOM_H_INCLUDED
