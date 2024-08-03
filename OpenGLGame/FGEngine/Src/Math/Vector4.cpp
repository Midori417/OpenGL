/**
* @file Vector4.cpp
*/
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Vector2.h"
#include "FGEngine/Math/Vector3.h"

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
	const Vector4 Vector4::one = Vector4(1, 1, 1, 1);

	/**
	* 4��float����Vector4���쐬����R���X�g���N�^
	*
	* @param x X����
	* @param y Y����
	* @param z Z����
	* @param w W����
	*/
	Vector4::Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	/**
	* 1��float����Vector4���쐬����R���X�g���N�^
	*
	* @param v XYZW����
	*/
	Vector4::Vector4(float v)
		: x(v), y(v), z(v), w(v)
	{
	}

	/**
	* Vector2��2��float����Vector4���\�z����R���X�g���N�^
	*
	* @param v Vector2��XY����
	* @param z Z����
	* @param w W����
	*/
	Vector4::Vector4(const Vector2& v, float z, float w)
		: x(v.x), y(v.y), z(z), w(w)
	{
	}

	/**
	* Vector3��1��float����Vector4���\�z����R���X�g���N�^
	*
	* @param v Vector3��XYZ����
	* @param w W����
	*/
	Vector4::Vector4(const Vector3& v, float w)
		: x(v.x), y(v.y), z(v.z), w(w)
	{
	}

	/**
	* �P�����Z�q
	*/
	Vector4 operator-(const Vector4& v)
	{
		return Vector4(-v.x, -v.y, -v.z, -v.w);
	}

	/**
	* Vector4���m�̉��Z
	*/
	Vector4 operator+(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	/**
	* Vector4���m�̌��Z
	*/
	Vector4 operator-(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	/**
	* Vector4���m�̏�Z
	*/
	Vector4 operator*(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	/**
	* Vector4���m�̏��Z
	*/
	Vector4 operator/(const Vector4& a, const Vector4& b)
	{
		// 0���Z�����Ȃ��悤��
		if (b.x == 0 || b.y == 0 || b.z == 0 || b.w == 0)
		{
			return Vector4::zero;
		}

		return Vector4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	/**
	* Vector4���m�̑�����Z
	*/
	Vector4 operator+=(Vector4& a, const Vector4& b)
	{
		a = a + b;
		return a;
	}

	/**
	* Vector4���m�̑�����Z
	*/
	Vector4 operator-=(Vector4& a, const Vector4& b)
	{
		a = a - b;
		return a;
	}

	/**
	* Vector4���m�̑����Z
	*/
	Vector4 operator*=(Vector4& a, const Vector4& b)
	{
		a = a * b;
		return a;
	}

	/**
	* Vector4���m�̑�����Z
	*/
	Vector4 operator/=(Vector4& a, const Vector4& b)
	{
		a = a / b;
		return a;
	}

	/**
	* Vector4���m�̔�r���Z
	*/
	bool operator==(const Vector4& a, const Vector4& b)
	{
		return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
	}

	/**
	* Vector4���m�̔�r���Z
	*/
	bool operator!=(const Vector4& a, const Vector4& b)
	{
		return ((a.x != b.x) || (a.y != b.y) || (a.z != b.z) || (a.w != b.w));
	}
}