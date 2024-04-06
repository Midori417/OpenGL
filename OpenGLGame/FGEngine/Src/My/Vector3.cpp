/**
* @file Vector3.cpp
*/
#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Mathf.h"

namespace FGEngine
{

	// スタティック変数の初期化
	const Vector3 Vector3::zero = Vector3(0, 0, 0);
	const Vector3 Vector3::one = Vector3(1, 1, 1);
	const Vector3 Vector3::up = Vector3(0, 1, 0);
	const Vector3 Vector3::down = Vector3(0, -1, 0);
	const Vector3 Vector3::left = Vector3(-1, 0, 0);
	const Vector3 Vector3::right = Vector3(1, 0, 0);
	const Vector3 Vector3::forward = Vector3(0, 0, 1);
	const Vector3 Vector3::back = Vector3(0, 0, -1);

	/**
	* 3個のfloatからVector3を構築するコンストラクタ
	*/
	Vector3::Vector3(float x, float y, float z)
		:x(x), y(y),z (z)
	{
	}

	/**
	* Vector2からVector3を構築するコンストラクタ
	*/
	Vector3::Vector3(const Vector2& v, float z)
		: x(v.x), y(v.y),z(z)
	{
	}

	/**
	* Vector4からVector3を構築するコンストラクタ
	*/
	Vector3::Vector3(const Vector4& v)
		: x(v.x), y(v.y), z(v.z)
	{
	}

	/**
	* ベクトルを正規化されたベクトル(単位ベクトル)にする
	*/
	void Vector3::Normalize()
	{
		float num = Magnitude();
		if (num > 0.0f) {
			*this /= num;
		}
		else
		{
			*this = Vector3::zero;
		}
	}

	/**
	* 正規化されたベクトル(単位ベクトル)を取得
	*
	* @return 正規化されたベクトル
	*/
	Vector3 Vector3::Normalized() const
	{
		Vector3 result = Vector3(x, y, z);
		result.Normalize();
		return result;
	}

	/**
	* ベクトルの大きさ(長さ)を計算する
	*
	* @return ベクトルの大きさ
	*/
	float Vector3::Magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y + z * z);
	}

	/**
	* 2つのベクトルの内積(ドット積)を計算する
	*
	* @param a ベクトル1
	* @param b ベクトル2
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
	* @param a ベクトル1
	* @param b ベクトル2
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
	*  2つのベクトルの距離(長さ)を計算する
	*
	* @param a ベクトル1
	* @param b ベクトル2
	*
	* @return aとbの距離
	*/
	float Vector3::Distance(const Vector3& a, const Vector3& b)
	{
		Vector3 tmp = a - b;
		return Mathf::Sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
	}

	/**
	* ベクトル a と ベクトル b の間を線形補間する
	*
	* @param a 補間の開始ベクトル
	* @param b 補間の終了ベクトル
	* @param t 補間パラメータ (0.0 ~ 1.0 の範囲)
	*
	* @return 補間されたベクトル
	*/
	Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
	{
		// 値を補完する
		t = Mathf::Clamp01(t);

		return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
	}


	/**
	* -単項演算子
	*/
	Vector3 operator-(const Vector3& a)
	{
		return Vector3(-a.x, -a.y, -a.z);
	}

	//=======================================
	//  加算
	//=======================================

	/**
	* Vector3同士の代入演算
	*/
	Vector3& operator+=(Vector3& a, const Vector3& b)
	{
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
		return a;
	}

	/**
	* Vector3同士の演算
	*/
	Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/**
	* Vector3とfloatの代入演算
	*/
	Vector3& operator+=(Vector3& a, float b)
	{
		return a += Vector3(b, b, b);
	}

	/**
	* Vector3とfloatの演算
	*/
	Vector3 operator+(const Vector3& a, float b)
	{
		return a + Vector3(b, b, b);
	}

	/**
	* floatとVector3の演算
	*/
	Vector3 operator+(float a, const Vector3& b)
	{
		return b + a;
	}

	//=======================================
	//  加算
	//=======================================

	/**
	* Vector3同士の代入演算
	*/
	Vector3& operator-=(Vector3& a, const Vector3& b)
	{
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
		return a;
	}

	/**
	* Vector3同士の演算
	*/
	Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/**
	* Vector3とfloatの代入演算
	*/
	Vector3& operator-=(Vector3& a, float b)
	{
		return a -= Vector3(b, b, b);
	}

	/**
	* Vector3とfloatの演算
	*/
	Vector3 operator-(const Vector3& a, float b)
	{
		return a - Vector3(b, b, b);
	}

	/**
	* floatとVector3の演算
	*/
	Vector3 operator-(float a, const Vector3& b)
	{
		return b - a;
	}

	//=======================================
	//  乗算
	//=======================================

	/**
	* Vector3同士の代入演算
	*/
	Vector3& operator*=(Vector3& a, const Vector3& b)
	{
		a.x *= b.x;
		a.y *= b.y;
		a.z *= b.z;
		return a;
	}

	/**
	* Vector3同士の演算
	*/
	Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	/**
	* Vector3とfloatの代入演算
	*/
	Vector3& operator*=(Vector3& a, float b)
	{
		return a *= Vector3(b, b, b);
	}

	/**
	* Vector3とfloatの演算
	*/
	Vector3 operator*(const Vector3& a, float b)
	{
		return a * Vector3(b, b, b);
	}

	/**
	* floatとVector3の演算
	*/
	Vector3 operator*(float a, const Vector3& b)
	{
		return b * a;
	}

	//=======================================
	//	除算
	//=======================================

	/**
	*　Vector3同士の代入演算
	*/
	Vector3& operator/=(Vector3& a, const Vector3& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0 || a.z == 0 || b.z == 0) {
		}
		a.x /= b.x;
		a.y /= b.y;
		a.z /= b.z;
		return a;
	}

	/**
	* Vector3同士の演算
	*/
	Vector3 operator/(const Vector3& a, const Vector3& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0 || a.z == 0 || b.z == 0) {
		}
		return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	/**
	* Vector3とfloatの代入演算
	*/
	Vector3& operator/=(Vector3& a, float b)
	{
		if (a.x == 0 || a.y == 0 || a.z == 0 || b == 0) {
		}
		return a /= Vector3(b, b, b);
	}

	/**
	* Vector3とfloatの演算
	*/
	Vector3 operator/(const Vector3& a, float b)
	{
		if (a.x == 0 || a.y == 0 || b == 0) {
		}
		return a / Vector3(b, b, b);
	}

	Vector3 operator/(float a, const Vector3& b)
	{
		if (b.x == 0 || b.y == 0 || b.z == 0 || a == 0) {
		}
		return b / a;
	}

	//=======================================
	//	比較
	//=======================================

	bool operator==(const Vector3& a, const Vector3& b)
	{
		return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
	}

	bool operator!=(const Vector3& a, const Vector3& b)
	{
		return !(a == b);
	}
}