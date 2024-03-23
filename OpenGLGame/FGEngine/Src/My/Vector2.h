/**
* @file Vector2.h
*/
#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED

#include "VectorFrd.h"

namespace FGEngine
{

	/**
	* 二次元ベクトル
	*/
	struct Vector2
	{
		// コンストラクタ
		Vector2() = default;
		explicit constexpr Vector2(const Vector3&);
		explicit constexpr Vector2(const Vector4&);
		explicit constexpr Vector2(float n) : x(n), y(n) {}
		explicit constexpr Vector2(float x, float y) : x(x), y(y) {}

		// 自身を正規化する
		void Normalize();

		// 各要素をｖの各要素と乗算する
		void Scale(const Vector2& v);

		// aとbのベクトルの内積を返す
		static float Dot(const Vector2& a, const Vector2& b);

		// aとbのベクトルの間の距離を返す
		static float Distance(const Vector2& a, const Vector2& b);

		// aとbの間をt(Clamp0～1)で線形補間する
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

		// aとbのの間をtで線形補間する
		static Vector2 LerpUnclamped(const Vector2& a, const Vector2& b, float t);

		// 現在の位置currentからtargetに向けて移動する
		static Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);

		// aとbのベクトルの成分を乗算して返す
		static Vector2 Scale(const Vector2& a, const Vector2& b);

		// aとbのベクトルで各成分の一番大きな値を使用してベクトルを作成
		static Vector2 Max(const Vector2& a, const Vector2& b);

		// aとbのベクトルで各成分の一番小さな値を使用してベクトルを作成
		static Vector2 Min(const Vector2& a, const Vector2& b);

	public:

		float x, y;

		// ベクトルの長さ返す
		float magnitude()const;

		// ベクトルの長さを二乗して返す
		float sqrtMagnitude() const;

		// 正規化ベクトル返す
		Vector2 normalized() const;

		// Vector2(0,0)
		static const Vector2 zero;

		// Vector2(1,1)
		static const Vector2 one;

		// Vector2(0,1)
		static const Vector2 up;

		// Vector2(0,-1)
		static const Vector2 down;

		// Vector2(-1,0)
		static const Vector2 left;

		// Vector2(1,0)
		static const Vector2 right;

		float operator[](size_t i)const {
			return *(&x + i);
		}
		float& operator[](size_t i) {
			return *(&x + i);
		}
	};

	// Vector2の単項-演算子
	Vector2 operator-(const Vector2& a);

	// Vector2同士の加算
	Vector2& operator+=(Vector2& a, const Vector2& b);
	Vector2 operator+(const Vector2& a, const Vector2& b);

	// Vector2とfloatの加算
	Vector2& operator+=(Vector2& a, float b);
	Vector2 operator+(const Vector2& a, float b);
	Vector2 operator+(float a, const Vector2& b);

	// Vector2同士の減算
	Vector2& operator-=(Vector2& a, const Vector2& b);
	Vector2 operator-(const Vector2& a, const Vector2& b);

	// Vector2とfloatの減算
	Vector2& operator-=(Vector2& a, float b);
	Vector2 operator-(const Vector2& a, float b);
	Vector2 operator-(float a, const Vector2& b);

	// Vector2同士の乗算
	Vector2& operator*=(Vector2& a, const Vector2& b);
	Vector2 operator*(const Vector2& a, const Vector2& b);

	// Vector2とfloatの乗算
	Vector2& operator*=(Vector2& a, float b);
	Vector2 operator*(const Vector2& a, float b);
	Vector2 operator*(float a, const Vector2& b);

	// Vector2同士の徐算
	Vector2& operator/=(Vector2& a, const Vector2& b);
	Vector2 operator/(const Vector2& a, const Vector2& b);

	// Vector2とfloatの徐算
	Vector2& operator/=(Vector2& a, float b);
	Vector2 operator/(const Vector2& a, float b);
	Vector2 operator/(float a, const Vector2& b);

	// Vector2同士の比較演算
	bool operator==(const Vector2& a, const Vector2& b);
	bool operator!=(const Vector2& a, const Vector2& b);
}
#endif // !VECTOR2_H_INCLUDED
