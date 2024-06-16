/**
* @file Matrix3x3.cpp
*/
#include "Matrix3x3.h"
#include "Matrix4x4.h"

namespace FGEngine
{
	/**
	* 3個のVector3からMatrix3x3を構築するコンストラクタ
	*/
	Matrix3x3::Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2)
	{
		data[0] = v0;
		data[1] = v1;
		data[2] = v2;
	}

	/**
	* 1個のfloatを対角線にコピーするコンストラクタ
	*/
	Matrix3x3::Matrix3x3(float f)
	{
		data[0] = Vector3(f, 0, 0);
		data[1] = Vector3(0, f, 0);
		data[2] = Vector3(0, 0, f);
	}

	/**
	* Matrix4x4からMatrix3x3に変換数コンストラクタ
	*/
	Matrix3x3::Matrix3x3(const Matrix4x4& m)
	{
		data[0] = Vector3(m.data[0]);
		data[1] = Vector3(m.data[1]);
		data[2] = Vector3(m.data[2]);
	}

	/**
	* 転置行列を求める
	*/
	Matrix3x3 Matrix3x3::Transpose(const Matrix3x3& m)
	{
		Matrix3x3 result = Matrix3x3(1);

		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];

		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];

		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];

		return result;
	}

	/**
	* 逆行列を求める
	*/
	Matrix3x3 Matrix3x3::Inverse(const Matrix3x3& m)
	{
		// 四因子行列を計算
		Matrix3x3 adjugate = Matrix3x3(1);
		adjugate[0][0] = m[1][1] * m[2][2] - m[1][2] * m[2][1];
		adjugate[0][1] = -m[0][1] * m[2][2] + m[0][2] * m[2][1];
		adjugate[0][2] = m[0][1] * m[1][2] - m[0][2] * m[1][1];
		
		adjugate[1][0] = -m[1][0] * m[2][2] + m[1][2] * m[2][0];
		adjugate[1][1] = m[0][0] * m[2][2] - m[0][2] * m[2][0];
		adjugate[1][2] = -m[0][0] * m[1][2] + m[0][2] * m[1][0];
		
		adjugate[2][0] = m[1][0] * m[2][1] - m[1][1] * m[2][0];
		adjugate[2][1] = -m[0][0] * m[2][1] + m[0][1] * m[2][0];
		adjugate[2][2] = m[0][0] * m[1][1] - m[0][1] * m[1][0];
		
		// 行列式を計算
		const float det =
		m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] +
		m[0][1] * m[1][2] * m[2][0] - m[0][1] * m[1][0] * m[2][2] +
		m[0][2] * m[1][0] * m[2][1] - m[0][2] * m[1][1] * m[2][0];
		
		  // 行列式の逆数を掛ける
		const float invDet = 1.0f / det;
		adjugate[0] *= invDet;
		adjugate[1] *= invDet;
		adjugate[2] *= invDet;
		
		return adjugate;
	}

	/**
	* Matrix3x3とVector3の乗算
	*/
	Vector3 operator*(const Matrix3x3& m, const Vector3& v)
	{
		return m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z;
	}

	/**
	* Matrix3x3同士の乗算
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
	* Matrix3x3同士の代入乗算
	*/
	Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b)
	{
		a = a * b;
		return a;
	}

}