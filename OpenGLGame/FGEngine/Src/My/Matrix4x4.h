/**
* @file Matrix4x4.h
*/
#ifndef MATRIX4X4_H_INCLUDED
#define MATRIX4X4_H_INCLUDED

#include "Vector3.h"
#include "Vector4.h"

namespace FGEngine
{
	// 先行宣言
	struct Matrix3x3;

	/**
	* 4x4行列
	*/
	struct Matrix4x4
	{
	public:

		// コンストラクタ
		Matrix4x4() = default;
		// デストラクタ
		~Matrix4x4() = default;

		// 4このvec4からmat4を構成するコンストラクタ
		Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
		{
			data[0] = v0;
			data[1] = v1;
			data[2] = v2;
			data[3] = v3;
		}

		// 1個のfloatを対角線にコピーするコンストラクタ
		explicit Matrix4x4(float f)
		{
			data[0] = Vector4{ f, 0, 0, 0 };
			data[1] = Vector4{ 0, f, 0, 0 };
			data[2] = Vector4{ 0, 0, f, 0 };
			data[3] = Vector4{ 0, 0, 0, f };
		}

		// mat3からmat4に変換するコンストラクタ
		explicit Matrix4x4(const Matrix3x3& m);

		// 平行移動行列
		static Matrix4x4 Translate(const Vector3& v);
		// 拡大縮小
		static Matrix4x4 Scale(const Vector3& v);
		// x軸の回転
		static Matrix4x4 RotateX(float angle);
		// y軸の回転
		static Matrix4x4 RotateY(float angle);
		// z軸の回転
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

	inline Vector3 operator*(const Matrix4x4& m, const Vector3& v)
	{
		Vector3 result(0);
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				result[i] += m[i][j] * v[j];
			}
		}
		return result;
	}

	// mat4とvec4の乗算
	inline Vector4 operator*(const Matrix4x4& m, const Vector4& v)
	{
		return m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3] * v.w;
	}

	// mat4同士の乗算
	inline Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
	{
		Matrix4x4 m;
		m.data[0] = a * b.data[0];
		m.data[1] = a * b.data[1];
		m.data[2] = a * b.data[2];
		m.data[3] = a * b.data[3];

		return m;
	}
	inline Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b)
	{
		a = a * b;
		return a;
	}
}
#endif // !MATRIX4X4_H_INCLUDED