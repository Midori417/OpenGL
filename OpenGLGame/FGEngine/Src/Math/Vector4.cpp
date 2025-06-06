/**
* @file Vector4.cpp
*/
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Math/Vector3.h"

namespace FGEngine
{
	// 静的変数の初期化
	const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
	const Vector4 Vector4::one = Vector4(1, 1, 1, 1);

	/**
	* 4個のfloatからVector4を作成するコンストラクタ
	*
	* @param x X成分
	* @param y Y成分
	* @param z Z成分
	* @param w W成分
	*/
	Vector4::Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	/**
	* 1個のfloatからVector4を作成するコンストラクタ
	*
	* @param v XYZW成分
	*/
	Vector4::Vector4(float v)
		: x(v), y(v), z(v), w(v)
	{
	}

	/**
	* Vector2と2個のfloatからVector4を構築するコンストラクタ
	*
	* @param v Vector2のXY成分
	* @param z Z成分
	* @param w W成分
	*/
	Vector4::Vector4(const Vector2& v, float z, float w)
		: x(v.x), y(v.y), z(z), w(w)
	{
	}

	/**
	* Vector3と1個のfloatからVector4を構築するコンストラクタ
	*
	* @param v Vector3のXYZ成分
	* @param w W成分
	*/
	Vector4::Vector4(const Vector3& v, float w)
		: x(v.x), y(v.y), z(v.z), w(w)
	{
	}

	/**
	* 単項演算子
	*/
	Vector4 operator-(const Vector4& v)
	{
		return Vector4(-v.x, -v.y, -v.z, -v.w);
	}

	/**
	* Vector4同士の加算
	*/
	Vector4 operator+(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	/**
	* Vector4同士の減算
	*/
	Vector4 operator-(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	/**
	* Vector4同士の乗算
	*/
	Vector4 operator*(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	/**
	* Vector4同士の除算
	*/
	Vector4 operator/(const Vector4& a, const Vector4& b)
	{
		// 0除算をしないように
		if (b.x == 0 || b.y == 0 || b.z == 0 || b.w == 0)
		{
			return Vector4::zero;
		}

		return Vector4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	/**
	* Vector4同士の代入加算
	*/
	Vector4 operator+=(Vector4& a, const Vector4& b)
	{
		a = a + b;
		return a;
	}

	/**
	* Vector4同士の代入減算
	*/
	Vector4 operator-=(Vector4& a, const Vector4& b)
	{
		a = a - b;
		return a;
	}

	/**
	* Vector4同士の代入乗算
	*/
	Vector4 operator*=(Vector4& a, const Vector4& b)
	{
		a = a * b;
		return a;
	}

	/**
	* Vector4同士の代入除算
	*/
	Vector4 operator/=(Vector4& a, const Vector4& b)
	{
		a = a / b;
		return a;
	}

	/**
	* Vector4同士の比較演算
	*/
	bool operator==(const Vector4& a, const Vector4& b)
	{
		return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
	}

	/**
	* Vector4同士の比較演算
	*/
	bool operator!=(const Vector4& a, const Vector4& b)
	{
		return ((a.x != b.x) || (a.y != b.y) || (a.z != b.z) || (a.w != b.w));
	}
}