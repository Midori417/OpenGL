/**
* @file Matrix4x4.h
*/
#ifndef FGENGINE_MATRIX4X4_H_INCLUDED
#define FGENGINE_MATRIX4X4_H_INCLUDED
#include "MatrixFrd.h"
#include "Vector4.h"

namespace FGEngine
{

	/**
	* 4x4�s��
	*/
	struct Matrix4x4
	{
	public:

		// �f�t�H���g�R���X�g���N�^
		Matrix4x4() = default;

		// 4��Vector4����Matrix4x4���\������R���X�g���N�^
		explicit Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);

		// 1��float��Ίp���ɃR�s�[����R���X�g���N�^
		explicit Matrix4x4(float f);

		// Matrix3x3����Matrix4x4�ɕϊ�����R���X�g���N�^
		explicit Matrix4x4(const Matrix3x3& m);

		/**
		* ���s�ړ��s����쐬
		* 
		* @param position �ʒu
		*/
		static Matrix4x4 Translate(const Vector3& position);

		/**
		*  �g��k���s����쐬
		* 
		* @param scale �X�P�[��
		*/
		static Matrix4x4 Scale(const Vector3& scale);

		/**
		* X���̉�]�s����쐬
		* 
		* @param angle x�̊p�x
		*/
		static Matrix4x4 RotateX(float angle);

		/**
		* Y���̉�]�s����쐬
		* 
		* @param angle y�̊p�x
		*/
		static Matrix4x4 RotateY(float angle);

		/**
		* Z���̉�]�s����쐬
		* 
		* @param angle z�̊p�x
		*/
		static Matrix4x4 RotateZ(float angle);


		// �Y�������Z�q
		Vector4& operator[](size_t i)
		{
			return data[i];
		}
		const Vector4& operator[](size_t i) const
		{
			return data[i];
		}

	public:

		Vector4 data[4];

	};

	/**
	* Matrix3x3��Vector3�̏�Z
	*/
	Vector4 operator*(const Matrix4x4& m, const Vector4& v);

	/**
	* Matrix3x3���m�̏�Z
	*/
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b);
}
#endif // !MATRIX4X4_H_INCLUDED