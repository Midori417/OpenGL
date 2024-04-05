/**
* @file Mathf.h
*/
#ifndef FGENGINE_MATHF_H_INCLUDED
#define FGENGINE_MATHF_H_INCLUDED

namespace FGEngine
{

	/**
	* ��ʓI�Ȑ��w�֐��������\����
	*/
	struct Mathf
	{
	public:

		// �R���X�g���N�^
		Mathf() = default;

		/**
		* f�x�̃T�C����Ԃ�
		*/
		static float Sin(float f);


		/**
		* f�x�̃R�T�C����Ԃ�
		*/
		static float Cos(float f);


		/**
		* f�x�̃R�T�C����Ԃ�
		*/
		static float Tan(float f);

		/**
		* f�x�̃A�[�N�T�C����Ԃ�
		*/
		static float Asin(float f);

		/**
		* f�x�̃A�[�N�R�T�C���Ԃ�
		*/
		static float Acos(float f);

		/**
		*  f�x�̃A�[�N�^���W�F���g��Ԃ�
		*/
		static float Atan(float f);

		/**
		*  Tan��y / x�ɂȂ�p�x�����W�A����Ԃ�
		*/
		static float Atan2(float x, float y);

		/**
		* f�̕�������Ԃ�
		*/
		static float Sqrt(float f);

		/**
		* f�̐�Βl��Ԃ�
		*/
		static float Abs(float f);

		/**
		* value�̐�Βl��Ԃ�
		*/
		static int Abs(int value);

		/**
		* a��b�̒l����ŏ���Ԃ�
		*/
		static float Min(float a, float b);

		/**
		* a��b�̒l����ŏ���Ԃ�
		*/
		static int Min(int a, int b);

		/**
		* a��b�̒l����ő��Ԃ�
		*/
		static float Max(float a, float b);

		/**
		* a��b�̍ő�l�̂ق�������
		*/
		static int Max(int a, int b);

		/**
		* (float)value��⊮����(min�`max)����
		*
		* @param (float)�⊮(min�`max)����l
		* @param min (float)��Ԃ̍ŏ��l
		* @parma max (float)��Ԃ̍ő�l
		*
		* @return �⊮(min�`max)�����l
		*/
		static float Clamp(float value, float min, float max);

		/**
		* (int)value��⊮����(min�`max)����
		*
		* @param (int)�⊮(min�`max)����l
		* @param min (int)��Ԃ̍ŏ��l
		* @parma max (int)��Ԃ̍ő�l
		*
		* @return �⊮(min�`max)�����l
		*/
		static int Clamp(int value, int min, int max);

		/**
		* value��⊮(0�`1)����
		*
		* @param value �⊮(0�`1)����l
		*
		* @return �⊮(0�`1)�����l
		*/
		static float Clamp01(float value);

		/**
		* �f�O���[(�x���@)���烉�W�A��(�ʓx�@)�ɕϊ�����
		*
		* @param deg �f�O���[(�x���@)
		*
		* @return ���W�A���ɕϊ�����deg
		*/
		static float DegToRad(float deg);

		/**
		* ���W�A��(�ʓx�@)����f�O���[(�x���@)�ɕϊ�����
		*
		* @param rad ���W�A��(�ʓx�@)
		*
		* @return �f�O���[�ɕϊ�����rad
		*/
		static float RadToDeg(float rad);

	public:

		// �~����
		const static float PI;
	};

}
#endif // !MATHF_H_INCLUDED
