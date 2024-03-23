/**
* @file Vector4.h
*/
#ifndef VECTOR4_H_INCLUDED
#define VECTOR4_H_INCLUDED

#include "VectorFrd.h"

namespace FGEngine
{

	// lŸŒ³ƒxƒNƒgƒ‹
	struct Vector4
	{

		Vector4() = default;
		explicit constexpr Vector4(float n) : x(n), y(n), z(n), w(n) {}
		explicit constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		constexpr Vector4(const Vector2& v, float z, float w);
		constexpr Vector4(const Vector3& v, float w);

		// ³‹K‰»‚·‚é
		void Normalize();

		// a‚Æb‚ÌŠe—v‘f‚ÌÅ‘å’l‚ÌƒxƒNƒgƒ‹‚ğ•Ô‚·
		static Vector4 Max(const Vector4& a, const Vector4& b);

		// a‚Æb‚ÌŠe—v‘f‚ÌÅ¬’l‚ÌƒxƒNƒgƒ‹‚ğ•Ô‚·
		static Vector4 Min(const Vector4& a, const Vector4& b);


	public:

		float x, y, z, w;

		// ƒxƒNƒgƒ‹‚Ì’·‚³
		float magnitude() const;

		// ƒxƒNƒgƒ‹‚Ì“ñæ‚Ì’·‚³
		float sqrtMagnitude() const;

		// ³‹K‰»ƒxƒNƒgƒ‹
		Vector4 normalized() const;

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


	// Vector4‚Ì’P€-‰‰Zq
	Vector4 operator-(const Vector4& a);

	// Vector4“¯m‚Ì‰ÁZ
	Vector4& operator+=(Vector4& a, const Vector4& b);
	Vector4 operator+(const Vector4& a, const Vector4& b);

	// Vector4‚Æfloat‚Ì‰ÁZ
	Vector4& operator+=(Vector4& a, float b);
	Vector4 operator+(const Vector4& a, float b);
	Vector4 operator+(float a, const Vector4& b);

	// Vector4“¯m‚ÌŒ¸Z
	Vector4& operator-=(Vector4& a, const Vector4& b);
	Vector4 operator-(const Vector4& a, const Vector4& b);

	// Vector4‚Æfloat‚ÌŒ¸Z
	Vector4& operator-=(Vector4& a, float b);
	Vector4 operator-(const Vector4& a, float b);
	Vector4 operator-(float a, const Vector4& b);

	// Vector4“¯m‚ÌæZ
	Vector4& operator*=(Vector4& a, const Vector4& b);
	Vector4 operator*(const Vector4& a, const Vector4& b);

	// Vector4‚Æfloat‚ÌæZ
	Vector4& operator*=(Vector4& a, float b);
	Vector4 operator*(const Vector4& a, float b);
	Vector4 operator*(float a, const Vector4& b);

	// Vector4“¯m‚Ì™Z
	Vector4& operator/=(Vector4& a, const Vector4& b);
	Vector4 operator/(const Vector4& a, const Vector4& b);

	// Vector4‚Æfloat‚Ì™Z
	Vector4& operator/=(Vector4& a, float b);
	Vector4 operator/(const Vector4& a, float b);
	Vector4 operator/(float a, const Vector4& b);

	// Vector4“¯m‚Ì”äŠr‰‰Z
	bool operator==(const Vector4& a, const Vector4& b);
	bool operator!=(const Vector4& a, const Vector4& b);
}
#endif // !VECTOR4_H_INCLUDED
