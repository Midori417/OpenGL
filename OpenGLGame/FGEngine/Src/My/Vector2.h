/**
* @file Vector2.h
*/
#ifndef VECTOR2_H_INCLUDED
#define VECTOR2_H_INCLUDED

#include "VectorFrd.h"

namespace FGEngine
{

	/**
	* �񎟌��x�N�g��
	*/
	struct Vector2
	{
		// �R���X�g���N�^
		Vector2() = default;
		explicit constexpr Vector2(const Vector3&);
		explicit constexpr Vector2(const Vector4&);
		explicit constexpr Vector2(float n) : x(n), y(n) {}
		explicit constexpr Vector2(float x, float y) : x(x), y(y) {}

		// ���g�𐳋K������
		void Normalize();

		// �e�v�f�����̊e�v�f�Ə�Z����
		void Scale(const Vector2& v);

		// a��b�̃x�N�g���̓��ς�Ԃ�
		static float Dot(const Vector2& a, const Vector2& b);

		// a��b�̃x�N�g���̊Ԃ̋�����Ԃ�
		static float Distance(const Vector2& a, const Vector2& b);

		// a��b�̊Ԃ�t(Clamp0�`1)�Ő��`��Ԃ���
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

		// a��b�̂̊Ԃ�t�Ő��`��Ԃ���
		static Vector2 LerpUnclamped(const Vector2& a, const Vector2& b, float t);

		// ���݂̈ʒucurrent����target�Ɍ����Ĉړ�����
		static Vector2 MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta);

		// a��b�̃x�N�g���̐�������Z���ĕԂ�
		static Vector2 Scale(const Vector2& a, const Vector2& b);

		// a��b�̃x�N�g���Ŋe�����̈�ԑ傫�Ȓl���g�p���ăx�N�g�����쐬
		static Vector2 Max(const Vector2& a, const Vector2& b);

		// a��b�̃x�N�g���Ŋe�����̈�ԏ����Ȓl���g�p���ăx�N�g�����쐬
		static Vector2 Min(const Vector2& a, const Vector2& b);

	public:

		float x, y;

		// �x�N�g���̒����Ԃ�
		float magnitude()const;

		// �x�N�g���̒������悵�ĕԂ�
		float sqrtMagnitude() const;

		// ���K���x�N�g���Ԃ�
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

	// Vector2�̒P��-���Z�q
	Vector2 operator-(const Vector2& a);

	// Vector2���m�̉��Z
	Vector2& operator+=(Vector2& a, const Vector2& b);
	Vector2 operator+(const Vector2& a, const Vector2& b);

	// Vector2��float�̉��Z
	Vector2& operator+=(Vector2& a, float b);
	Vector2 operator+(const Vector2& a, float b);
	Vector2 operator+(float a, const Vector2& b);

	// Vector2���m�̌��Z
	Vector2& operator-=(Vector2& a, const Vector2& b);
	Vector2 operator-(const Vector2& a, const Vector2& b);

	// Vector2��float�̌��Z
	Vector2& operator-=(Vector2& a, float b);
	Vector2 operator-(const Vector2& a, float b);
	Vector2 operator-(float a, const Vector2& b);

	// Vector2���m�̏�Z
	Vector2& operator*=(Vector2& a, const Vector2& b);
	Vector2 operator*(const Vector2& a, const Vector2& b);

	// Vector2��float�̏�Z
	Vector2& operator*=(Vector2& a, float b);
	Vector2 operator*(const Vector2& a, float b);
	Vector2 operator*(float a, const Vector2& b);

	// Vector2���m�̏��Z
	Vector2& operator/=(Vector2& a, const Vector2& b);
	Vector2 operator/(const Vector2& a, const Vector2& b);

	// Vector2��float�̏��Z
	Vector2& operator/=(Vector2& a, float b);
	Vector2 operator/(const Vector2& a, float b);
	Vector2 operator/(float a, const Vector2& b);

	// Vector2���m�̔�r���Z
	bool operator==(const Vector2& a, const Vector2& b);
	bool operator!=(const Vector2& a, const Vector2& b);
}
#endif // !VECTOR2_H_INCLUDED
