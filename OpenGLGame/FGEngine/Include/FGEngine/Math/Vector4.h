/**
* @file Vector4.h
*/
#ifndef FGENGINE_VECTOR4_H_INCLUDED
#define FGENGINE_VECTOR4_H_INCLUDED
#include "FGEngine/UsingNames/UsingMath.h"

namespace FGEngine
{
	/**
	* �l�����x�N�g��
	*/
	struct Vector4
	{
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Vector4() = default;

		/**
		* 4��float����Vector4���쐬����R���X�g���N�^
		*
		* @param x X����
		* @param y Y����
		* @param z Z����
		* @param w W����
		*/
		explicit Vector4(float x, float y, float z, float w);

		/**
		* 1��float����Vector4���쐬����R���X�g���N�^
		*
		* @param v XYZW����
		*/
		explicit Vector4(float v);

		/**
		* Vector2��2��float����Vector4���\�z����R���X�g���N�^
		*
		* @param v Vector2��XY����
		* @param z Z����
		* @param w W����
		*/
		explicit Vector4(const Vector2& v, float z, float w);

		/**
		* Vector3��1��float����Vector4���\�z����R���X�g���N�^
		*
		* @param v Vector3��XYZ����
		* @param w W����
		*/
		explicit Vector4(const Vector3& v, float w);

	public:

		// X����
		float x;

		// Y����
		float y;

		// Z����
		float z;

		// W����
		float w;

		// Vector4(0, 0, 0, 0)
		const static Vector4 zero;

		// Vector4(1, 1, 1, 1)
		const static Vector4 one;

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
	Vector4 operator-(const Vector4& v);

	// Vector4���m�̉��Z�q
	Vector4 operator+(const Vector4& a, const Vector4& b);
	Vector4 operator-(const Vector4& a, const Vector4& b);
	Vector4 operator*(const Vector4& a, const Vector4& b);
	Vector4 operator/(const Vector4& a, const Vector4& b);

	// Vector4���m�̑�����Z�q
	Vector4 operator+=(Vector4& a, const Vector4& b);
	Vector4 operator-=(Vector4& a, const Vector4& b);
	Vector4 operator*=(Vector4& a, const Vector4& b);
	Vector4 operator/=(Vector4& a, const Vector4& b);

	// Vector4���m�̔�r���Z�q
	bool operator==(const Vector4& a, const Vector4& b);
	bool operator!=(const Vector4& a, const Vector4& b);
}

#endif // !FGENGINE_VECTOR4_H_INCLUDED
