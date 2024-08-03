/**
* @file Vector3.cpp
*/
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Mathf.h"

namespace FGEngine
{
	// 静的変数の初期化
	const Vector3 Vector3::zero = Vector3(0, 0, 0);
	const Vector3 Vector3::one = Vector3(1, 1, 1);
	const Vector3 Vector3::up = Vector3(0, 1, 0);
	const Vector3 Vector3::down = Vector3(0, -1, 0);
	const Vector3 Vector3::left = Vector3(-1, 0, 0);
	const Vector3 Vector3::right = Vector3(1, 0, 0);
	const Vector3 Vector3::forward = Vector3(0, 0, 1);
	const Vector3 Vector3::back = Vector3(0, 0, -1);

	/**
	* 3個のfloatからVector3を作成するコンストラクタ
	*
	* @param x X成分
	* @param y Y成分
	* @param z Z成分
	*/
	Vector3::Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}

	/**
	* 1個のfloatからVector3を作成するコンストラクタ
	*
	* @param v XYZ成分
	*/
	Vector3::Vector3(float v)
		: x(v), y(v), z(v)
	{
	}

	/**
	* Vector2と1個のfloatからVector3を構築するコンストラクタ
	*
	* @param v Vector2のXY成分
	* @param z Z成分
	*/
	Vector3::Vector3(const Vector2& v, float z)
		: x(v.x), y(v.y), z(z)
	{
	}

	/**
	* Vector4からVector3を構築するコンストラクタ
	*
	* @parma v	Vector4のXYZ成分
	*/
	Vector3::Vector3(const Vector4& v)
		: x(v.x), y(v.y), z(v.z)
	{
	}

	/**
	* ベクトルの正規化を計算する
	*/
	Vector3 Vector3::Normalize(const Vector3& v)
	{
		float num = Mathf::Sqrt(Dot(v, v));
		if (num > 0.0f)
		{
			return v / Vector3(num);
		}
		else
		{
			return Vector3::zero;
		}
	}

	/**
	* ベクトルの大きさを計算する
	*/
	float Vector3::Magnitude(const Vector3& v)
	{
		return Mathf::Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}


	/**
	* ベクトルの内積を計算する
	*
	* @return aとbの内積
	*/
	float Vector3::Dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/**
	* 2のベクトルの外積(クロス積)を計算する
	*
	* @return aとbの外積
	*/
	Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
	{
		float num = a.y * b.z - a.z * b.y;
		float num2 = a.z * b.x - a.x * b.z;
		float num3 = a.x * b.y - a.y * b.x;
		return Vector3(num, num2, num3);
	}

	/**
	* 2つのベクトルの距離を計算する
	*
	* return aとbの距離
	*/
	float Vector3::Distance(const Vector3& a, const Vector3& b)
	{
		Vector3 tmp = a - b;
		return Mathf::Sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
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
	Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
	}

	/**
	* 単項演算子
	*/
	Vector3 operator-(const Vector3& v)
	{
		return Vector3(-v.x, -v.y, -v.z);
	}

	/**
	* Vector3同士の加算
	*/
	Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/**
	* Vector3同士の減算
	*/
	Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/**
	* Vector3同士の乗算
	*/
	Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	/**
	* Vector3同士の除算
	*/
	Vector3 operator/(const Vector3& a, const Vector3& b)
	{
		// 0除算をしないように
		if (b.x == 0 || b.y == 0 || b.z == 0)
		{
			return Vector3::zero;
		}

		return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	/**
	* Vector3とfloatの乗算
	*/
	Vector3 operator*(const Vector3& v, float f)
	{
		return v * Vector3(f);
	}

	/**
	* Vector3とfloatの除算
	*/
	Vector3 operator/(const Vector3& v, float f)
	{
		return v / Vector3(f);
	}

	/**
	* Vector3同士の代入加算
	*/
	Vector3 operator+=(Vector3& a, const Vector3& b)
	{
		a = a + b;
		return a;
	}

	/**
	* Vector3同士の代入減算
	*/
	Vector3 operator-=(Vector3& a, const Vector3& b)
	{
		a = a - b;
		return a;
	}

	/**
	* Vector3同士の代入乗算
	*/
	Vector3 operator*=(Vector3& a, const Vector3& b)
	{
		a = a * b;
		return a;
	}

	/**
	* Vector3同士の代入除算
	*/
	Vector3 operator/=(Vector3& a, const Vector3& b)
	{
		a = a / b;
		return a;
	}

	/**
	* Vector3とfloatの代入乗算
	*/
	Vector3 operator*=(Vector3& v, float f)
	{
		v = v * f;
		return v;
	}

	/**
	* Vector3とfloatの代入乗算
	*/
	Vector3 operator/=(Vector3& v, float f)
	{
		v = v / f;
		return v;
	}

	/**
	* Vector3同士の比較演算
	*/
	bool operator==(const Vector3& a, const Vector3& b)
	{
		return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
	}

	/**
	* Vector3同士の比較演算
	*/
	bool operator!=(const Vector3& a, const Vector3& b)
	{
		return ((a.x != b.x) || (a.y != b.y) || (a.z != b.z));
	}
}