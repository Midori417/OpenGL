/**
* @file Vector2.cpp
*/
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Mathf.h"

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	const Vector2 Vector2::zero = Vector2(0, 0);
	const Vector2 Vector2::one = Vector2(1, 1);

	/**
	* 2��float����Vector2���쐬����R���X�g���N�^
	*
	* @param x X����
	* @param y Y����
	*/
	Vector2::Vector2(float x, float y)
		: x(x), y(y)
	{
	}

	/**
	* 1��float����Vector2���쐬����R���X�g���N�^
	*
	* @param v XY�̐���
	*/
	Vector2::Vector2(float v)
		: x(v), y(v)
	{
	}

	/**
	* Vector3����Vector2���\�z����R���X�g���N�^
	*
	* @param v Vector3��XY����
	*/
	Vector2::Vector2(const Vector3& v)
		: x(v.x), y(v.y)
	{
	}

	/**
	* Vector4����Vector2���\�z����R���X�g���N�^
	*
	* @param v Vector4��XY����
	*/
	Vector2::Vector2(const Vector4& v)
		: x(v.x), y(v.y)
	{
	}

	/**
	* �x�N�g���̐��K�����v�Z����
	*/
	Vector2 Vector2::Normalize(const Vector2& v)
	{
		float num = Mathf::Sqrt(Dot(v, v));
		if (num > 0.0f)
		{
			return v / Vector2(num);
		}
		else
		{
			return Vector2::zero;
		}
	}

	/**
	* �x�N�g���̓��ς��v�Z����
	*
	* @return a��b�̓���
	*/
	float Vector2::Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/**
	* 2�̃x�N�g���̋������v�Z����
	*
	* return a��b�̋���
	*/
	float Vector2::Distance(const Vector2& a, const Vector2& b)
	{
		Vector2 tmp = a - b;
		return Mathf::Sqrt(tmp.x * tmp.x + tmp.y * tmp.y);
	}

	/**
	* 2�̃x�N�g���̊Ԃ���`��Ԃ���
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

	/**
	* Vector2���m�̉��Z
	*/
	Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	/**
	* Vector2���m�̌��Z
	*/
	Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	/**
	* Vector2���m�̏�Z
	*/
	Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	/**
	* Vector2���m�̏��Z
	*/
	Vector2 operator/(const Vector2& a, const Vector2& b)
	{
		// 0���Z�����Ȃ��悤��
		if (b.x == 0 || b.y == 0)
		{
			return Vector2::zero;
		}

		return Vector2(a.x / b.x, a.y / b.y);
	}

	/**
	* Vector2��float�̏�Z
	*/
	Vector2 operator*(const Vector2& v, float f)
	{
		return v * Vector2(f);
	}

	/**
	* Vector2��float�̏��Z
	*/
	Vector2 operator/(const Vector2& v, float f)
	{
		return v / Vector2(f);
	}

	/**
	* Vector2���m�̑�����Z
	*/
	Vector2 operator+=(Vector2& a, const Vector2& b)
	{
		a = a + b;
		return a;
	}

	/**
	* Vector2���m�̑�����Z
	*/
	Vector2 operator-=(Vector2& a, const Vector2& b)
	{
		a = a - b;
		return a;
	}

	/**
	* Vector2���m�̑����Z
	*/
	Vector2 operator*=(Vector2& a, const Vector2& b)
	{
		a = a * b;
		return a;
	}

	/**
	* Vector2���m�̑�����Z
	*/
	Vector2 operator/=(Vector2& a, const Vector2& b)
	{
		a = a / b;
		return a;
	}

	/**
	* Vector2��float�̑����Z
	*/
	Vector2 operator*=(Vector2& v, float f)
	{
		v = v * f;
		return v;
	}

	/**
	* Vector2��float�̑�����Z
	*/
	Vector2 operator/=(Vector2& v, float f)
	{
		v = v / f;
		return v;
	}

	/**
	* Vector2���m�̔�r���Z
	*/
	bool operator==(const Vector2& a, const Vector2& b)
	{
		return ((a.x == b.x) && (a.y == b.y));
	}

	/**
	* Vector2���m�̔�r���Z
	*/
	bool operator!=(const Vector2& a, const Vector2& b)
	{
		return ((a.x != b.x) || (a.y != b.y));
	}
}