/**
* @file Vector3.cpp
*/
#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Mathf.h"

namespace FGEngine
{

	// �X�^�e�B�b�N�ϐ��̏�����
	const Vector3 Vector3::zero = Vector3(0, 0, 0);
	const Vector3 Vector3::one = Vector3(1, 1, 1);
	const Vector3 Vector3::up = Vector3(0, 1, 0);
	const Vector3 Vector3::down = Vector3(0, -1, 0);
	const Vector3 Vector3::left = Vector3(-1, 0, 0);
	const Vector3 Vector3::right = Vector3(1, 0, 0);
	const Vector3 Vector3::forward = Vector3(0, 0, 1);
	const Vector3 Vector3::back = Vector3(0, 0, -1);

	/**
	* 3��float����Vector3���\�z����R���X�g���N�^
	*/
	Vector3::Vector3(float x, float y, float z)
		:x(x), y(y),z (z)
	{
	}

	/**
	* Vector2����Vector3���\�z����R���X�g���N�^
	*/
	Vector3::Vector3(const Vector2& v, float z)
		: x(v.x), y(v.y),z(z)
	{
	}

	/**
	* Vector4����Vector3���\�z����R���X�g���N�^
	*/
	Vector3::Vector3(const Vector4& v)
		: x(v.x), y(v.y), z(v.z)
	{
	}

	/**
	* �x�N�g���𐳋K�����ꂽ�x�N�g��(�P�ʃx�N�g��)�ɂ���
	*/
	void Vector3::Normalize()
	{
		float num = Magnitude();
		if (num > 0.0f) {
			*this /= num;
		}
		else
		{
			*this = Vector3::zero;
		}
	}

	/**
	* ���K�����ꂽ�x�N�g��(�P�ʃx�N�g��)���擾
	*
	* @return ���K�����ꂽ�x�N�g��
	*/
	Vector3 Vector3::Normalized() const
	{
		Vector3 result = Vector3(x, y, z);
		result.Normalize();
		return result;
	}

	/**
	* �x�N�g���̑傫��(����)���v�Z����
	*
	* @return �x�N�g���̑傫��
	*/
	float Vector3::Magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y + z * z);
	}

	/**
	* 2�̃x�N�g���̓���(�h�b�g��)���v�Z����
	*
	* @param a �x�N�g��1
	* @param b �x�N�g��2
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
	* @param a �x�N�g��1
	* @param b �x�N�g��2
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
	*  2�̃x�N�g���̋���(����)���v�Z����
	*
	* @param a �x�N�g��1
	* @param b �x�N�g��2
	*
	* @return a��b�̋���
	*/
	float Vector3::Distance(const Vector3& a, const Vector3& b)
	{
		Vector3 tmp = a - b;
		return Mathf::Sqrt(tmp.x * tmp.x + tmp.y * tmp.y + tmp.z * tmp.z);
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
	Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
	{
		// �l��⊮����
		t = Mathf::Clamp01(t);

		return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
	}


	/**
	* -�P�����Z�q
	*/
	Vector3 operator-(const Vector3& a)
	{
		return Vector3(-a.x, -a.y, -a.z);
	}

	//=======================================
	//  ���Z
	//=======================================

	/**
	* Vector3���m�̑�����Z
	*/
	Vector3& operator+=(Vector3& a, const Vector3& b)
	{
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
		return a;
	}

	/**
	* Vector3���m�̉��Z
	*/
	Vector3 operator+(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
	}

	/**
	* Vector3��float�̑�����Z
	*/
	Vector3& operator+=(Vector3& a, float b)
	{
		return a += Vector3(b, b, b);
	}

	/**
	* Vector3��float�̉��Z
	*/
	Vector3 operator+(const Vector3& a, float b)
	{
		return a + Vector3(b, b, b);
	}

	/**
	* float��Vector3�̉��Z
	*/
	Vector3 operator+(float a, const Vector3& b)
	{
		return b + a;
	}

	//=======================================
	//  ���Z
	//=======================================

	/**
	* Vector3���m�̑�����Z
	*/
	Vector3& operator-=(Vector3& a, const Vector3& b)
	{
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
		return a;
	}

	/**
	* Vector3���m�̉��Z
	*/
	Vector3 operator-(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
	}

	/**
	* Vector3��float�̑�����Z
	*/
	Vector3& operator-=(Vector3& a, float b)
	{
		return a -= Vector3(b, b, b);
	}

	/**
	* Vector3��float�̉��Z
	*/
	Vector3 operator-(const Vector3& a, float b)
	{
		return a - Vector3(b, b, b);
	}

	/**
	* float��Vector3�̉��Z
	*/
	Vector3 operator-(float a, const Vector3& b)
	{
		return b - a;
	}

	//=======================================
	//  ��Z
	//=======================================

	/**
	* Vector3���m�̑�����Z
	*/
	Vector3& operator*=(Vector3& a, const Vector3& b)
	{
		a.x *= b.x;
		a.y *= b.y;
		a.z *= b.z;
		return a;
	}

	/**
	* Vector3���m�̉��Z
	*/
	Vector3 operator*(const Vector3& a, const Vector3& b)
	{
		return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
	}

	/**
	* Vector3��float�̑�����Z
	*/
	Vector3& operator*=(Vector3& a, float b)
	{
		return a *= Vector3(b, b, b);
	}

	/**
	* Vector3��float�̉��Z
	*/
	Vector3 operator*(const Vector3& a, float b)
	{
		return a * Vector3(b, b, b);
	}

	/**
	* float��Vector3�̉��Z
	*/
	Vector3 operator*(float a, const Vector3& b)
	{
		return b * a;
	}

	//=======================================
	//	���Z
	//=======================================

	/**
	*�@Vector3���m�̑�����Z
	*/
	Vector3& operator/=(Vector3& a, const Vector3& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0 || a.z == 0 || b.z == 0) {
		}
		a.x /= b.x;
		a.y /= b.y;
		a.z /= b.z;
		return a;
	}

	/**
	* Vector3���m�̉��Z
	*/
	Vector3 operator/(const Vector3& a, const Vector3& b)
	{
		if (a.x == 0 || b.x == 0 || a.y == 0 || b.y == 0 || a.z == 0 || b.z == 0) {
		}
		return Vector3(a.x / b.x, a.y / b.y, a.z / b.z);
	}

	/**
	* Vector3��float�̑�����Z
	*/
	Vector3& operator/=(Vector3& a, float b)
	{
		if (a.x == 0 || a.y == 0 || a.z == 0 || b == 0) {
		}
		return a /= Vector3(b, b, b);
	}

	/**
	* Vector3��float�̉��Z
	*/
	Vector3 operator/(const Vector3& a, float b)
	{
		if (a.x == 0 || a.y == 0 || b == 0) {
		}
		return a / Vector3(b, b, b);
	}

	Vector3 operator/(float a, const Vector3& b)
	{
		if (b.x == 0 || b.y == 0 || b.z == 0 || a == 0) {
		}
		return b / a;
	}

	//=======================================
	//	��r
	//=======================================

	bool operator==(const Vector3& a, const Vector3& b)
	{
		return ((a.x == b.x) && (a.y == b.y) && (a.z == b.z));
	}

	bool operator!=(const Vector3& a, const Vector3& b)
	{
		return !(a == b);
	}
}