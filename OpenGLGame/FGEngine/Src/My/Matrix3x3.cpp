/**
* @file Matrix3x3.cpp
*/
#include "Matrix3x3.h"
#include "Matrix4x4.h"

namespace FGEngine
{
	/**
	* 3��Vector3����Matrix3x3���\�z����R���X�g���N�^
	*/
	Matrix3x3::Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2)
	{
		data[0] = v0;
		data[1] = v1;
		data[2] = v2;
	}

	/**
	* 1��float��Ίp���ɃR�s�[����R���X�g���N�^
	*/
	Matrix3x3::Matrix3x3(float f)
	{
		data[0] = Vector3(f, 0, 0);
		data[1] = Vector3(0, f, 0);
		data[2] = Vector3(0, 0, f);
	}

	/**
	* Matrix4x4����Matrix3x3�ɕϊ����R���X�g���N�^
	*/
	Matrix3x3::Matrix3x3(const Matrix4x4& m)
	{
		data[0] = Vector3(m.data[0]);
		data[1] = Vector3(m.data[1]);
		data[2] = Vector3(m.data[2]);
	}

	/**
	* Matrix3x3��Vector3�̏�Z
	*/
	Vector3 operator*(const Matrix3x3& m, const Vector3& v)
	{
		return m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z;
	}

	/**
	* Matrix3x3���m�̏�Z
	*/
	Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b)
	{
		Matrix3x3 m;
		m.data[0] = a * b.data[0];
		m.data[1] = a * b.data[1];
		m.data[2] = a * b.data[2];
		return m;
	}

	/**
	* Matrix3x3���m�̑����Z
	*/
	Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b)
	{
		a = a * b;
		return a;
	}

}