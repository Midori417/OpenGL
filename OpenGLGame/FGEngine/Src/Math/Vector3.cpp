/**
* @file Vector3.cpp
*/
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Mathf.h"

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	const Vector3 Vector3::zero = Vector3(0, 0, 0);
	const Vector3 Vector3::one = Vector3(1, 1, 1);
	const Vector3 Vector3::up = Vector3(0, 1, 0);
	const Vector3 Vector3::down = Vector3(0, -1, 0);
	const Vector3 Vector3::left = Vector3(-1, 0, 0);
	const Vector3 Vector3::right = Vector3(1, 0, 0);
	const Vector3 Vector3::forward = Vector3(0, 0, 1);
	const Vector3 Vector3::back = Vector3(0, 0, -1);

	/**
	* 3��float����Vector3���쐬����R���X�g���N�^
	*
	* @param x X����
	* @param y Y����
	* @param z Z����
	*/
	Vector3::Vector3(float x, float y, float z)
		: x(x), y(y), z(z)
	{
	}

	/**
	* 1��float����Vector3���쐬����R���X�g���N�^
	*
	* @param v XYZ����
	*/
	Vector3::Vector3(float v)
		: x(v), y(v), z(v)
	{
	}

	/**
	* Vector2��1��float����Vector3���\�z����R���X�g���N�^
	*
	* @param v Vector2��XY����
	* @param z Z����
	*/
	Vector3::Vector3(const Vector2& v, float z)
		: x(v.x), y(v.y), z(z)
	{
	}

	/**
	* Vector4����Vector3���\�z����R���X�g���N�^
	*
	* @parma v	Vector4��XYZ����
	*/
	Vector3::Vector3(const Vector4& v)
		: x(v.x), y(v.y), z(v.z)
	{
	}

	/**
	* �x�N�g���̐��K�����v�Z����
	*/
	Vector3 Vector3::Normalize(const Vector3& v)
	{
		float num = Mathf::Sqrt(Dot(v, v));
		if (num > 0.0f)
		{
			return v / Vector3(num);
		}
		else
		{
			return Vector3::zero;
		}
	}

	/**
	* �x�N�g���̑傫�����v�Z����
	*/
	float Vector3::Magnitude(const Vector3& v)
	{
		return Mathf::Sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}


	/**
	* �x�N�g���̓��ς��v�Z����
	*
	* @return a��b�̓���
	*/
	float Vector3::Dot(const Vector3& a, const Vector3& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	/**
	* 2�̃x�N�g���̊O��(�N���X��)���v�Z����
	*
	* @return a��b�̊O��
	*/
	Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
	{
		float num = a.y * b.z - a.z * b.y;
		float num2 = a.z * b.x - a.x * b.z;
		float num3 = a.x * b.y - a.y * b.x;
		return Vector3(num, num2, num3);
	}

	/**
	* 2�̃x�N�g���̋������v�Z����
	*
	* return a��b�̋���
	*/
	float Vector3::Distance(const Vector3& a, const Vector3& b)
	{
		Vector3 tmp = a - b;
		return Mathf::Sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
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
	Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
	}

	/**
	* �P�����Z�q
	*/
	Vector3 operator-(const Vector3& v)
	{
		return Vector3(-v.x, -v.y, -v.z);
	}

	/**
	* Vector3���m�̉��Z
	*/
	Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/**
	* Vector3���m�̌��Z
	*/
	Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/**
	* Vector3���m�̏�Z
	*/
	Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	/**
	* Vector3���m�̏��Z
	*/
	Vector3 operator/(const Vector3& a, const Vector3& b)
	{
		// 0���Z�����Ȃ��悤��
		if (b.x == 0 || b.y == 0 || b.z == 0)
		{
			return Vector3::zero;
		}

		return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	/**
	* Vector3��float�̏�Z
	*/
	Vector3 operator*(const Vector3& v, float f)
	{
		return v * Vector3(f);
	}

	/**
	* Vector3��float�̏��Z
	*/
	Vector3 operator/(const Vector3& v, float f)
	{
		return v / Vector3(f);
	}

	/**
	* Vector3���m�̑�����Z
	*/
	Vector3 operator+=(Vector3& a, const Vector3& b)
	{
		a = a + b;
		return a;
	}

	/**
	* Vector3���m�̑�����Z
	*/
	Vector3 operator-=(Vector3& a, const Vector3& b)
	{
		a = a - b;
		return a;
	}

	/**
	* Vector3���m�̑����Z
	*/
	Vector3 operator*=(Vector3& a, const Vector3& b)
	{
		a = a * b;
		return a;
	}

	/**
	* Vector3���m�̑�����Z
	*/
	Vector3 operator/=(Vector3& a, const Vector3& b)
	{
		a = a / b;
		return a;
	}

	/**
	* Vector3��float�̑����Z
	*/
	Vector3 operator*=(Vector3& v, float f)
	{
		v = v * f;
		return v;
	}

	/**
	* Vector3��float�̑����Z
	*/
	Vector3 operator/=(Vector3& v, float f)
	{
		v = v / f;
		return v;
	}

	/**
	* Vector3���m�̔�r���Z
	*/
	bool operator==(const Vector3& a, const Vector3& b)
	{
		return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
	}

	/**
	* Vector3���m�̔�r���Z
	*/
	bool operator!=(const Vector3& a, const Vector3& b)
	{
		return ((a.x != b.x) || (a.y != b.y) || (a.z != b.z));
	}
}