/**
* @file Vector2.cpp
*/
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mathf.h"

namespace FGEngine
{
	// �X�^�e�B�b�N�ϐ��̏�����
	const Vector2 Vector2::zero = Vector2(0, 0);
	const Vector2 Vector2::one = Vector2(1, 1);
	const Vector2 Vector2::up = Vector2(0, 1);
	const Vector2 Vector2::down = Vector2(0, -1);
	const Vector2 Vector2::left = Vector2(-1, 0);
	const Vector2 Vector2::right = Vector2(1, 0);

	/**
	* 2��float����Vector2���\�z����R���X�g���N�^
	* 
	* @param x X����
	* @param y Y����
	*/
	Vector2::Vector2(float x, float y)
		: x(x), y(y)
	{
	}

	/**
	* Vector3����Vector2���\�z����R���X�g���N�^
	*/
	Vector2::Vector2(const Vector3& v)
		:x(v.x), y(v.y)
	{

	}

	/**
	* Vector4����Vector2���\�z����R���X�g���N�^
	*/
	Vector2::Vector2(const Vector4& v)
		:x(v.x), y(v.y)
	{

	}

	/**
	* �x�N�g���𐳋K�����ꂽ�x�N�g��(�P�ʃx�N�g��)�ɂ���
	*/
	void Vector2::Normalize()
	{
		float num = Magnitude();
		if (num > 0.0f) {
			*this /= num;
		}
		else
		{
			*this = Vector2::zero;
		}
	}

	/**
	* ���K�����ꂽ�x�N�g��(�P�ʃx�N�g��)���擾
	*
	* @return ���K�����ꂽ�x�N�g��
	*/
	Vector2 Vector2::Normalized() const
	{
		Vector2 result = Vector2(x, y);
		result.Normalize();
		return result;
	}

	/**
	* �x�N�g���̑傫��(����)���v�Z����
	*
	* @return �x�N�g���̑傫��
	*/
	float Vector2::Magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y);
	}

	/**
	* 2�̃x�N�g���̓���(�h�b�g��)���v�Z����
	*
	* @param a �x�N�g��1
	* @param b �x�N�g��2
	* 
	* @return a��b�̓���
	*/
	float Vector2::Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/**
	*  2�̃x�N�g���̋���(����)���v�Z����
	*
	* @param a �x�N�g��1
	* @param b �x�N�g��2
	* 
	* @return a��b�̋���	
	*/
	float Vector2::Distance(const Vector2& a, const Vector2& b)
	{
		float num = a.x - b.x;
		float num2 = a.y - b.y;
		return Mathf::Sqrt(num * num + num2 * num2);
	}

	/**
	* �x�N�g�� a �� �x�N�g�� b �̊Ԃ���`��Ԃ���
	* 
	* @param a ��Ԃ̊J�n�x�N�g��
	* @param b ��Ԃ̏I���x�N�g��
	* @param t ��ԃp�����[�^ (0.0 ~ 1.0 �͈̔�)
	* 
	* @return ��Ԃ��ꂽ�x�N�g��	
	*/
	Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
	}

	//=======================================
	//
	//  Operator
	//
	//=======================================

	/**
	* -�P�����Z�q
	*/
	Vector2 operator-(const Vector2& a)
	{
		return Vector2(-a.x, -a.y);
	}

	//=======================================
	//  ���Z
	//=======================================

	/**
	* Vector2���m�̑�����Z
	*/
	Vector2& operator+=(Vector2& a, const Vector2& b)
	{
		a.x += b.x;
		a.y += b.y;
		return a;
	}

	/**
	* Vector2���m�̉��Z
	*/
	Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	/**
	* Vector2��float�̑�����Z
	*/
	Vector2& operator+=(Vector2& a, float b)
	{
		return a += Vector2(b, b);
	}

	/**
	* Vector2��float�̉��Z
	*/
	Vector2 operator+(const Vector2& a, float b)
	{
		return a + Vector2(b, b);
	}

	/**
	* float��Vector2�̉��Z
	*/
	Vector2 operator+(float a, const Vector2& b)
	{
		return b + a;
	}

	//=======================================
	//  ���Z
	//=======================================

	/**
	* Vector2���m�̑�����Z
	*/
	Vector2& operator-=(Vector2& a, const Vector2& b)
	{
		a.x -= b.x;
		a.y -= b.y;
		return a;
	}

	/**
	* Vector2���m�̉��Z
	*/
	Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	/**
	* Vector2��float�̑�����Z
	*/
	Vector2& operator-=(Vector2& a, float b)
	{
		return a -= Vector2(b, b);
	}

	/**
	* Vector2��float�̉��Z
	*/
	Vector2 operator-(const Vector2& a, float b)
	{
		return a - Vector2(b, b);
	}

	/**
	* float��Vector2�̉��Z
	*/
	Vector2 operator-(float a, const Vector2& b)
	{
		return b - a;
	}

	//=======================================
	//  ��Z
	//=======================================

	/**
	* Vector2���m�̑�����Z
	*/
	Vector2& operator*=(Vector2& a, const Vector2& b)
	{
		a.x *= b.x;
		a.y *= b.y;
		return a;
	}

	/**
	* Vector2���m�̉��Z
	*/
	Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	/**
	* Vector2��float�̑�����Z
	*/
	Vector2& operator*=(Vector2& a, float b)
	{
		return a *= Vector2(b, b);
	}

	/**
	* Vector2��float�̉��Z
	*/
	Vector2 operator*(const Vector2& a, float b)
	{
		return a * Vector2(b, b);
	}

	/**
	* float��Vector2�̉��Z
	*/
	Vector2 operator*(float a, const Vector2& b)
	{
		return b * a;
	}

	//=======================================
	//	���Z
	//=======================================

	/**
	*�@Vector2���m�̑�����Z
	*/
	Vector2& operator/=(Vector2& a, const Vector2& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0) {
		}
		a.x /= b.x;
		a.y /= b.y;
		return a;
	}

	/**
	* Vector2���m�̉��Z
	*/
	Vector2 operator/(const Vector2& a, const Vector2& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0) {
		}
		return Vector2(a.x / b.x, a.y / b.y);
	}

	/**
	* Vector2��float�̑�����Z
	*/
	Vector2& operator/=(Vector2& a, float b)
	{
		if (a.x == 0 || a.y == 0 || b == 0) {
		}
		return a /= Vector2(b, b);
	}

	Vector2 operator/(const Vector2& a, float b)
	{
		if (a.x == 0 || a.y == 0 || b == 0) {
		}
		return a / Vector2(b, b);
	}

	Vector2 operator/(float a, const Vector2& b)
	{
		if (b.x == 0 || b.y == 0 || a == 0) {
		}
		return b / a;
	}

	//=======================================
	//	��r
	//=======================================

	bool operator==(const Vector2& a, const Vector2& b)
	{
		return ((a.x == b.x) && (a.y == b.y));
	}

	bool operator!=(const Vector2& a, const Vector2& b)
	{
		return ((a.x != b.x) || (a.y != b.y));
	}
}