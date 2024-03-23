/**
* @file Vector3.h
*/
#ifndef VECTOR3_H_INCLUDED
#define VECTOR3_H_INCLUDED

#include "VectorFrd.h"

namespace FGEngine
{

	// 三次元ベクトル
	struct Vector3
	{

		Vector3() = default;
		explicit constexpr Vector3(float n) : x(n), y(n), z(n) {}
		constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		explicit constexpr Vector3(const Vector2& v, float z);
		explicit constexpr Vector3(const Vector4&);

		// 自身のベクトルを正規化する
		void Normalize();

		// 各要素をｖの各要素と乗算する
		void Scale(const Vector3& v);

		// aとbのベクトルの内積を返す
		static float Dot(const Vector3& a, const Vector3& b);

		// aとbのベクトルの外積を返す
		static Vector3 Cross(const Vector3& a, const Vector3& b);

		// aとbのベクトルの間の距離を返す
		static float Distance(const Vector3& a, const Vector3& b);

		// aとbの間をt(Clamp0～1)で線形補間する
		static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

		// aとbのの間をtで線形補間する
		static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);

		// 現在の位置currentからtargetに向けて移動する
		static Vector3 MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);

		// aとbのベクトルの成分を乗算して返す
		static Vector3 Scale(const Vector3& a, const Vector3& b);

		// aとbのベクトルで各成分の一番大きな値を使用してベクトルを作成
		static Vector3 Max(const Vector3& a, const Vector3& b);

		// aとbのベクトルで各成分の一番小さな値を使用してベクトルを作成
		static Vector3 Min(const Vector3& a, const Vector3& b);

	public:

		float x, y, z;

		// ベクトルの長さ返す
		float magnitude()const;

		// ベクトルの長さを二乗して返す
		float sqrtMagnitude() const;

		// 正規化ベクトル返す
		Vector3 normalized() const;

		// Vector3(0,0,0)
		static const Vector3 zero;

		// Vector3(1,1,1)
		static const Vector3 one;

		// Vector3(0,1,0)
		static const Vector3 up;

		// Vector3(0,-1,0)
		static const Vector3 down;

		// Vector3(0,-1,0)
		static const Vector3 left;

		// Vector3(0,1,0)
		static const Vector3 right;

		// Vector3(0,0,1)
		static const Vector3 forward;

		// Vector3(0,0,-1)
		static const Vector3 back;

		float operator[](size_t i)const {
			return *(&x + i);
		}
		float& operator[](size_t i) {
			return *(&x + i);
		}
	};

	// Vector3の単項-演算子
	Vector3 operator-(const Vector3& a);

	// Vector3同士の加算
	Vector3& operator+=(Vector3& a, const Vector3& b);
	Vector3 operator+(const Vector3& a, const Vector3& b);

	// Vector3とfloatの加算
	Vector3& operator+=(Vector3& a, float b);
	Vector3 operator+(const Vector3& a, float b);
	Vector3 operator+(float a, const Vector3& b);

	// Vector3同士の減算
	Vector3& operator-=(Vector3& a, const Vector3& b);
	Vector3 operator-(const Vector3& a, const Vector3& b);

	// Vector3とfloatの減算
	Vector3& operator-=(Vector3& a, float b);
	Vector3 operator-(const Vector3& a, float b);
	Vector3 operator-(float a, const Vector3& b);

	// Vector3同士の乗算
	Vector3& operator*=(Vector3& a, const Vector3& b);
	Vector3 operator*(const Vector3& a, const Vector3& b);

	// Vector3とfloatの乗算
	Vector3& operator*=(Vector3& a, float b);
	Vector3 operator*(const Vector3& a, float b);
	Vector3 operator*(float a, const Vector3& b);

	// Vector3同士の徐算
	Vector3& operator/=(Vector3& a, const Vector3& b);
	Vector3 operator/(const Vector3& a, const Vector3& b);

	// Vector3とfloatの徐算
	Vector3& operator/=(Vector3& a, float b);
	Vector3 operator/(const Vector3& a, float b);
	Vector3 operator/(float a, const Vector3& b);

	// Vector3同士の比較演算
	bool operator==(const Vector3& a, const Vector3& b);
	bool operator!=(const Vector3& a, const Vector3& b);
}
#endif // !VECTOR3_H_INCLUDED
