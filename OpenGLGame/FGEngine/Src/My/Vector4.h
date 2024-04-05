/**
* @file Vector4.h
*/
#ifndef FGENGINE_VECTOR4_H_INCLUDED
#define FGENGINE_VECTOR4_H_INCLUDED
#include "VectorFrd.h"

namespace FGEngine
{

	// �l�����x�N�g��
	struct Vector4
	{

		Vector4() = default;

		// 4��float����Vector4���\�z����R���X�g���N�^
		explicit Vector4(float x, float y, float z, float w);

		// Vector2��2��float����Vector4���\�z����R���X�g���N�^
		explicit Vector4(const Vector2& v, float z, float w);

		// Vector3�ƂP��float����Vector3���\�z����R���X�g���N�^
		explicit Vector4(const Vector3& v, float w);

		/**
		* �x�N�g���𐳋K�����ꂽ�x�N�g��(�P�ʃx�N�g��)�ɂ���
		*/
		void Normalize();

		/**
		* ���K�����ꂽ�x�N�g��(�P�ʃx�N�g��)���擾
		*
		* @return ���K�����ꂽ�x�N�g��
		*/
		Vector4 Normalized() const;

		/**
		* �x�N�g���̑傫��(����)���v�Z����
		*
		* @return �x�N�g���̑傫��
		*/
		float Magnitude() const;


	public:

		// �x�N�g����X����
		float x;

		// �x�N�g����Y����
		float y;

		// �x�N�g����Z����
		float z;

		// �x�N�g����W����
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
