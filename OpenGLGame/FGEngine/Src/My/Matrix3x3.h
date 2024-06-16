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
	* 3x3行列
	*/
	struct Matrix3x3
	{
		// デフォルトコンストラクタ
		Matrix3x3() = default;

		// 3個のvec3からmat3を構築するコンストラクタ
		explicit Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2);

		// 1個のfloatを対角線にコピーするコンストラクタ
		explicit Matrix3x3(float f);

		// Matrix4x4からMatrix3x3に変換するコンストラクタ
		explicit Matrix3x3(const Matrix4x4& m);

		/**
		* 転置行列を求める
		*/
		static Matrix3x3 Transpose(const Matrix3x3& m);

		/**
		* 逆行列を求める
		*/
		static Matrix3x3 Inverse(const Matrix3x3& m);

		// 添え字演算子
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
	* Matrix3x3とVector3の乗算
	*/
	Vector3 operator*(const Matrix3x3& m, const Vector3& v);

	/**
	* Matrix3x3同士の乗算
	*/
	Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b);
	Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b);
}
#endif // !MATRIX3X3_H_INCLUDED