/**
* @file Vector4.h
*/
#ifndef VECTOR4_H_INCLUDED
#define VECTOR4_H_INCLUDED

#include "VectorFrd.h"

namespace FGEngine
{

	// �l�����x�N�g��
	struct Vector4
	{

		Vector4() = default;
		explicit constexpr Vector4(float n) : x(n), y(n), z(n), w(n) {}
		explicit constexpr Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
		constexpr Vector4(const Vector2& v, float z, float w);
		constexpr Vector4(const Vector3& v, float w);

		// ���K������
		void Normalize();

		// a��b�̊e�v�f�̍ő�l�̃x�N�g����Ԃ�
		static Vector4 Max(const Vector4& a, const Vector4& b);

		// a��b�̊e�v�f�̍ŏ��l�̃x�N�g����Ԃ�
		static Vector4 Min(const Vector4& a, const Vector4& b);


	public:

		float x, y, z, w;

		// �x�N�g���̒���
		float magnitude() const;

		// �x�N�g���̓��̒���
		float sqrtMagnitude() const;

		// ���K���x�N�g��
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


	// Vector4�̒P��-���Z�q
	Vector4 operator-(const Vector4& a);

	// Vector4���m�̉��Z
	Vector4& operator+=(Vector4& a, const Vector4& b);
	Vector4 operator+(const Vector4& a, const Vector4& b);

	// Vector4��float�̉��Z
	Vector4& operator+=(Vector4& a, float b);
	Vector4 operator+(const Vector4& a, float b);
	Vector4 operator+(float a, const Vector4& b);

	// Vector4���m�̌��Z
	Vector4& operator-=(Vector4& a, const Vector4& b);
	Vector4 operator-(const Vector4& a, const Vector4& b);

	// Vector4��float�̌��Z
	Vector4& operator-=(Vector4& a, float b);
	Vector4 operator-(const Vector4& a, float b);
	Vector4 operator-(float a, const Vector4& b);

	// Vector4���m�̏�Z
	Vector4& operator*=(Vector4& a, const Vector4& b);
	Vector4 operator*(const Vector4& a, const Vector4& b);

	// Vector4��float�̏�Z
	Vector4& operator*=(Vector4& a, float b);
	Vector4 operator*(const Vector4& a, float b);
	Vector4 operator*(float a, const Vector4& b);

	// Vector4���m�̏��Z
	Vector4& operator/=(Vector4& a, const Vector4& b);
	Vector4 operator/(const Vector4& a, const Vector4& b);

	// Vector4��float�̏��Z
	Vector4& operator/=(Vector4& a, float b);
	Vector4 operator/(const Vector4& a, float b);
	Vector4 operator/(float a, const Vector4& b);

	// Vector4���m�̔�r���Z
	bool operator==(const Vector4& a, const Vector4& b);
	bool operator!=(const Vector4& a, const Vector4& b);
}
#endif // !VECTOR4_H_INCLUDED
