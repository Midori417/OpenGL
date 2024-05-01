/**
* @file Vector3.cpp
*/
#include "Vector3.h"
#include "Mathf.h"

// �X�^�e�B�b�N�ϐ��̏�����
const Vector3 Vector3::zero = Vector3(0, 0, 0);
const Vector3 Vector3::one = Vector3(1, 1, 1);
const Vector3 Vector3::up = Vector3(0, 1, 0);
const Vector3 Vector3::down = Vector3(0, -1, 0);
const Vector3 Vector3::left = Vector3(-1, 0, 0);
const Vector3 Vector3::right = Vector3(1, 0, 0);
const Vector3 Vector3::forward = Vector3(0, 0, -1);
const Vector3 Vector3::back = Vector3(0, 0, 1);



//=======================================
//
//  �֐�
//
//=======================================

/**
* ���g�̃x�N�g���𐳋K������
*/
void Vector3::Normalize()
{
	float num = magnitude();
	if (num > 0.0f) {
		*this /= num;
	}
	else
	{
		*this = Vector3::zero;
	}
}

/**
* �e�v�f��v�̊e�v�f�Ə�Z����
* 
* @param v ��Z����v�f
*/
void Vector3::Scale(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
}


/**
* a��b�̃x�N�g���̓��ς�Ԃ�
* 
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
* 
* @return a��b�̓���
*/
float Vector3::Dot(const Vector3& a, const Vector3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

/**
* a��b�̃x�N�g���̊O�ς�Ԃ�
*
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
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
* a��b�̃x�N�g���̒�����Ԃ�
* 
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
*
* @return a��b�̒���
*/
float Vector3::Distance(const Vector3& a, const Vector3& b)
{
	float num = a.x - b.x;
	float num2 = a.y - b.y;
	float num3 = a.z - b.z;
	return Mathf::Sqrt(num * num + num2 * num2 + num3 * num3);
}

/**
* a��b�̊Ԃ�t(Clamp0�`1)�Ő��`��Ԃ���
* 
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
* @param t 
*/
Vector3 Vector3::Lerp(const Vector3& a, const Vector3& b, float t)
{
	t = Mathf::Clamp01(t);
	return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
}

/**
* a��b�̊Ԃ�t�Ő��`��Ԃ���
*
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
* @param t
*/
Vector3 Vector3::LerpUnclamped(const Vector3& a, const Vector3& b, float t)
{
	return Vector3(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t, a.z + (b.z - a.z) * t);
}

/**
* ���݂̈ʒucurrent����target�Ɍ����Ĉړ�����
*
* @param current	���݈ʒu
* @param target		�^�[�Q�b�g�ʒu
*
*/
Vector3 Vector3::MoveTowards(const Vector3& current, const Vector3& target, float maxDistanceDelta)
{
	float num = target.x - current.x;
	float num2 = target.y - current.y;
	float num3 = target.z - current.z;
	float num4 = num * num + num2 * num2 + num3 * num3;
	if (num4 == 0.0f || (maxDistanceDelta >= 0.0f && num4 <= maxDistanceDelta * maxDistanceDelta))
	{
		return target;
	}

	float num5 = Mathf::Sqrt(num4);
	return Vector3(
		current.x + num / num5 * maxDistanceDelta,
		current.y + num2 / num5 * maxDistanceDelta,
		current.z + num3 / num5 * maxDistanceDelta);
}

/**
* a��b�̊e��������Z���ĕԂ�
* 
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
* 
* @return a��b�̊e��������Z�����x�N�g��
*/
Vector3 Vector3::Scale(const Vector3& a, const Vector3& b)
{
	float num = a.x * b.x;
	float num2 = a.y * b.y;
	float num3 = a.z * b.z;
	return Vector3(num, num2, num3);
}

/**
* a��b�̊e�v�f�̍ő�l�̃x�N�g����Ԃ�
*
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
*
* @return �e�v�f�̍ő�̃x�N�g��
*/
Vector3 Vector3::Max(const Vector3& a, const Vector3& b)
{
	return Vector3(Mathf::Max(a.x, b.x), Mathf::Max(a.y, b.y), Mathf::Max(a.z, b.z));
}

/**
* a��b�̊e�v�f�̍ŏ��l�̃x�N�g����Ԃ�
*
* @param a �v�Z�Ώۂ���1
* @param b �v�Z�Ώۂ���2
*
* @return �e�v�f�̍ŏ��̃x�N�g��
*/
Vector3 Vector3::Min(const Vector3& a, const Vector3& b)
{
	return Vector3(Mathf::Min(a.x, b.x), Mathf::Min(a.y, b.y), Mathf::Min(a.z, b.z));
}

/**
* �x�N�g���̒�����Ԃ�
*
* @return�x�N�g���̒���
*/
float Vector3::magnitude() const
{
	return Mathf::Sqrt(x * x + y * y + z * z);
}

/**
* �x�N�g���̒������悵�ĕԂ�
*
* @return �x�N�g���̓�悵������
*/
float Vector3::sqrtMagnitude() const
{
	return x * x + y * y + z * z;
}

/**
* �x�N�g���𐳋K�����ĕԂ�
*
* @return ���K�������x�N�g��
* @return zero 0���Z���ꂽ
*/
Vector3 Vector3::normalized() const
{
	Vector3 result = Vector3(x, y, z);
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
