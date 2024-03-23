/**
* @file Matrix4x4.cpp
*/
#include "Matrix4x4.h"
#include "Vector3.h"
#include "VecMath.h"

namespace FGEngine
{

	/**
	* ���s�ړ��s����쐬����
	*/
	Matrix4x4 Matrix4x4::Translate(const Vector3& v)
	{
		Matrix4x4 m(1);
		m[3][0] = v.x;
		m[3][1] = v.y;
		m[3][2] = v.z;
		return m;
	}

	/**
	* �g��k���s����쐬����
	*/
	Matrix4x4 Matrix4x4::Scale(const Vector3& v)
	{
		Matrix4x4 m(1);
		m[0][0] = v.x;
		m[1][1] = v.y;
		m[2][2] = v.z;
		return m;
	}

	/**
	* X����]�s����쐬����
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
	* Y����]�s����쐬����
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
	* Z����]�s����쐬����
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
}