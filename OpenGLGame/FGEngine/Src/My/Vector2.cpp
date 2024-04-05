/**
* @file Vector2.cpp
*/
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mathf.h"

namespace FGEngine
{
	// スタティック変数の初期化
	const Vector2 Vector2::zero = Vector2(0, 0);
	const Vector2 Vector2::one = Vector2(1, 1);
	const Vector2 Vector2::up = Vector2(0, 1);
	const Vector2 Vector2::down = Vector2(0, -1);
	const Vector2 Vector2::left = Vector2(-1, 0);
	const Vector2 Vector2::right = Vector2(1, 0);

	/**
	* 2個のfloatからVector2を構築するコンストラクタ
	* 
	* @param x X成分
	* @param y Y成分
	*/
	Vector2::Vector2(float x, float y)
		: x(x), y(y)
	{
	}

	/**
	* Vector3からVector2を構築するコンストラクタ
	*/
	Vector2::Vector2(const Vector3& v)
		:x(v.x), y(v.y)
	{

	}

	/**
	* Vector4からVector2を構築するコンストラクタ
	*/
	Vector2::Vector2(const Vector4& v)
		:x(v.x), y(v.y)
	{

	}

	/**
	* ベクトルを正規化されたベクトル(単位ベクトル)にする
	*/
	void Vector2::Normalize()
	{
		float num = Magnitude();
		if (num > 0.0f) {
			*this /= num;
		}
		else
		{
			*this = Vector2::zero;
		}
	}

	/**
	* 正規化されたベクトル(単位ベクトル)を取得
	*
	* @return 正規化されたベクトル
	*/
	Vector2 Vector2::Normalized() const
	{
		Vector2 result = Vector2(x, y);
		result.Normalize();
		return result;
	}

	/**
	* ベクトルの大きさ(長さ)を計算する
	*
	* @return ベクトルの大きさ
	*/
	float Vector2::Magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y);
	}

	/**
	* 2つのベクトルの内積(ドット積)を計算する
	*
	* @param a ベクトル1
	* @param b ベクトル2
	* 
	* @return aとbの内積
	*/
	float Vector2::Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/**
	*  2つのベクトルの距離(長さ)を計算する
	*
	* @param a ベクトル1
	* @param b ベクトル2
	* 
	* @return aとbの距離	
	*/
	float Vector2::Distance(const Vector2& a, const Vector2& b)
	{
		float num = a.x - b.x;
		float num2 = a.y - b.y;
		return Mathf::Sqrt(num * num + num2 * num2);
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
	Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
	}

	//=======================================
	//
	//  Operator
	//
	//=======================================

	/**
	* -単項演算子
	*/
	Vector2 operator-(const Vector2& a)
	{
		return Vector2(-a.x, -a.y);
	}

	//=======================================
	//  加算
	//=======================================

	/**
	* Vector2同士の代入演算
	*/
	Vector2& operator+=(Vector2& a, const Vector2& b)
	{
		a.x += b.x;
		a.y += b.y;
		return a;
	}

	/**
	* Vector2同士の演算
	*/
	Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	/**
	* Vector2とfloatの代入演算
	*/
	Vector2& operator+=(Vector2& a, float b)
	{
		return a += Vector2(b, b);
	}

	/**
	* Vector2とfloatの演算
	*/
	Vector2 operator+(const Vector2& a, float b)
	{
		return a + Vector2(b, b);
	}

	/**
	* floatとVector2の演算
	*/
	Vector2 operator+(float a, const Vector2& b)
	{
		return b + a;
	}

	//=======================================
	//  加算
	//=======================================

	/**
	* Vector2同士の代入演算
	*/
	Vector2& operator-=(Vector2& a, const Vector2& b)
	{
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}

	/**
	* Vector2同士の演算
	*/
	Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	/**
	* Vector2とfloatの代入演算
	*/
	Vector2& operator-=(Vector2& a, float b)
	{
		return a -= Vector2(b, b);
	}

	/**
	* Vector2とfloatの演算
	*/
	Vector2 operator-(const Vector2& a, float b)
	{
		return a - Vector2(b, b);
	}

	/**
	* floatとVector2の演算
	*/
	Vector2 operator-(float a, const Vector2& b)
	{
		return b - a;
	}

	//=======================================
	//  乗算
	//=======================================

	/**
	* Vector2同士の代入演算
	*/
	Vector2& operator*=(Vector2& a, const Vector2& b)
	{
		a.x *= b.x;
		a.y *= b.y;
		return a;
	}

	/**
	* Vector2同士の演算
	*/
	Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	/**
	* Vector2とfloatの代入演算
	*/
	Vector2& operator*=(Vector2& a, float b)
	{
		return a *= Vector2(b, b);
	}

	/**
	* Vector2とfloatの演算
	*/
	Vector2 operator*(const Vector2& a, float b)
	{
		return a * Vector2(b, b);
	}

	/**
	* floatとVector2の演算
	*/
	Vector2 operator*(float a, const Vector2& b)
	{
		return b * a;
	}

	//=======================================
	//	除算
	//=======================================

	/**
	*　Vector2同士の代入演算
	*/
	Vector2& operator/=(Vector2& a, const Vector2& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0) {
		}
		a.x /= b.x;
		a.y /= b.y;
		return a;
	}

	/**
	* Vector2同士の演算
	*/
	Vector2 operator/(const Vector2& a, const Vector2& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0) {
		}
		return Vector2(a.x / b.x, a.y / b.y);
	}

	/**
	* Vector2とfloatの代入演算
	*/
	Vector2& operator/=(Vector2& a, float b)
	{
		if (a.x == 0 || a.y == 0 || b == 0) {
		}
		return a /= Vector2(b, b);
	}

	Vector2 operator/(const Vector2& a, float b)
	{
		if (a.x == 0 || a.y == 0 || b == 0) {
		}
		return a / Vector2(b, b);
	}

	Vector2 operator/(float a, const Vector2& b)
	{
		if (b.x == 0 || b.y == 0 || a == 0) {
		}
		return b / a;
	}

	//=======================================
	//	比較
	//=======================================

	bool operator==(const Vector2& a, const Vector2& b)
	{
		return ((a.x == b.x) && (a.y == b.y));
	}

	bool operator!=(const Vector2& a, const Vector2& b)
	{
		return ((a.x != b.x) || (a.y != b.y));
	}
}