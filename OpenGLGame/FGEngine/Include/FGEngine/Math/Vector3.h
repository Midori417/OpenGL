/**
* @file Vector3.h
*/
#ifndef FGENGINE_VECTOR3_H_INCLUDED
#define FGENGINE_VECTOR3_H_INCLUDED
#include "FGEngine/UsingNames/UsingMath.h"

namespace FGEngine
{
	/**
	* 三次元ベクトル
	*/
	struct Vector3
	{
		/**
		* デフォルトコンストラクタ
		*/
		Vector3() = default;

		/**
		* 3個のfloatからVector3を作成するコンストラクタ
		*
		* @param x X成分
		* @param y Y成分
		* @param z Z成分
		*/
		explicit Vector3(float x, float y, float z);

		/**
		* 1個のfloatからVector3を作成するコンストラクタ
		*
		* @param v XYZ成分
		*/
		explicit Vector3(float v);

		/**
		* Vector2と1個のfloatからVector3を構築するコンストラクタ
		*
		* @param v Vector2のXY成分
		* @param z Z成分
		*/
		explicit Vector3(const Vector2& v, float z);

		/**
		* Vector4からVector3を構築するコンストラクタ
		*
		* @parma v Vector4のXYZ成分
		*/
		explicit Vector3(const Vector4& v);

		/**
		* ベクトルの正規化を計算する
		*/
		static Vector3 Normalize(const Vector3& v);

		/**
		* ベクトルの大きさを計算する
		*/
		static float Magnitude(const Vector3& v);

		/**
		* ベクトルの内積を計算する
		*
		* @return aとbの内積
		*/
		static float Dot(const Vector3& a, const Vector3& b);

		/**
		* 2のベクトルの外積(クロス積)を計算する
		*
		* @return aとbの外積
		*/
		static Vector3 Cross(const Vector3& a, const Vector3& b);

		/**
		* 2つのベクトルの距離を計算する
		*
		* return aとbの距離
		*/
		static float Distance(const Vector3& a, const Vector3& b);

		/**
		* 2つのベクトルの間を線形補間する
		*
		* @param a 補間の開始ベクトル
		* @param b 補間の終了ベクトル
		* @param t 補間パラメータ (0.0 ~ 1.0 の範囲)
		*
		* @return 補間されたベクトル
		*/
		static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	public:

		// X成分
		float x;

		// Y成分
		float y;

		// Z成分
		float z;

		// Vector3(0, 0, 0,)
		static const Vector3 zero;

		// Vector3(1, 1, 1)
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
	Vector3 operator-(const Vector3& v);

	// Vector3同士の演算子
	Vector3 operator+(const Vector3& a, const Vector3& b);
	Vector3 operator-(const Vector3& a, const Vector3& b);
	Vector3 operator*(const Vector3& a, const Vector3& b);
	Vector3 operator/(const Vector3& a, const Vector3& b);

	// Vector3とfloatの演算子
	Vector3 operator*(const Vector3&v, float f);
	Vector3 operator/(const Vector3&v, float f);

	// Vector3同士の代入演算子
	Vector3 operator+=(Vector3& a, const Vector3& b);
	Vector3 operator-=(Vector3& a, const Vector3& b);
	Vector3 operator*=(Vector3& a, const Vector3& b);
	Vector3 operator/=(Vector3& a, const Vector3& b);

	// Vector3とfloatの代入演算子
	Vector3 operator*=(Vector3& v, float f);
	Vector3 operator/=(Vector3& v, float f);

	// Vector3同士の比較演算子
	bool operator==(const Vector3& a, const Vector3& b);
	bool operator!=(const Vector3& a, const Vector3& b);

}

#endif // !FGENGINE_VECTOR3_H_INCLUDUED
