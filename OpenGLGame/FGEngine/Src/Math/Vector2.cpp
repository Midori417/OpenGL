/**
* @file Vector2.cpp
*/
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Mathf.h"

namespace FGEngine
{
	// 静的変数の初期化
	const Vector2 Vector2::zero = Vector2(0, 0);
	const Vector2 Vector2::one = Vector2(1, 1);

	/**
	* 2個のfloatからVector2を作成するコンストラクタ
	*
	* @param x X成分
	* @param y Y成分
	*/
	Vector2::Vector2(float x, float y)
		: x(x), y(y)
	{
	}

	/**
	* 1個のfloatからVector2を作成するコンストラクタ
	*
	* @param v XYの成分
	*/
	Vector2::Vector2(float v)
		: x(v), y(v)
	{
	}

	/**
	* Vector3からVector2を構築するコンストラクタ
	*
	* @param v Vector3のXY成分
	*/
	Vector2::Vector2(const Vector3& v)
		: x(v.x), y(v.y)
	{
	}

	/**
	* Vector4からVector2を構築するコンストラクタ
	*
	* @param v Vector4のXY成分
	*/
	Vector2::Vector2(const Vector4& v)
		: x(v.x), y(v.y)
	{
	}

	/**
	* ベクトルの正規化を計算する
	*/
	Vector2 Vector2::Normalize(const Vector2& v)
	{
		float num = Mathf::Sqrt(Dot(v, v));
		if (num > 0.0f)
		{
			return v / Vector2(num);
		}
		else
		{
			return Vector2::zero;
		}
	}

	/**
	* ベクトルの内積を計算する
	*
	* @return aとbの内積
	*/
	float Vector2::Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/**
	* 2つのベクトルの距離を計算する
	*
	* return aとbの距離
	*/
	float Vector2::Distance(const Vector2& a, const Vector2& b)
	{
		Vector2 tmp = a - b;
		return Mathf::Sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
	}

	/**
	* 2つのベクトルの間を線形補間する
	*
	* @param a 補間の開始ベクトル
	* @param b 補間の終了ベクトル
	* @param t 補間パラメータ (0.0 ~ 1.0 の範囲)
	*
	* @return 補間されたベクトル
	*/
	Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
	}

	/**
	* Vector2同士の加算
	*/
	Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	/**
	* Vector2同士の減算
	*/
	Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	/**
	* Vector2同士の乗算
	*/
	Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	/**
	* Vector2同士の除算
	*/
	Vector2 operator/(const Vector2& a, const Vector2& b)
	{
		// 0除算をしないように
		if (b.x == 0 || b.y == 0)
		{
			return Vector2::zero;
		}

		return Vector2(a.x / b.x, a.y / b.y);
	}

	/**
	* Vector2とfloatの乗算
	*/
	Vector2 operator*(const Vector2& v, float f)
	{
		return v * Vector2(f);
	}

	/**
	* Vector2とfloatの除算
	*/
	Vector2 operator/(const Vector2& v, float f)
	{
		return v / Vector2(f);
	}

	/**
	* Vector2同士の代入加算
	*/
	Vector2 operator+=(Vector2& a, const Vector2& b)
	{
		a = a + b;
		return a;
	}

	/**
	* Vector2同士の代入減算
	*/
	Vector2 operator-=(Vector2& a, const Vector2& b)
	{
		a = a - b;
		return a;
	}

	/**
	* Vector2同士の代入乗算
	*/
	Vector2 operator*=(Vector2& a, const Vector2& b)
	{
		a = a * b;
		return a;
	}

	/**
	* Vector2同士の代入除算
	*/
	Vector2 operator/=(Vector2& a, const Vector2& b)
	{
		a = a / b;
		return a;
	}

	/**
	* Vector2とfloatの代入乗算
	*/
	Vector2 operator*=(Vector2& v, float f)
	{
		v = v * f;
		return v;
	}

	/**
	* Vector2とfloatの代入除算
	*/
	Vector2 operator/=(Vector2& v, float f)
	{
		v = v / f;
		return v;
	}

	/**
	* Vector2同士の比較演算
	*/
	bool operator==(const Vector2& a, const Vector2& b)
	{
		return ((a.x == b.x) && (a.y == b.y));
	}

	/**
	* Vector2同士の比較演算
	*/
	bool operator!=(const Vector2& a, const Vector2& b)
	{
		return ((a.x != b.x) || (a.y != b.y));
	}
}