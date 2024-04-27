/**
* @file Vector3.h
*/
#ifndef FGENGINE_VECTOR3_H_INCLUDED
#define FGENGINE_VECTOR3_H_INCLUDED

#include "VectorFrd.h"

namespace FGEngine
{

	// �O�����x�N�g��
	struct Vector3
	{

		// �f�t�H���g�R���X�g���N�^
		Vector3() = default;

		// 3��float����Vector3���\�z����R���X�g���N�^
		explicit Vector3(float x, float y, float z);

		// 1��float����Vector3���\�z����R���X�g���N�^
		explicit Vector3(float f);

		// Vector2��1��float����Vector3���\�z����R���X�g���N�^
		explicit Vector3(const Vector2& v, float z);

		// Vector4����Vector3���\�z����R���X�g���N�^
		explicit Vector3(const Vector4& v);		

		/**
		* �x�N�g���𐳋K�����ꂽ�x�N�g��(�P�ʃx�N�g��)�ɂ���
		*/
		void Normalize();

		/**
		* ���K�����ꂽ�x�N�g��(�P�ʃx�N�g��)���擾
		*
		* @return ���K�����ꂽ�x�N�g��
		*/
		Vector3 Normalized() const;

		/**
		* �x�N�g���̑傫��(����)���v�Z����
		*
		* @return �x�N�g���̑傫��
		*/
		float Magnitude() const;

		/**
		* 2�̃x�N�g���̓���(�h�b�g��)���v�Z����
		*
		* @param a �x�N�g��1
		* @param b �x�N�g��2
		*
		* @return a��b�̓���
		*/
		static float Dot(const Vector3& a, const Vector3& b);

		/**
		* 2�̃x�N�g���̊O��(�N���X��)���v�Z����
		* 
		* @param a �x�N�g��1
		* @param b �x�N�g��2
		*
		* @return a��b�̊O��
		*/
		static Vector3 Cross(const Vector3& a, const Vector3& b);

		/**
		*  2�̃x�N�g���̋���(����)���v�Z����
		*
		* @param a �x�N�g��1
		* @param b �x�N�g��2
		*
		* @return a��b�̋���
		*/
		static float Distance(const Vector3& a, const Vector3& b);

		/**
		* �x�N�g�� a �� �x�N�g�� b �̊Ԃ���`��Ԃ���
		*
		* @param a ��Ԃ̊J�n�x�N�g��
		* @param b ��Ԃ̏I���x�N�g��
		* @param t ��ԃp�����[�^ (0.0 ~ 1.0 �͈̔�)
		*
		* @return ��Ԃ��ꂽ�x�N�g��
		*/
		static Vector3 Lerp(const Vector3& a, const Vector3& b, float t);

	public:

		float x, y, z;


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
