/**
* @file Matrix3x3.h
*/
#ifndef FGENGINE_MATRIX3X3_H_INCLUDED
#define FGENGINE_MATRIX3X3_H_INCLUDED
#include "MathFrd.h"

namespace FGEngine
{
	/**
	* 3x3�s��
	*/
	struct Matrix3x3
	{
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Matrix3x3() = default;

		/**
		* 3��Vector3����Matrix3x3���쐬����R���X�g���N�^
		*
		* @param v0
		* @param v1
		* @param v2
		*/
		explicit Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2);

		/**
		* 1��float��Ίp����Matrix3x3���쐬����R���X�g���N�^
		*
		* @param f
		*/
		explicit Matrix3x3(float f);

		/**
		* Matrix4x4����Matrix3x3���쐬����R���X�g���N�^
		*
		* @param m �ϊ�����Matrix4x4
		*/
		explicit Matrix3x3(const Matrix4x4& m);

		/**
		* �s��̍s���擾����
		*
		* @param index �s�̔ԍ�
		*/
		Vector3 GetRow(size_t index) const;

		/**
		* �s��̍s��ݒ肷��
		*
		* @param index	�s�̔ԍ�
		* @param v		�ݒ肷��Vector3
		*/
		void SetRow(size_t index, const Vector3& v);

		/**
		* �s��̗���擾����
		*
		* @param index ��̔ԍ�
		*/
		Vector3 GerColumn(size_t index) const;

		/**
		* �s��̗��ݒ肷��
		*
		* @param index	��̔ԍ�
		* @param v		�ݒ肷��Vector3
		*/
		void SetColumn(size_t index, const Vector3& v);

		/**
		* �]�u�s������߂�
		*/
		static Matrix3x3 Transpose(const Matrix3x3& m);

		/**
		* �t�s����v�Z����
		*/
		static Matrix3x3 Inverse(const Matrix3x3& m);

	public:

		float num00;
		float num01;
		float num02;

		float num10;
		float num11;
		float num12;

		float num20;
		float num21;
		float num22;

		// �P���s��
		const static Matrix3x3 identity;

		// �S�Ă̗v�f��0�̍s��
		const static Matrix3x3 zero;

		/**
		* �Q�Ƃ�Ԃ��Y�������Z�q
		*
		* @param row	�s�̃C���f�b�N�X
		* @param column	��̃C���f�b�N�X
		*/
		const float& operator()(size_t row, size_t column) const;
		float& operator()(size_t row, size_t column);
	};

	// Matrux3x3��Vector3�̏�Z
	Vector3 operator*(const Matrix3x3& m, const Vector3& v);

	// Matrix3x3���m�̏�Z
	Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b);
	Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b);

}

#endif // !FGENGINE_MATRIX3X3_H_INCLUDED