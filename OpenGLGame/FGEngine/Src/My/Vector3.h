/**
* @file Vector3.h
*/
#ifndef VECTOR3_H_INCLUDED
#define VECTOR3_H_INCLUDED

#include "VectorFrd.h"

namespace FGEngine
{

	// �O�����x�N�g��
	struct Vector3
	{

		Vector3() = default;
		explicit constexpr Vector3(float n) : x(n), y(n), z(n) {}
		constexpr Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		explicit constexpr Vector3(const Vector2& v, float z);
		explicit constexpr Vector3(const Vector4&);

		// ���g�̃x�N�g���𐳋K������
		void Normalize();

		// �e�v�f�����̊e�v�f�Ə�Z����
		void Scale(const Vector3& v);

		// a��b�̃x�N�g���̓��ς�Ԃ�
		static float Dot(const Vector3& a, const Vector3& b);

		// a��b�̃x�N�g���̊O�ς�Ԃ�
		static Vector3 Cross(const Vector3& a, const Vector3& b);

		// a��b�̃x�N�g���̊Ԃ̋�����Ԃ�
		static float Distance(const Vector3& a, const Vector3& b);

		// a��b�̊Ԃ�t(Clamp0�`1)�Ő��`��Ԃ���
		static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

		// a��b�̂̊Ԃ�t�Ő��`��Ԃ���
		static Vector3 LerpUnclamped(const Vector3& a, const Vector3& b, float t);

		// ���݂̈ʒucurrent����target�Ɍ����Ĉړ�����
		static Vector3 MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta);

		// a��b�̃x�N�g���̐�������Z���ĕԂ�
		static Vector3 Scale(const Vector3& a, const Vector3& b);

		// a��b�̃x�N�g���Ŋe�����̈�ԑ傫�Ȓl���g�p���ăx�N�g�����쐬
		static Vector3 Max(const Vector3& a, const Vector3& b);

		// a��b�̃x�N�g���Ŋe�����̈�ԏ����Ȓl���g�p���ăx�N�g�����쐬
		static Vector3 Min(const Vector3& a, const Vector3& b);

	public:

		float x, y, z;

		// �x�N�g���̒����Ԃ�
		float magnitude()const;

		// �x�N�g���̒������悵�ĕԂ�
		float sqrtMagnitude() const;

		// ���K���x�N�g���Ԃ�
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

	// Vector3�̒P��-���Z�q
	Vector3 operator-(const Vector3& a);

	// Vector3���m�̉��Z
	Vector3& operator+=(Vector3& a, const Vector3& b);
	Vector3 operator+(const Vector3& a, const Vector3& b);

	// Vector3��float�̉��Z
	Vector3& operator+=(Vector3& a, float b);
	Vector3 operator+(const Vector3& a, float b);
	Vector3 operator+(float a, const Vector3& b);

	// Vector3���m�̌��Z
	Vector3& operator-=(Vector3& a, const Vector3& b);
	Vector3 operator-(const Vector3& a, const Vector3& b);

	// Vector3��float�̌��Z
	Vector3& operator-=(Vector3& a, float b);
	Vector3 operator-(const Vector3& a, float b);
	Vector3 operator-(float a, const Vector3& b);

	// Vector3���m�̏�Z
	Vector3& operator*=(Vector3& a, const Vector3& b);
	Vector3 operator*(const Vector3& a, const Vector3& b);

	// Vector3��float�̏�Z
	Vector3& operator*=(Vector3& a, float b);
	Vector3 operator*(const Vector3& a, float b);
	Vector3 operator*(float a, const Vector3& b);

	// Vector3���m�̏��Z
	Vector3& operator/=(Vector3& a, const Vector3& b);
	Vector3 operator/(const Vector3& a, const Vector3& b);

	// Vector3��float�̏��Z
	Vector3& operator/=(Vector3& a, float b);
	Vector3 operator/(const Vector3& a, float b);
	Vector3 operator/(float a, const Vector3& b);

	// Vector3���m�̔�r���Z
	bool operator==(const Vector3& a, const Vector3& b);
	bool operator!=(const Vector3& a, const Vector3& b);
}
#endif // !VECTOR3_H_INCLUDED
