/**
* @file Vector4.h
*/
#ifndef FGENGINE_VECTOR4_H_INCLUDED
#define FGENGINE_VECTOR4_H_INCLUDED
#include "FGEngine/UsingNames/UsingMath.h"

namespace FGEngine
{
	/**
	* 四次元ベクトル
	*/
	struct Vector4
	{
		/**
		* デフォルトコンストラクタ
		*/
		Vector4() = default;

		/**
		* 4個のfloatからVector4を作成するコンストラクタ
		*
		* @param x X成分
		* @param y Y成分
		* @param z Z成分
		* @param w W成分
		*/
		explicit Vector4(float x, float y, float z, float w);

		/**
		* 1個のfloatからVector4を作成するコンストラクタ
		*
		* @param v XYZW成分
		*/
		explicit Vector4(float v);

		/**
		* Vector2と2個のfloatからVector4を構築するコンストラクタ
		*
		* @param v Vector2のXY成分
		* @param z Z成分
		* @param w W成分
		*/
		explicit Vector4(const Vector2& v, float z, float w);

		/**
		* Vector3と1個のfloatからVector4を構築するコンストラクタ
		*
		* @param v Vector3のXYZ成分
		* @param w W成分
		*/
		explicit Vector4(const Vector3& v, float w);

	public:

		// X成分
		float x;

		// Y成分
		float y;

		// Z成分
		float z;

		// W成分
		float w;

		// Vector4(0, 0, 0, 0)
		const static Vector4 zero;

		// Vector4(1, 1, 1, 1)
		const static Vector4 one;

		float operator[](size_t i)const
		{
			return *(&x + i);
		}
		float& operator[](size_t i)
		{
			return *(&x + i);
		}
	};

	// 単項演算子
	Vector4 operator-(const Vector4& v);

	// Vector4同士の演算子
	Vector4 operator+(const Vector4& a, const Vector4& b);
	Vector4 operator-(const Vector4& a, const Vector4& b);
	Vector4 operator*(const Vector4& a, const Vector4& b);
	Vector4 operator/(const Vector4& a, const Vector4& b);

	// Vector4同士の代入演算子
	Vector4 operator+=(Vector4& a, const Vector4& b);
	Vector4 operator-=(Vector4& a, const Vector4& b);
	Vector4 operator*=(Vector4& a, const Vector4& b);
	Vector4 operator/=(Vector4& a, const Vector4& b);

	// Vector4同士の比較演算子
	bool operator==(const Vector4& a, const Vector4& b);
	bool operator!=(const Vector4& a, const Vector4& b);
}

#endif // !FGENGINE_VECTOR4_H_INCLUDED
