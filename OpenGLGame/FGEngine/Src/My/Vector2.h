/**
* @file Vector2.h
*/
#ifndef FGENGINE_VECTOR2_H_INCLUDED
#define FGENGINE_VECTOR2_H_INCLUDED
#include "VectorFrd.h"

namespace FGEngine
{

	/**
	* 二次元ベクトル
	*/
	struct Vector2
	{
		// デフォルトコンストラクタ
		Vector2() = default;

		// 2個のfloatからVector2を構築するコンストラクタ
		explicit Vector2(float x, float y);

		// Vector3からVector2を構築するコンストラクタ
		explicit Vector2(const Vector3& v);

		// Vector4からVector2を構築するコンストラクタ
		explicit Vector2(const Vector4& v);

		/**
		* ベクトルを正規化されたベクトル(単位ベクトル)にする
		*/
		void Normalize();

		/**
		* 正規化されたベクトル(単位ベクトル)を取得
		*
		* @return 正規化されたベクトル
		*/
		Vector2 Normalized() const;

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
		static float Dot(const Vector2& a, const Vector2& b);

		/**
		*  2つのベクトルの距離(長さ)を計算する
		*
		* @param a ベクトル1
		* @param b ベクトル2
		*
		* @return aとbの距離
		*/
		static float Distance(const Vector2& a, const Vector2& b);

		/**
		* ベクトル a と ベクトル b の間を線形補間する
		*
		* @param a 補間の開始ベクトル
		* @param b 補間の終了ベクトル
		* @param t 補間パラメータ (0.0 ~ 1.0 の範囲)
		*
		* @return 補間されたベクトル
		*/
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);


	public:

		// ベクトルのX成分
		float x;

		// ベクトルのY成分
		float y;

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
