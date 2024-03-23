/**
* @file Matrix3x3.h
*/
#ifndef MATRIX3X3_H_INCLUDED
#define MATRIX3X3_H_INCLUDED

#include "MatrixFrd.h"
#include "Vector3.h"

namespace FGEngine
{
	struct Matrix4x4;
	/**
	* 3x3行列
	*/
	struct Matrix3x3
	{
		Vector3 data[3];

		// デフォルトコンストラクタ
		Matrix3x3() = default;

		// 3個のvec3からmat3を構築するコンストラクタ
		Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2) {
			data[0] = v0;
			data[1] = v1;
			data[2] = v2;
		}

		// 1個のfloatを対角線にコピーするコンストラクタ
		explicit Matrix3x3(float f) {
			data[0] = { f, 0, 0 };
			data[1] = { 0, f, 0 };
			data[2] = { 0, 0, f };
		}

		// mat4からmat3に変換するコンストラクタ
		explicit Matrix3x3(const Matrix4x4& m);

		// 添え字演算子
		Vector3& operator[](size_t i) {
			return data[i];
		}
		const Vector3& operator[](size_t i) const {
			return data[i];
		}
	};


	// mat3とvec3の乗算
	inline Vector3 operator*(const Matrix3x3& m, const Vector3& v)
	{
		return m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z;
	}

	// mat3同士の乗算
	inline Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b)
	{
		Matrix3x3 m;
		m.data[0] = a * b.data[0];
		m.data[1] = a * b.data[1];
		m.data[2] = a * b.data[2];
		return m;
	}
	inline Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b)
	{
		a = a * b;
		return a;
	}
}
#endif // !MATRIX3X3_H_INCLUDED
