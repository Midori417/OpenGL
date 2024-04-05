/**
* @file Matrix4x4.cpp
*/
#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "Vector3.h"
#include "Mathf.h"

namespace FGEngine
{
	/**
	* 4��Vector4����Matrix4x4���\������R���X�g���N�^
	*/
	Matrix4x4::Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
	{
		data[0] = v0;
		data[1] = v1;
		data[2] = v2;
		data[3] = v3;
	}

	/**
	* 1��float��Ίp���ɃR�s�[����R���X�g���N�^
	*/
	Matrix4x4::Matrix4x4(float f)
	{
		data[0] = Vector4{ f, 0, 0, 0 };
		data[1] = Vector4{ 0, f, 0, 0 };
		data[2] = Vector4{ 0, 0, f, 0 };
		data[3] = Vector4{ 0, 0, 0, f };
	}

	/**
	* Matrix3x3����Matrix4x4�ɕϊ�����R���X�g���N�^
	*/
	Matrix4x4::Matrix4x4(const Matrix3x3& m)
	{
		data[0] = Vector4{ m.data[0], 0 };
		data[1] = Vector4{ m.data[1], 0 };
		data[2] = Vector4{ m.data[2], 0 };
		data[3] = Vector4{ 0, 0, 0, 1 };
	}

	/**
	* ���s�ړ��s����쐬
	*
	* @param position �ʒu
	*/
	Matrix4x4 Matrix4x4::Translate(const Vector3& position)
	{
		Matrix4x4 m(1);
		m[3][0] = position.x;
		m[3][1] = position.y;
		m[3][2] = position.z;
		return m;
	}

	/**
	*  �g��k���s����쐬
	*
	* @param scale �X�P�[��
	*/
	Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
	{
		Matrix4x4 m(1);
		m[0][0] = scale.x;
		m[1][1] = scale.y;
		m[2][2] = scale.z;
		return m;
	}

	/**
	* X���̉�]�s����쐬
	*
	* @param angle x�̊p�x
	*/
	Matrix4x4 Matrix4x4::RotateX(float angle)
	{
		const float c = Mathf::Cos(angle);
		const float s = Mathf::Sin(angle);
		Matrix4x4 m(1);
		// y' = y * c - z * s
		// z' = y * s + z * c
		m[1][1] = c;
		m[2][1] = -s;
		m[1][2] = s;
		m[2][2] = c;
		return m;
	}

	/**
	* Y���̉�]�s����쐬
	*
	* @param angle y�̊p�x
	*/
	Matrix4x4 Matrix4x4::RotateY(float angle)
	{
		const float c = Mathf::Cos(angle);
		const float s = Mathf::Sin(angle);
		Matrix4x4 m(1);
		// x' = x * c + z * s
		// z' = x * -s + z * c
		m[0][0] = c;
		m[2][0] = s;
		m[0][2] = -s;
		m[2][2] = c;
		return m;
	}

	/**
	* Z���̉�]�s����쐬
	*
	* @param angle z�̊p�x
	*/
	Matrix4x4 Matrix4x4::RotateZ(float angle)
	{
		const float c = Mathf::Cos(angle);
		const float s = Mathf::Sin(angle);
		Matrix4x4 m(1);
		// x' = x * c - y * s
		// y' = x * s + y * c
		m[0][0] = c;
		m[1][0] = -s;
		m[0][1] = s;
		m[1][1] = c;
		return m;
	}

	/**
	* Matrix3x3��Vector3�̏�Z
	*/
	Vector4 operator*(const Matrix4x4& m, const Vector4& v)
	{
		return m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3] * v.w;
	}

	/**
	* Matrix3x3���m�̏�Z
	*/
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
	{
		Matrix4x4 m;
		m.data[0] = a * b.data[0];
		m.data[1] = a * b.data[1];
		m.data[2] = a * b.data[2];
		m.data[3] = a * b.data[3];

		return m;
	}

	/**
	* Matrix3x3���m�̑����Z
	*/
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b)
	{
		a = a * b;
		return a;
	}
}