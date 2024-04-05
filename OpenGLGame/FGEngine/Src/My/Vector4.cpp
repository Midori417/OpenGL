/**
* @file Vector4.cpp
*/
#include "Vector4.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Mathf.h"

namespace FGEngine
{

	// �X�^�e�B�b�N�ϐ��̏�����
	const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
	const Vector4 Vector4::one = Vector4(1, 1, 1, 1);

	/**
	* 4��float����Vector4���\�z����R���X�g���N�^
	*/
	Vector4::Vector4(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	/**
	* Vector2��2��float����Vector4���\�z����R���X�g���N�^
	*/
	Vector4::Vector4(const Vector2& v, float z, float w)
		: x(v.x), y(v.y), z(z), w(w)
	{
	}

	/**
	* Vector3�ƂP��float����Vector3���\�z����R���X�g���N�^
	*/
	Vector4::Vector4(const Vector3& v, float w)
		: x(v.x), y(v.y), z(v.z), w(w)
	{
	}

	/**
	* �x�N�g���𐳋K�����ꂽ�x�N�g��(�P�ʃx�N�g��)�ɂ���
	*/
	void Vector4::Normalize()
	{
		float num = Magnitude();
		if (num > 0.0f) {
			*this /= num;
		}
		else
		{
			*this = Vector4::zero;
		}
	}

	/**
	* ���K�����ꂽ�x�N�g��(�P�ʃx�N�g��)���擾
	*
	* @return ���K�����ꂽ�x�N�g��
	*/
	Vector4 Vector4::Normalized() const
	{
		Vector4 result = Vector4(x, y, z, w);
		result.Normalize();
		return result;
	}

	/**
	* �x�N�g���̑傫��(����)���v�Z����
	*
	* @return �x�N�g���̑傫��
	*/
	float Vector4::Magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y + z * z + w * w);
	}


	//=======================================
	//
	//  Operator
	//
	//=======================================

	/**
	* -�P�����Z�q
	*/
	Vector4 operator-(const Vector4& a)
	{
		return Vector4(-a.x, -a.y, -a.z, -a.w);
	}

	//=======================================
	//  ���Z
	//=======================================

	/**
	* Vector4���m�̑�����Z
	*/
	Vector4& operator+=(Vector4& a, const Vector4& b)
	{
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
		a.w += b.w;
		return a;
	}

	/**
	* Vector4���m�̉��Z
	*/
	Vector4 operator+(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}

	/**
	* Vector4��float�̑�����Z
	*/
	Vector4& operator+=(Vector4& a, float b)
	{
		return a += Vector4(b, b, b, b);
	}

	/**
	* Vector4��float�̉��Z
	*/
	Vector4 operator+(const Vector4& a, float b)
	{
		return a + Vector4(b, b, b, b);
	}

	/**
	* float��Vector4�̉��Z
	*/
	Vector4 operator+(float a, const Vector4& b)
	{
		return b + a;
	}

	//=======================================
	//  ���Z
	//=======================================

	/**
	* Vector4���m�̑�����Z
	*/
	Vector4& operator-=(Vector4& a, const Vector4& b)
	{
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
		a.w -= b.w;
		return a;
	}

	/**
	* Vector4���m�̉��Z
	*/
	Vector4 operator-(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}

	/**
	* Vector4��float�̑�����Z
	*/
	Vector4& operator-=(Vector4& a, float b)
	{
		return a -= Vector4(b, b, b, b);
	}

	/**
	* Vector4��float�̉��Z
	*/
	Vector4 operator-(const Vector4& a, float b)
	{
		return a - Vector4(b, b, b, b);
	}

	/**
	* float��Vector4�̉��Z
	*/
	Vector4 operator-(float a, const Vector4& b)
	{
		return b - a;
	}

	//=======================================
	//  ��Z
	//=======================================

	/**
	* Vector4���m�̑�����Z
	*/
	Vector4& operator*=(Vector4& a, const Vector4& b)
	{
		a.x *= b.x;
		a.y *= b.y;
		a.z *= b.z;
		a.w *= b.w;
		return a;
	}

	/**
	* Vector4���m�̉��Z
	*/
	Vector4 operator*(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}

	/**
	* Vector4��float�̑�����Z
	*/
	Vector4& operator*=(Vector4& a, float b)
	{
		return a *= Vector4(b, b, b, b);
	}

	/**
	* Vector4��float�̉��Z
	*/
	Vector4 operator*(const Vector4& a, float b)
	{
		return a * Vector4(b, b, b, b);
	}

	/**
	* float��Vector4�̉��Z
	*/
	Vector4 operator*(float a, const Vector4& b)
	{
		return b * a;
	}

	//=======================================
	//	���Z
	//=======================================

	/**
	*�@Vector4���m�̑�����Z
	*/
	Vector4& operator/=(Vector4& a, const Vector4& b)
	{
		a.x /= b.x;
		a.y /= b.y;
		a.z /= b.z;
		a.w /= b.w;
		return a;
	}

	/**
	* Vector4���m�̉��Z
	*/
	Vector4 operator/(const Vector4& a, const Vector4& b)
	{
		return Vector4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}

	/**
	* Vector4��float�̑�����Z
	*/
	Vector4& operator/=(Vector4& a, float b)
	{
		return a /= Vector4(b, b, b, b);
	}

	/**
	* Vector4��float�̉��Z
	*/
	Vector4 operator/(const Vector4& a, float b)
	{
		return a / Vector4(b, b, b, b);
	}

	Vector4 operator/(float a, const Vector4& b)
	{
		return b / a;
	}

	//=======================================
	//	��r
	//=======================================

	bool operator==(const Vector4& a, const Vector4& b)
	{
		return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w));
	}

	bool operator!=(const Vector4& a, const Vector4& b)
	{
		return !(a == b);
	}

}