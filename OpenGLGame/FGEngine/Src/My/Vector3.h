/**
* @file Vector3.h
*/
#ifndef FGENGINE_VECTOR3_H_INCLUDED
#define FGENGINE_VECTOR3_H_INCLUDED

#include "VectorFrd.h"

namespace FGEngine
{

	// 三次元ベクトル
	struct Vector3
	{

		// デフォルトコンストラクタ
		Vector3() = default;

		// 3個のfloatからVector3を構築するコンストラクタ
		explicit Vector3(float x, float y, float z);

		// 1個のfloatからVector3を構築するコンストラクタ
		explicit Vector3(float f);

		// Vector2と1個のfloatからVector3を構築するコンストラクタ
		explicit Vector3(const Vector2& v, float z);

		// Vector4からVector3を構築するコンストラクタ
		explicit Vector3(const Vector4& v);		

		/**
		* ベクトルを正規化されたベクトル(単位ベクトル)にする
		*/
		void Normalize();

		/**
		* 正規化されたベクトル(単位ベクトル)を取得
		*
		* @return 正規化されたベクトル
		*/
		Vector3 Normalized() const;

		/**
		* ベクトルの大きさ(長さ)を計算する
		*
		* @return ベクトルの大きさ
		*/
		float Magnitude() const;

		/**
		* 2つのベクトルの内積(ドット積)を計算する
		*
		* @param a ベクトル1
		* @param b ベクトル2
		*
		* @return aとbの内積
		*/
		static float Dot(const Vector3& a, const Vector3& b);

		/**
		* 2のベクトルの外積(クロス積)を計算する
		* 
		* @param a ベクトル1
		* @param b ベクトル2
		*
		* @return aとbの外積
		*/
		static Vector3 Cross(const Vector3& a, const Vector3& b);

		/**
		*  2つのベクトルの距離(長さ)を計算する
		*
		* @param a ベクトル1
		* @param b ベクトル2
		*
		* @return aとbの距離
		*/
		static float Distance(const Vector3& a, const Vector3& b);

		/**
		* ベクトル a と ベクトル b の間を線形補間する
		*
		* @param a 補間の開始ベクトル
		* @param b 補間の終了ベクトル
		* @param t 補間パラメータ (0.0 ~ 1.0 の範囲)
		*
		* @return 補間されたベクトル
		*/
		static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	public:

		float x, y, z;


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
