/**
* @file Vector4.cpp
*/
#include "Vector4.h"
#include "Mathf.h"

// �X�^�e�B�b�N�ϐ��̏�����
const Vector4 Vector4::zero = Vector4(0, 0, 0, 0);
const Vector4 Vector4::one = Vector4(1, 1, 1, 1);

//=======================================
//
//  �֐�
//
//=======================================

/**
* ���g�̃x�N�g���𐳋K������
*/
void Vector4::Normalize()
{
	float num = magnitude();
	if (num > 0.0f) {
		*this /= num;
	}
	else
	{
		*this = Vector4::zero;
	}
}


/**
* a��b�̊e�v�f�̍ő�l�̃x�N�g����Ԃ�
*
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
*
* @return �e�v�f�̍ő�̃x�N�g��
*/
Vector4 Vector4::Max(const Vector4& a, const Vector4& b)
{
	return Vector4(Mathf::Max(a.x, b.x), Mathf::Max(a.y, b.y), Mathf::Max(a.z, b.z), Mathf::Max(a.w, b.w));
}

/**
* a��b�̊e�v�f�̍ŏ��l�̃x�N�g����Ԃ�
*
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
*
* @return �e�v�f�̍ŏ��̃x�N�g��
*/
Vector4 Vector4::Min(const Vector4& a, const Vector4& b)
{
	return Vector4(Mathf::Min(a.x, b.x), Mathf::Min(a.y, b.y), Mathf::Min(a.z, b.z), Mathf::Min(a.w, b.w));
}

/**
* �x�N�g���̒�����Ԃ�
*
* @return�x�N�g���̒���
*/
float Vector4::magnitude() const
{
	return Mathf::Sqrt(x * x + y * y + z * z + w * w);
}

/**
* �x�N�g���̒������悵�ĕԂ�
*
* @return �x�N�g���̓�悵������
*/
float Vector4::sqrtMagnitude() const
{
	return x * x + y * y + z * z + w * w;
}

/**
* �x�N�g���𐳋K�����ĕԂ�
*
* @return ���K�������x�N�g��
* @return zero 0���Z���ꂽ
*/
Vector4 Vector4::normalized() const
{
	Vector4 result = Vector4(x, y, z, w);
	result.Normalize();
	return result;
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

