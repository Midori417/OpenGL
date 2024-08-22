/**
* @file Vector3.h
*/
#ifndef FGENGINE_VECTOR3_H_INCLUDED
#define FGENGINE_VECTOR3_H_INCLUDED
#include "FGEngine/UsingNames/UsingMath.h"

namespace FGEngine
{
	/**
	* �O�����x�N�g��
	*/
	struct Vector3
	{
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Vector3() = default;

		/**
		* 3��float����Vector3���쐬����R���X�g���N�^
		*
		* @param x X����
		* @param y Y����
		* @param z Z����
		*/
		explicit Vector3(float x, float y, float z);

		/**
		* 1��float����Vector3���쐬����R���X�g���N�^
		*
		* @param v XYZ����
		*/
		explicit Vector3(float v);

		/**
		* Vector2��1��float����Vector3���\�z����R���X�g���N�^
		*
		* @param v Vector2��XY����
		* @param z Z����
		*/
		explicit Vector3(const Vector2& v, float z);

		/**
		* Vector4����Vector3���\�z����R���X�g���N�^
		*
		* @parma v Vector4��XYZ����
		*/
		explicit Vector3(const Vector4& v);

		/**
		* �x�N�g���̐��K�����v�Z����
		*/
		static Vector3 Normalize(const Vector3& v);

		/**
		* �x�N�g���̑傫�����v�Z����
		*/
		static float Magnitude(const Vector3& v);

		/**
		* �x�N�g���̓��ς��v�Z����
		*
		* @return a��b�̓���
		*/
		static float Dot(const Vector3& a, const Vector3& b);

		/**
		* 2�̃x�N�g���̊O��(�N���X��)���v�Z����
		*
		* @return a��b�̊O��
		*/
		static Vector3 Cross(const Vector3& a, const Vector3& b);

		/**
		* 2�̃x�N�g���̋������v�Z����
		*
		* return a��b�̋���
		*/
		static float Distance(const Vector3& a, const Vector3& b);

		/**
		* 2�̃x�N�g���̊Ԃ���`��Ԃ���
		*
		* @param a ��Ԃ̊J�n�x�N�g��
		* @param b ��Ԃ̏I���x�N�g��
		* @param t ��ԃp�����[�^ (0.0 ~ 1.0 �͈̔�)
		*
		* @return ��Ԃ��ꂽ�x�N�g��
		*/
		static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	public:

		// X����
		float x;

		// Y����
		float y;

		// Z����
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

	// �P�����Z�q
	Vector3 operator-(const Vector3& v);

	// Vector3���m�̉��Z�q
	Vector3 operator+(const Vector3& a, const Vector3& b);
	Vector3 operator-(const Vector3& a, const Vector3& b);
	Vector3 operator*(const Vector3& a, const Vector3& b);
	Vector3 operator/(const Vector3& a, const Vector3& b);

	// Vector3��float�̉��Z�q
	Vector3 operator*(const Vector3&v, float f);
	Vector3 operator/(const Vector3&v, float f);

	// Vector3���m�̑�����Z�q
	Vector3 operator+=(Vector3& a, const Vector3& b);
	Vector3 operator-=(Vector3& a, const Vector3& b);
	Vector3 operator*=(Vector3& a, const Vector3& b);
	Vector3 operator/=(Vector3& a, const Vector3& b);

	// Vector3��float�̑�����Z�q
	Vector3 operator*=(Vector3& v, float f);
	Vector3 operator/=(Vector3& v, float f);

	// Vector3���m�̔�r���Z�q
	bool operator==(const Vector3& a, const Vector3& b);
	bool operator!=(const Vector3& a, const Vector3& b);

}

#endif // !FGENGINE_VECTOR3_H_INCLUDUED
