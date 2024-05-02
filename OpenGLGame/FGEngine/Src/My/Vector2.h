/**
* @file Vector2.h
*/
#ifndef FGENGINE_VECTOR2_H_INCLUDED
#define FGENGINE_VECTOR2_H_INCLUDED
#include "VectorFrd.h"

namespace FGEngine
{

	/**
	* �񎟌��x�N�g��
	*/
	struct Vector2
	{
		// �f�t�H���g�R���X�g���N�^
		Vector2() = default;

		// 2��float����Vector2���\�z����R���X�g���N�^
		explicit Vector2(float x, float y);

		// Vector3����Vector2���\�z����R���X�g���N�^
		explicit Vector2(const Vector3& v);

		// Vector4����Vector2���\�z����R���X�g���N�^
		explicit Vector2(const Vector4& v);

		/**
		* �x�N�g���𐳋K�����ꂽ�x�N�g��(�P�ʃx�N�g��)�ɂ���
		*/
		void Normalize();

		/**
		* ���K�����ꂽ�x�N�g��(�P�ʃx�N�g��)���擾
		*
		* @return ���K�����ꂽ�x�N�g��
		*/
		Vector2 Normalized() const;

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
		static float Dot(const Vector2& a, const Vector2& b);

		/**
		*  2�̃x�N�g���̋���(����)���v�Z����
		*
		* @param a �x�N�g��1
		* @param b �x�N�g��2
		*
		* @return a��b�̋���
		*/
		static float Distance(const Vector2& a, const Vector2& b);

		/**
		* �x�N�g�� a �� �x�N�g�� b �̊Ԃ���`��Ԃ���
		*
		* @param a ��Ԃ̊J�n�x�N�g��
		* @param b ��Ԃ̏I���x�N�g��
		* @param t ��ԃp�����[�^ (0.0 ~ 1.0 �͈̔�)
		*
		* @return ��Ԃ��ꂽ�x�N�g��
		*/
		static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);


	public:

		// �x�N�g����X����
		float x;

		// �x�N�g����Y����
		float y;

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
