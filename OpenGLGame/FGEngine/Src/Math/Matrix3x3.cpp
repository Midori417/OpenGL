/**
* @file Matrix3x3.cpp
*/
#include "FGEngine/Math/Matrix3x3.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Matrix4x4.h"

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	const Matrix3x3 Matrix3x3::identity = Matrix3x3(1);
	const Matrix3x3 Matrix3x3::zero = Matrix3x3(0);

	/**
	* 3��Vector3����Matrix3x3���쐬����R���X�g���N�^
	*
	* @param v0
	* @param v1
	* @param v2
	*/
	Matrix3x3::Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2)
		: num00(v0.x), num01(v0.y), num02(v0.z)
		, num10(v1.x), num11(v1.y), num12(v1.z)
		, num20(v2.x), num21(v2.y), num22(v2.z)
	{

	}

	/**
	* 1��float��Ίp����Matrix3x3���쐬����R���X�g���N�^
	*
	* @param f
	*/
	Matrix3x3::Matrix3x3(float f)
		: num00(f), num01(0), num02(0)
		, num10(0), num11(f), num12(0)
		, num20(0), num21(0), num22(f)
	{
	}

	/**
	* Matrix4x4����Matrix3x3���쐬����R���X�g���N�^
	*
	* @param m �ϊ�����Matrix4x4
	*/
	Matrix3x3::Matrix3x3(const Matrix4x4& m)
		: num00(m.num00), num01(m.num01), num02(m.num02)
		, num10(m.num10), num11(m.num11), num12(m.num12)
		, num20(m.num20), num21(m.num21), num22(m.num22)
	{
	}

	/**
	* �s��̍s���擾����
	*
	* @param index �s�̔ԍ�
	*/
	Vector3 Matrix3x3::GetRow(size_t index) const
	{
		Vector3 result = Vector3::zero;

		switch (index)
		{
		case 0:
			result.x = num00;
			result.y = num01;
			result.z = num02;
			break;
		case 1:
			result.x = num10;
			result.y = num11;
			result.z = num12;
			break;
		case 2:
			result.x = num20;
			result.y = num21;
			result.z = num22;
			break;
		}

		return result;
	}

	/**
	* �s��̍s��ݒ肷��
	*
	* @param index	�s�̔ԍ�
	* @param v		�ݒ肷��Vector3
	*/
	void Matrix3x3::SetRow(size_t index, const Vector3& v)
	{
		switch (index)
		{
		case 0:
			num00 = v.x;
			num01 = v.y;
			num02 = v.z;
			break;
		case 1:
			num10 = v.x;
			num11 = v.y;
			num12 = v.z;
			break;
		case 2:
			num20 = v.x;
			num21 = v.y;
			num22 = v.z;
			break;
		}
	}

	/**
	* �s��̗���擾����
	*
	* @param index ��̔ԍ�
	*/
	Vector3 Matrix3x3::GerColumn(size_t index) const
	{
		Vector3 result = Vector3::zero;

		switch (index)
		{
		case 0:
			result.x = num00;
			result.y = num10;
			result.z = num20;
			break;
		case 1:
			result.x = num01;
			result.y = num11;
			result.z = num21;
			break;
		case 2:
			result.x = num02;
			result.y = num12;
			result.z = num22;
			break;
		}

		return result;
	}

	/**
	* �s��̗��ݒ肷��
	*
	* @param index	��̔ԍ�
	* @param v		�ݒ肷��Vector3
	*/
	void Matrix3x3::SetColumn(size_t index, const Vector3& v)
	{
		switch (index)
		{
		case 0:
			num00 = v.x;
			num10 = v.y;
			num20 = v.z;
			break;
		case 1:
			num01 = v.x;
			num11 = v.y;
			num21 = v.z;
			break;
		case 2:
			num02 = v.x;
			num12 = v.y;
			num22 = v.z;
			break;
		}
	}

	/**
	* �]�u�s������߂�
	*/
	Matrix3x3 Matrix3x3::Transpose(const Matrix3x3& m)
	{
		Matrix3x3 result = Matrix3x3::identity;

		result(0, 0) = m(0, 0);
		result(0, 1) = m(1, 0);
		result(0, 2) = m(2, 0);

		result(1, 0) = m(0, 1);
		result(1, 1) = m(1, 1);
		result(1, 2) = m(2, 1);

		result(2, 0) = m(0, 2);
		result(2, 1) = m(1, 2);
		result(2, 2) = m(2, 2);

		return result;
	}

	/**
	* �t�s����v�Z����
	*/
	Matrix3x3 Matrix3x3::Inverse(const Matrix3x3& m)
	{
		// �l���q�s����v�Z
		Matrix3x3 adjugate = Matrix3x3::identity;

		adjugate(0, 0) = m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1);
		adjugate(0, 1) = -m(0, 1) * m(2, 2) + m(0, 2) * m(2, 1);
		adjugate(0, 2) = m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1);

		adjugate(1, 0) = -m(1, 0) * m(2, 2) + m(1, 2) * m(2, 0);
		adjugate(1, 1) = m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0);
		adjugate(1, 2) = -m(0, 0) * m(1, 2) + m(0, 2) * m(1, 0);

		adjugate(2, 0) = m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0);
		adjugate(2, 1) = -m(0, 0) * m(2, 1) + m(0, 1) * m(2, 0);
		adjugate(2, 2) = m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);

		// �s�񎮂��v�Z
		const float det =
			m(0, 0) * m(1, 1) * m(2, 2) - m(0, 0) * m(1, 2) * m(2, 1) +
			m(0, 1) * m(1, 2) * m(2, 0) - m(0, 1) * m(1, 0) * m(2, 2) +
			m(0, 2) * m(1, 0) * m(2, 1) - m(0, 2) * m(1, 1) * m(2, 0);

		// �s�񎮂̋t�����|����
		const float invDet = 1.0f / det;
		adjugate.SetRow(0, adjugate.GetRow(0) * Vector3(invDet));
		adjugate.SetRow(1, adjugate.GetRow(1) * Vector3(invDet));
		adjugate.SetRow(2, adjugate.GetRow(2) * Vector3(invDet));

		return adjugate;
	}

	/**
	* �Q�Ƃ�Ԃ��Y�������Z�q
	*
	* @param row	�s�̃C���f�b�N�X
	* @param column	��̃C���f�b�N�X
	*/
	const float& Matrix3x3::operator()(size_t row, size_t column) const
	{
		return *((&num00) + row * 3 + column);
	}

	/**
	* �Q�Ƃ�Ԃ��Y�������Z�q
	*
	* @param row	�s�̃C���f�b�N�X
	* @param column	��̃C���f�b�N�X
	*/
	float& Matrix3x3::operator()(size_t row, size_t column)
	{
		return *((&num00) + row * 3 + column);
	}

	/**
	* Matrix3x3��Vector3�̏�Z
	*/
	Vector3 operator*(const Matrix3x3& m, const Vector3& v)
	{
		return
			m.GetRow(0) * Vector3(v.x) +
			m.GetRow(1) * Vector3(v.y) +
			m.GetRow(2) * Vector3(v.z);
	}

	/**
	* Matrix3x3���m�̏�Z
	*/
	Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b)
	{
		return Matrix3x3(
			Vector3(a * b.GetRow(0)),
			Vector3(a * b.GetRow(1)),
			Vector3(a * b.GetRow(2)));
	}

	/**
	* Matrix3x3���m�̑����Z
	*/
	Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b)
	{
		a = a * b;
		return a;
	}
}