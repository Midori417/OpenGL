/**
* @file Vector4.h
*/
#ifndef FGENGINE_VECTOR4_H_INCLUDED
#define FGENGINE_VECTOR4_H_INCLUDED
#include "VectorFrd.h"

namespace FGEngine
{

	// 四次元ベクトル
	struct Vector4
	{

		Vector4() = default;

		// 4個のfloatからVector4を構築するコンストラクタ
		explicit Vector4(float x, float y, float z, float w);

		// Vector2と2個のfloatからVector4を構築するコンストラクタ
		explicit Vector4(const Vector2& v, float z, float w);

		// Vector3と１個のfloatからVector3を構築するコンストラクタ
		explicit Vector4(const Vector3& v, float w);

		/**
		* ベクトルを正規化されたベクトル(単位ベクトル)にする
		*/
		void Normalize();

		/**
		* 正規化されたベクトル(単位ベクトル)を取得
		*
		* @return 正規化されたベクトル
		*/
		Vector4 Normalized() const;

		/**
		* ベクトルの大きさ(長さ)を計算する
		*
		* @return ベクトルの大きさ
		*/
		float Magnitude() const;


	public:

		// ベクトルのX成分
		float x;

		// ベクトルのY成分
		float y;

		// ベクトルのZ成分
		float z;

		// ベクトルのW成分
		float w;

		// Vector4(0,0,0,0)
		const static Vector4 zero;

		// Vector4(1,1,1,1)
		const static Vector4 one;

		float operator[](size_t i)const {
			return *(&x + i);
		}
		float& operator[](size_t i) {
			return *(&x + i);
		}
	};


	// Vector4の単項-演算子
	Vector4 operator-(const Vector4& a);

	// Vector4同士の加算
	Vector4& operator+=(Vector4& a, const Vector4& b);
	Vector4 operator+(const Vector4& a, const Vector4& b);

	// Vector4とfloatの加算
	Vector4& operator+=(Vector4& a, float b);
	Vector4 operator+(const Vector4& a, float b);
	Vector4 operator+(float a, const Vector4& b);

	// Vector4同士の減算
	Vector4& operator-=(Vector4& a, const Vector4& b);
	Vector4 operator-(const Vector4& a, const Vector4& b);

	// Vector4とfloatの減算
	Vector4& operator-=(Vector4& a, float b);
	Vector4 operator-(const Vector4& a, float b);
	Vector4 operator-(float a, const Vector4& b);

	// Vector4同士の乗算
	Vector4& operator*=(Vector4& a, const Vector4& b);
	Vector4 operator*(const Vector4& a, const Vector4& b);

	// Vector4とfloatの乗算
	Vector4& operator*=(Vector4& a, float b);
	Vector4 operator*(const Vector4& a, float b);
	Vector4 operator*(float a, const Vector4& b);

	// Vector4同士の徐算
	Vector4& operator/=(Vector4& a, const Vector4& b);
	Vector4 operator/(const Vector4& a, const Vector4& b);

	// Vector4とfloatの徐算
	Vector4& operator/=(Vector4& a, float b);
	Vector4 operator/(const Vector4& a, float b);
	Vector4 operator/(float a, const Vector4& b);

	// Vector4同士の比較演算
	bool operator==(const Vector4& a, const Vector4& b);
	bool operator!=(const Vector4& a, const Vector4& b);
}
#endif // !VECTOR4_H_INCLUDED
