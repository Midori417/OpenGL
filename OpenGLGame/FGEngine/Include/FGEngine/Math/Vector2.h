/**
* @file Vector2.h
*/
#ifndef FGENGINE_VECTOR2_H_INCLUDED
#define FGENGINE_VECTOR2_H_INCLUDED
#include "MathFrd.h"

namespace FGEngine
{
	/**
	* 二次元ベクトル
	*/
	struct Vector2
	{
		/**
		* デフォルトコンストラクタ
		*/
		Vector2() = default;

		/**
		* 2個のfloatからVector2を作成するコンストラクタ
		*
		* @param x X成分
		* @param y Y成分
		*/
		explicit Vector2(float x, float y);

		/**
		* 1個のfloatからVector2を作成するコンストラクタ
		*
		* @param v XYの成分
		*/
		explicit Vector2(float v);

		/**
		* Vector3からVector2を構築するコンストラクタ
		*
		* @param v Vector3のXY成分
		*/
		explicit Vector2(const Vector3& v);

		/**
		* Vector4からVector2を構築するコンストラクタ
		*
		* @param v Vector4のXY成分
		*/
		explicit Vector2(const Vector4& v);

		/**
		* ベクトルの正規化を計算する
		*/
		static Vector2 Normalize(const Vector2& v);

		/**
		* ベクトルの内積を計算する
		*
		* @return aとbの内積
		*/
		static float Dot(const Vector2& a, const Vector2& b);

		/**
		* 2つのベクトルの距離を計算する
		*
		* return aとbの距離
		*/
		static float Distance(const Vector2& a, const Vector2& b);

		/**
		* 2つのベクトルの間を線形補間する
		*
		* @param a 補間の開始ベクトル
		* @param b 補間の終了ベクトル
		* @param t 補間パラメータ (0.0 ~ 1.0 の範囲)
		*
		* @return 補間されたベクトル
		*/
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

	public:

		// X成分
		float x;

		// Y成分
		float y;

		// Vector2(0, 0)
		static const Vector2 zero;

		// Vector2(1, 1)
		static const Vector2 one;

		// Vector2(0, 1)
		static const Vector2 up;

		// Vector2(0,-1)
		static const Vector2 down;

		// Vector2(0,-1)
		static const Vector2 left;

		// Vector2(0,1)
		static const Vector2 right;

		float operator[](size_t i)const
		{
			return *(&x + i);
		}
		float& operator[](size_t i)
		{
			return *(&x + i);
		}
	};

	// Vector2同士の演算子
	Vector2 operator+(const Vector2& a, const Vector2& b);
	Vector2 operator-(const Vector2& a, const Vector2& b);
	Vector2 operator*(const Vector2& a, const Vector2& b);
	Vector2 operator/(const Vector2& a, const Vector2& b);

	// Vector2とfloatの演算子
	Vector2 operator*(const Vector2& v, float f);
	Vector2 operator/(const Vector2& v, float f);

	// Vector2同士の代入演算子
	Vector2 operator+=(Vector2& a, const Vector2& b);
	Vector2 operator-=(Vector2& a, const Vector2& b);
	Vector2 operator*=(Vector2& a, const Vector2& b);
	Vector2 operator/=(Vector2& a, const Vector2& b);

	// Vector2とfloatの代入演算子
	Vector2 operator*=(Vector2& v, float f);
	Vector2 operator/=(Vector2& v, float f);

	// Vector2同士の比較演算子
	bool operator==(const Vector2& a, const Vector2& b);
	bool operator!=(const Vector2& a, const Vector2& b);
}

#endif // !FGENGINE_VECTOR2_H_INCLUDED
