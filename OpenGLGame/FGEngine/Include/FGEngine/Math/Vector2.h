/**
* @file Vector2.h
*/
#ifndef FGENGINE_VECTOR2_H_INCLUDED
#define FGENGINE_VECTOR2_H_INCLUDED
#include "MathFrd.h"

namespace FGEngine
{
	/**
	* �񎟌��x�N�g��
	*/
	struct Vector2
	{
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Vector2() = default;

		/**
		* 2��float����Vector2���쐬����R���X�g���N�^
		*
		* @param x X����
		* @param y Y����
		*/
		explicit Vector2(float x, float y);

		/**
		* 1��float����Vector2���쐬����R���X�g���N�^
		*
		* @param v XY�̐���
		*/
		explicit Vector2(float v);

		/**
		* Vector3����Vector2���\�z����R���X�g���N�^
		*
		* @param v Vector3��XY����
		*/
		explicit Vector2(const Vector3& v);

		/**
		* Vector4����Vector2���\�z����R���X�g���N�^
		*
		* @param v Vector4��XY����
		*/
		explicit Vector2(const Vector4& v);

		/**
		* �x�N�g���̐��K�����v�Z����
		*/
		static Vector2 Normalize(const Vector2& v);

		/**
		* �x�N�g���̓��ς��v�Z����
		*
		* @return a��b�̓���
		*/
		static float Dot(const Vector2& a, const Vector2& b);

		/**
		* 2�̃x�N�g���̋������v�Z����
		*
		* return a��b�̋���
		*/
		static float Distance(const Vector2& a, const Vector2& b);

		/**
		* 2�̃x�N�g���̊Ԃ���`��Ԃ���
		*
		* @param a ��Ԃ̊J�n�x�N�g��
		* @param b ��Ԃ̏I���x�N�g��
		* @param t ��ԃp�����[�^ (0.0 ~ 1.0 �͈̔�)
		*
		* @return ��Ԃ��ꂽ�x�N�g��
		*/
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);

	public:

		// X����
		float x;

		// Y����
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

	// Vector2���m�̉��Z�q
	Vector2 operator+(const Vector2& a, const Vector2& b);
	Vector2 operator-(const Vector2& a, const Vector2& b);
	Vector2 operator*(const Vector2& a, const Vector2& b);
	Vector2 operator/(const Vector2& a, const Vector2& b);

	// Vector2��float�̉��Z�q
	Vector2 operator*(const Vector2& v, float f);
	Vector2 operator/(const Vector2& v, float f);

	// Vector2���m�̑�����Z�q
	Vector2 operator+=(Vector2& a, const Vector2& b);
	Vector2 operator-=(Vector2& a, const Vector2& b);
	Vector2 operator*=(Vector2& a, const Vector2& b);
	Vector2 operator/=(Vector2& a, const Vector2& b);

	// Vector2��float�̑�����Z�q
	Vector2 operator*=(Vector2& v, float f);
	Vector2 operator/=(Vector2& v, float f);

	// Vector2���m�̔�r���Z�q
	bool operator==(const Vector2& a, const Vector2& b);
	bool operator!=(const Vector2& a, const Vector2& b);
}

#endif // !FGENGINE_VECTOR2_H_INCLUDED
