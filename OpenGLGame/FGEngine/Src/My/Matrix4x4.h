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
	* 4x4行列
	*/
	struct Matrix4x4
	{
	public:

		// デフォルトコンストラクタ
		Matrix4x4() = default;

		// 4個のVector4からMatrix4x4を構成するコンストラクタ
		explicit Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);

		// 1個のfloatを対角線にコピーするコンストラクタ
		explicit Matrix4x4(float f);

		// Matrix3x3からMatrix4x4に変換するコンストラクタ
		explicit Matrix4x4(const Matrix3x3& m);

		/**
		* 平行移動行列を作成
		* 
		* @param position 位置
		*/
		static Matrix4x4 Translate(const Vector3& position);

		/**
		*  拡大縮小行列を作成
		* 
		* @param scale スケール
		*/
		static Matrix4x4 Scale(const Vector3& scale);

		/**
		* X軸の回転行列を作成
		* 
		* @param angle xの角度
		*/
		static Matrix4x4 RotateX(float angle);

		/**
		* Y軸の回転行列を作成
		* 
		* @param angle yの角度
		*/
		static Matrix4x4 RotateY(float angle);

		/**
		* Z軸の回転行列を作成
		* 
		* @param angle zの角度
		*/
		static Matrix4x4 RotateZ(float angle);


		// 添え字演算子
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
	* Matrix3x3とVector3の乗算
	*/
	Vector4 operator*(const Matrix4x4& m, const Vector4& v);

	/**
	* Matrix3x3同士の乗算
	*/
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b);
}
#endif // !MATRIX4X4_H_INCLUDED