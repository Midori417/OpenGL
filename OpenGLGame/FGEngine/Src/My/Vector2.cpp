/**
* @file Vector2.cpp
*/
#include "Vector2.h"
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

	//=======================================
	//
	//  �֐�
	//
	//=======================================

	/**
	* ���g�̃x�N�g���𐳋K������
	*/
	void Vector2::Normalize()
	{
		float num = magnitude();
		if (num > 0.0f) {
			*this /= num;
		}
		else
		{
			*this = Vector2::zero;
		}
	}

	/**
	* �e�v�f�����̊e�v�f�Ə�Z����
	*
	* @param v ��Z����v�f
	*/
	void Vector2::Scale(const Vector2& v)
	{
		x *= v.x;
		y += v.y;
	}

	/**
	* a��b�̃x�N�g���̓��ς�Ԃ�
	*
	* @param a �v�Z�Ώۂ���1
	* @param b �v�Z�Ώۂ���2
	*
	* @return ��̃x�N�g���̓���
	*/
	float Vector2::Dot(const Vector2& a, const Vector2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	/**
	* a��b�̃x�N�g���̋�����Ԃ�
	*
	* @param a �v�Z�Ώۂ���1
	* @param b �v�Z�Ώۂ���2
	*
	* @return ��̃x�N�g���̋���
	*/
	float Vector2::Distance(const Vector2& a, const Vector2& b)
	{
		float num = a.x - b.x;
		float num2 = a.y - b.y;
		return Mathf::Sqrt(num * num + num2 * num2);
	}

	/**
	* a��b�̊Ԃ�t(Clamp0�`1)�Ő��`��Ԃ���
	*/
	Vector2 Vector2::Lerp(const Vector2& a, const Vector2& b, float t)
	{
		t = Mathf::Clamp01(t);
		return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
	}

	/**
	* a��b�̊Ԃ�t�Ő��`��Ԃ���
	*/
	Vector2 Vector2::LerpUnclamped(const Vector2& a, const Vector2& b, float t)
	{
		return Vector2(a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t);
	}

	/**
	* ���݂̈ʒucurrent����target�Ɍ����Ĉړ�����
	*
	* @param current	���݈ʒu
	* @param target		�^�[�Q�b�g�ʒu
	*
	*/
	Vector2 Vector2::MoveTowards(const Vector2& current, const Vector2& target, float maxDistanceDelta)
	{
		float num = target.x - current.x;
		float num2 = target.y - current.y;
		float num3 = num * num + num2 * num2;
		if (num3 == 0.0f || (maxDistanceDelta >= 0.0f && num3 <= maxDistanceDelta * maxDistanceDelta))
		{
			return target;
		}

		float num4 = Mathf::Sqrt(num3);
		return Vector2(current.x + num / num4 * maxDistanceDelta, current.y + num2 / num4 * maxDistanceDelta);
	}

	/**
	* a��b�̊e�v�f����Z���ĕԂ�
	*
	* @param a �v�Z�Ώۂ���1
	* @param b �v�Z�Ώۂ���2
	*
	* @return a��b����Z�����x�N�g��
	*/
	Vector2 Vector2::Scale(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	/**
	* a��b�̊e�v�f�̍ő�l�̃x�N�g����Ԃ�
	*
	* @param a �v�Z�Ώۂ���1
	* @param b �v�Z�Ώۂ���2
	*
	* @return �e�v�f�̍ő�̃x�N�g��
	*/
	Vector2 Vector2::Max(const Vector2& a, const Vector2& b)
	{
		return Vector2(Mathf::Max(a.x, b.x), Mathf::Max(a.y, b.y));
	}

	/**
	* a��b�̊e�v�f�̍ŏ��l�̃x�N�g����Ԃ�
	*
	* @param a �v�Z�Ώۂ���1
	* @param b �v�Z�Ώۂ���2
	*
	* @return �e�v�f�̍ŏ��̃x�N�g��
	*/
	Vector2 Vector2::Min(const Vector2& a, const Vector2& b)
	{
		return Vector2(Mathf::Min(a.x, b.x), Mathf::Min(a.y, b.y));
	}

	/**
	* �x�N�g���̒�����Ԃ�
	*
	* @return�x�N�g���̒���
	*/
	float Vector2::magnitude() const
	{
		return Mathf::Sqrt(x * x + y * y);
	}

	/**
	* �x�N�g���̒������悵�ĕԂ�
	*
	* @return �x�N�g���̓�悵������
	*/
	float Vector2::sqrtMagnitude() const
	{

		return x * x + y * y;
	}

	/**
	* �x�N�g���𐳋K�����ĕԂ�
	*
	* @return ���K�������x�N�g��
	* @return zero 0���Z���ꂽ
	*/
	Vector2 Vector2::normalized() const
	{
		Vector2 result = Vector2(x, y);
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