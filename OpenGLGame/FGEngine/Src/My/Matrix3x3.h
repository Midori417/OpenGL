/**
* @file Matrix3x3.h
*/
#ifndef FGENGINE_MATRIX3X3_H_INCLUDED
#define FGENGINE_MATRIX3X3_H_INCLUDED
#include "MatrixFrd.h"
#include "Vector3.h"

namespace FGEngine
{
	/**
	* 3x3�s��
	*/
	struct Matrix3x3
	{
		// �f�t�H���g�R���X�g���N�^
		Matrix3x3() = default;

		// 3��vec3����mat3���\�z����R���X�g���N�^
		explicit Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2);

		// 1��float��Ίp���ɃR�s�[����R���X�g���N�^
		explicit Matrix3x3(float f);

		// Matrix4x4����Matrix3x3�ɕϊ�����R���X�g���N�^
		explicit Matrix3x3(const Matrix4x4& m);

		/**
		* �]�u�s������߂�
		*/
		static Matrix3x3 Transpose(const Matrix3x3& m);

		/**
		* �t�s������߂�
		*/
		static Matrix3x3 Inverse(const Matrix3x3& m);

		// �Y�������Z�q
		Vector3& operator[](size_t i) {
			return data[i];
		}
		const Vector3& operator[](size_t i) const {
			return data[i];
		}

	public:

		Vector3 data[3];
	};

	/**
	* Matrix3x3��Vector3�̏�Z
	*/
	Vector3 operator*(const Matrix3x3& m, const Vector3& v);

	/**
	* Matrix3x3���m�̏�Z
	*/
	Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b);
	Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b);
}
#endif // !MATRIX3X3_H_INCLUDED