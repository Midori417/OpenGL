/**
* @file Matrix4x4.cpp
*/
#include "FGEngine/Math/Matrix4x4.h"
#include "FGEngine/Math/Matrix3x3.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Mathf.h"

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	const Matrix4x4 Matrix4x4::identity = Matrix4x4(1);
	const Matrix4x4 Matrix4x4::zero = Matrix4x4(0);

	/**
	* 4��Vector4����Matrix4x4���쐬����R���X�g���N�^
	*/
	Matrix4x4::Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
		: num00(v0.x), num01(v0.y), num02(v0.z), num03(v0.w)
		, num10(v1.x), num11(v1.y), num12(v1.z), num13(v1.w)
		, num20(v2.x), num21(v2.y), num22(v2.z), num23(v2.w)
		, num30(v3.x), num31(v3.y), num32(v3.z), num33(v3.w)
	{
	}

	/**
	* 1��float����Ίp���ɃR�s�[����R���X�g���N�^
	*/
	Matrix4x4::Matrix4x4(float f)
		: num00(f), num01(0), num02(0), num03(0)
		, num10(0), num11(f), num12(0), num13(0)
		, num20(0), num21(0), num22(f), num23(0)
		, num30(0), num31(0), num32(0), num33(f)
	{
	}

	/*
	* Matrix3x3����Matrix4x4���쐬����R���X�g���N�^
	*/
	Matrix4x4::Matrix4x4(const Matrix3x3& m)
		: num00(m.num00), num01(m.num01), num02(m.num02), num03(0)
		, num10(m.num10), num11(m.num11), num12(m.num12), num13(0)
		, num20(m.num20), num21(m.num21), num22(m.num22), num23(0)
		, num30(0), num31(0), num32(0), num33(1)
	{
	}

	/**
	* �s��̍s���擾����
	*
	* @param index �s�̔ԍ�
	*/
	Vector4 Matrix4x4::GetRow(size_t index) const
	{
		Vector4 result = Vector4::zero;

		switch (index)
		{
		case 0:
			result.x = num00;
			result.y = num01;
			result.z = num02;
			result.w = num03;
			break;
		case 1:
			result.x = num10;
			result.y = num11;
			result.z = num12;
			result.w = num13;
			break;
		case 2:
			result.x = num20;
			result.y = num21;
			result.z = num22;
			result.w = num23;
			break;
		case 3:
			result.x = num30;
			result.y = num31;
			result.z = num32;
			result.w = num33;
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
	void Matrix4x4::SetRow(size_t index, const Vector4& v)
	{
		switch (index)
		{
		case 0:
			num00 = v.x;
			num01 = v.y;
			num02 = v.z;
			num03 = v.w;
			break;
		case 1:
			num10 = v.x;
			num11 = v.y;
			num12 = v.z;
			num13 = v.w;
			break;
		case 2:
			num20 = v.x;
			num21 = v.y;
			num22 = v.z;
			num23 = v.w;
			break;
		case 3:
			num30 = v.x;
			num31 = v.y;
			num32 = v.z;
			num33 = v.w;
			break;
		}
	}

	/**
	* �s��̗���擾����
	*
	* @param index ��̔ԍ�
	*/
	Vector4 Matrix4x4::GerColumn(size_t index) const
	{
		Vector4 result = Vector4::zero;

		switch (index)
		{
		case 0:
			result.x = num00;
			result.y = num10;
			result.z = num20;
			result.w = num30;
			break;
		case 1:
			result.x = num01;
			result.y = num11;
			result.z = num21;
			result.w = num31;
			break;
		case 2:
			result.x = num02;
			result.y = num12;
			result.z = num22;
			result.w = num32;
			break;
		case 3:
			result.x = num03;
			result.y = num13;
			result.z = num23;
			result.w = num33;
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
	void Matrix4x4::SetColumn(size_t index, const Vector4& v)
	{
		switch (index)
		{
		case 0:
			num00 = v.x;
			num10 = v.y;
			num20 = v.z;
			num30 = v.w;
			break;
		case 1:
			num01 = v.x;
			num11 = v.y;
			num21 = v.z;
			num31 = v.w;
			break;
		case 2:
			num02 = v.x;
			num12 = v.y;
			num22 = v.z;
			num32 = v.w;
			break;
		case 3:
			num03 = v.x;
			num13 = v.y;
			num23 = v.z;
			num33 = v.w;
			break;
		}
	}

	/**
	* �t�s����쐬[
	* 
	* @param matrix �t�s��ɂ������s��
	*/
	Matrix4x4 Matrix4x4::Invers(const Matrix4x4& matrix)
	{
		Matrix4x4 result(1);
		float det;
		int i;

		result.num00 = matrix.num11 * matrix.num22 * matrix.num33 - matrix.num11 * matrix.num23 * matrix.num32 - matrix.num21 * matrix.num12 * matrix.num33 + matrix.num21 * matrix.num13 * matrix.num32 + matrix.num31 * matrix.num12 * matrix.num23 - matrix.num31 * matrix.num13 * matrix.num22;
		result.num01 = -matrix.num01 * matrix.num22 * matrix.num33 + matrix.num01 * matrix.num23 * matrix.num32 + matrix.num21 * matrix.num02 * matrix.num33 - matrix.num21 * matrix.num03 * matrix.num32 - matrix.num31 * matrix.num02 * matrix.num23 + matrix.num31 * matrix.num03 * matrix.num22;
		result.num02 = matrix.num01 * matrix.num12 * matrix.num33 - matrix.num01 * matrix.num13 * matrix.num32 - matrix.num11 * matrix.num02 * matrix.num33 + matrix.num11 * matrix.num03 * matrix.num32 + matrix.num31 * matrix.num02 * matrix.num13 - matrix.num31 * matrix.num03 * matrix.num12;
		result.num03 = -matrix.num01 * matrix.num12 * matrix.num23 + matrix.num01 * matrix.num13 * matrix.num22 + matrix.num11 * matrix.num02 * matrix.num23 - matrix.num11 * matrix.num03 * matrix.num22 - matrix.num21 * matrix.num02 * matrix.num13 + matrix.num21 * matrix.num03 * matrix.num12;

		result.num10 = -matrix.num10 * matrix.num22 * matrix.num33 + matrix.num10 * matrix.num23 * matrix.num32 + matrix.num20 * matrix.num12 * matrix.num33 - matrix.num20 * matrix.num13 * matrix.num32 - matrix.num30 * matrix.num12 * matrix.num23 + matrix.num30 * matrix.num13 * matrix.num22;
		result.num11 = matrix.num00 * matrix.num22 * matrix.num33 - matrix.num00 * matrix.num23 * matrix.num32 - matrix.num20 * matrix.num02 * matrix.num33 + matrix.num20 * matrix.num03 * matrix.num32 + matrix.num30 * matrix.num02 * matrix.num23 - matrix.num30 * matrix.num03 * matrix.num22;
		result.num12 = -matrix.num00 * matrix.num12 * matrix.num33 + matrix.num00 * matrix.num13 * matrix.num32 + matrix.num10 * matrix.num02 * matrix.num33 - matrix.num10 * matrix.num03 * matrix.num32 - matrix.num30 * matrix.num02 * matrix.num13 + matrix.num30 * matrix.num03 * matrix.num12;
		result.num13 = matrix.num00 * matrix.num12 * matrix.num23 - matrix.num00 * matrix.num13 * matrix.num22 - matrix.num10 * matrix.num02 * matrix.num23 + matrix.num10 * matrix.num03 * matrix.num22 + matrix.num20 * matrix.num02 * matrix.num13 - matrix.num20 * matrix.num03 * matrix.num12;

		result.num20 = matrix.num10 * matrix.num21 * matrix.num33 - matrix.num10 * matrix.num23 * matrix.num31 - matrix.num20 * matrix.num11 * matrix.num33 + matrix.num20 * matrix.num13 * matrix.num31 + matrix.num30 * matrix.num11 * matrix.num23 - matrix.num30 * matrix.num13 * matrix.num21;
		result.num21 = -matrix.num00 * matrix.num21 * matrix.num33 + matrix.num00 * matrix.num23 * matrix.num31 + matrix.num20 * matrix.num01 * matrix.num33 - matrix.num20 * matrix.num03 * matrix.num31 - matrix.num30 * matrix.num01 * matrix.num23 + matrix.num30 * matrix.num03 * matrix.num21;
		result.num22 = matrix.num00 * matrix.num11 * matrix.num33 - matrix.num00 * matrix.num13 * matrix.num31 - matrix.num10 * matrix.num01 * matrix.num33 + matrix.num10 * matrix.num03 * matrix.num31 + matrix.num30 * matrix.num01 * matrix.num13 - matrix.num30 * matrix.num03 * matrix.num11;
		result.num23 = -matrix.num00 * matrix.num11 * matrix.num23 + matrix.num00 * matrix.num13 * matrix.num21 + matrix.num10 * matrix.num01 * matrix.num23 - matrix.num10 * matrix.num03 * matrix.num21 - matrix.num20 * matrix.num01 * matrix.num13 + matrix.num20 * matrix.num03 * matrix.num11;

		result.num30 = -matrix.num10 * matrix.num21 * matrix.num32 + matrix.num10 * matrix.num22 * matrix.num31 + matrix.num20 * matrix.num11 * matrix.num32 - matrix.num20 * matrix.num12 * matrix.num31 - matrix.num30 * matrix.num11 * matrix.num22 + matrix.num30 * matrix.num12 * matrix.num21;
		result.num31 = matrix.num00 * matrix.num21 * matrix.num32 - matrix.num00 * matrix.num22 * matrix.num31 - matrix.num20 * matrix.num01 * matrix.num32 + matrix.num20 * matrix.num02 * matrix.num31 + matrix.num30 * matrix.num01 * matrix.num22 - matrix.num30 * matrix.num02 * matrix.num21;
		result.num32 = -matrix.num00 * matrix.num11 * matrix.num32 + matrix.num00 * matrix.num12 * matrix.num31 + matrix.num10 * matrix.num01 * matrix.num32 - matrix.num10 * matrix.num02 * matrix.num31 - matrix.num30 * matrix.num01 * matrix.num12 + matrix.num30 * matrix.num02 * matrix.num11;
		result.num33 = matrix.num00 * matrix.num11 * matrix.num22 - matrix.num00 * matrix.num12 * matrix.num21 - matrix.num10 * matrix.num01 * matrix.num22 + matrix.num10 * matrix.num02 * matrix.num21 + matrix.num20 * matrix.num01 * matrix.num12 - matrix.num20 * matrix.num02 * matrix.num11;

		det = matrix.num00 * result.num00 + matrix.num01 * result.num10 + matrix.num02 * result.num20 + matrix.num03 * result.num30;

		if (det == 0)
		{
			return Matrix4x4::zero;
		}
		det = 1.0f / det;

		for (i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				result(i, j) *= det;
			}
		}

		return result;
	}

	/**
	* ���s�ړ��s����쐬
	*
	* @param position �ʒu
	*/
	Matrix4x4 Matrix4x4::Translate(const Vector3& position)
	{
		Matrix4x4 result = Matrix4x4::identity;

		result(3, 0) = position.x;
		result(3, 1) = position.y;
		result(3, 2) = position.z;
		return result;
	}

	/**
	* �g��k���s����쐬
	*
	* @param scale �X�P�[��
	*/
	Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
	{
		Matrix4x4 result = Matrix4x4::identity;
		result(0, 0) = scale.x;
		result(1, 1) = scale.y;
		result(2, 2) = scale.z;
		return result;
	}

	/**
	* X���̉�]�s����쐬
	*
	* @param angle x�̊p�x
	*/
	Matrix4x4 Matrix4x4::RotateX(float angle)
	{
		const float c = Mathf::Cos(angle);
		const float s = Mathf::Sin(angle);
		Matrix4x4 m = Matrix4x4::identity;
		// y' = y * c - z * s
		// z' = y * s + z * c
		m(1, 1) = c;
		m(2, 1) = -s;
		m(1, 2) = s;
		m(2, 2) = c;
		return m;
	}

	/**
	* Y���̉�]�s����쐬
	*
	* @param angle y�̊p�x
	*/
	Matrix4x4 Matrix4x4::RotateY(float angle)
	{
		const float c = Mathf::Cos(angle);
		const float s = Mathf::Sin(angle);
		Matrix4x4 m = Matrix4x4::identity;
		// x' = x * c + z * s
		// z' = x * -s + z * c
		m(0, 0) = c;
		m(2, 0) = s;
		m(0, 2) = -s;
		m(2, 2) = c;
		return m;
	}

	/**
	* Z���̉�]�s����쐬
	*
	* @param angle z�̊p�x
	*/
	Matrix4x4 Matrix4x4::RotateZ(float angle)
	{
		const float c = Mathf::Cos(angle);
		const float s = Mathf::Sin(angle);
		Matrix4x4 m = Matrix4x4::identity;
		// x' = x * c - y * s
		// y' = x * s + y * c
		m(0, 0) = c;
		m(1, 0) = -s;
		m(0, 1) = s;
		m(1, 1) = c;
		return m;
	}

	/**
	* ���W�ϊ��s��𕽍s�ړ��A�g�嗦�A��]�s��̊e�����ɕ�������
	*
	* @param[in] transform	�������̍��W�ϊ��s��
	* @param[out] translate ���s�ړ��̊i�[��ƂȂ�ϐ�
	* @param[out] scale		�g�嗦�̊i�[��ƂȂ�ϐ�
	* @param[out] rotation	��]�s��̊i�[��ƂȂ�ϐ�
	*/
	void Matrix4x4::Decompose(const Matrix4x4& transform, Vector3& translate, Vector3& scale, Matrix3x3& rotation)
	{
		// ���s�ړ��𕪉�
		translate = ExtractTranslate(transform);

		// �g�嗦�̕���
		scale = ExtractScale(transform);

		// ��]�s��𕪉�
		rotation = Matrix3x3(transform);
		rotation.SetRow(0, rotation.GetRow(0) / Vector3(scale.x));
		rotation.SetRow(1, rotation.GetRow(1) / Vector3(scale.y));
		rotation.SetRow(2, rotation.GetRow(2) / Vector3(scale.z));
	}

	/**
	* ���W�ϊ��s�񂩂畽�s�ړ��𒊏o
	*
	* @param transform ���o���̍��W�ϊ��s��
	*
	* @return ���o�������s�ړ�
	*/
	Vector3 Matrix4x4::ExtractTranslate(const Matrix4x4& transform)
	{
		return Vector3(transform.GetRow(3));
	}

	/**
	* ���W�ϊ��s�񂩂�g�嗦�𒊏o
	*
	* @param transform	���o���̍��W�ϊ��s��
	*
	* @return ���o�����g�嗦
	*/
	Vector3 Matrix4x4::ExtractScale(const Matrix4x4& transform)
	{
		const float sx = Vector3::Magnitude(Vector3(transform.GetRow(0)));
		const float sy = Vector3::Magnitude(Vector3(transform.GetRow(1)));
		const float sz = Vector3::Magnitude(Vector3(transform.GetRow(2)));
		return Vector3(sx, sy, sz);
	}

	/**
	* ���W�ϊ��s�񂩂��]�s��𒊏o
	*
	* @param transform	���o���̍��W�ϊ��s��
	*
	* @return ���o������]�s��
	*/
	Matrix3x3 Matrix4x4::ExtractRotation(const Matrix4x4& transform)
	{
		// �g�嗦�̕���
		Vector3 scale = ExtractScale(transform);

		// ��]�s��𕪉�
		Matrix3x3 rotation = Matrix3x3(transform);
		rotation.SetRow(0, rotation.GetRow(0) / Vector3(scale.x));
		rotation.SetRow(1, rotation.GetRow(1) / Vector3(scale.y));
		rotation.SetRow(2, rotation.GetRow(2) / Vector3(scale.z));

		return rotation;
	}

	/**
	* �r���[�s����쐬����
	*
	* @param eye		�n�_�̍��W
	* @param target		�����_�̍��W
	* @param up			�n�_�̏�������������̃x�N�g��
	*
	* @return eye, target, up����쐬�����r���[�s��
	*/
	Matrix4x4 Matrix4x4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		// ���[���h���W�n�ɂ�����n�_���W�n��XYZ�̌������v�Z
		const Vector3 axisZ = Vector3::Normalize(Vector3(eye - target));
		const Vector3 axisX = Vector3::Normalize(Vector3::Cross(up, axisZ));
		const Vector3 axisY = Vector3::Normalize(Vector3::Cross(axisZ, axisX));

		// ���W�����x�N�g���ɓ��e����悤�ɍs���ݒ�
		Matrix4x4 m;
		m.SetRow(0, Vector4{ axisX.x, axisY.x, axisZ.x, 0 });
		m.SetRow(1, Vector4{ axisX.y, axisY.y, axisZ.y, 0 });
		m.SetRow(2, Vector4{ axisX.z, axisY.z, axisZ.z, 0 });

		// eye�����_�ɂȂ�悤�ɁAeye���e���Ɏˉe���ĕ��s�ړ��ʂ��v�Z
		m.SetRow(3, Vector4{ -Vector3::Dot(axisX, eye),
			-Vector3::Dot(axisY, eye),
			-Vector3::Dot(axisZ, eye),
			1 });

		return m;
	}

	/**
	* ���s���e�s����쐬����
	*
	* @param left	�`��͈͂̍��[�܂ł̋���
	* @param right	�`��͈͂̉E�[�܂ł̋���
	* @param bottom	�`��͈͂̉��[�܂ł̋���
	* @param top	�`��͈͂̏�[�܂ł̋���
	* @param zNear	�`��͈͂Ɋ܂܂��ŏ�Z���W
	* @param zFar	�`��͈͂Ɋ܂܂��ő�Z���W
	*
	* @return ���s���e�s��
	*/
	Matrix4x4 Matrix4x4::Orthogonal(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		// �`��͈͂̃T�C�Y�ƒ��S���W���v�Z
		const Vector3 size = Vector3{ right - left, top - bottom, zFar - zNear };
		const Vector3 center = Vector3{ right + left, top + bottom, zFar + zNear };

		// �`��͈͓��̍��W��-1�`+1�ɕϊ������悤�ɁA�g�嗦�ƕ��s�ړ���ݒ�
		Matrix4x4 m;
		m.SetRow(0, Vector4{ 2 / size.x,  0, 0,	0 });
		m.SetRow(1, Vector4{ 0,	2 / size.y,	0, 0 });
		m.SetRow(2, Vector4{ 0,	0, -2 / size.z,	0 });
		m.SetRow(3, Vector4(-center / size, 1));
		return m;
	}

	/**
	* �Q�Ƃ�Ԃ��Y�������Z�q
	*
	* @param row	�s�̃C���f�b�N�X
	* @param column	��̃C���f�b�N�X
	*/
	const float& Matrix4x4::operator()(size_t row, size_t column) const
	{
		return *((&num00) + row * 4 + column);
	}

	/**
	* �Q�Ƃ�Ԃ��Y�������Z�q
	*
	* @param row	�s�̃C���f�b�N�X
	* @param column	��̃C���f�b�N�X
	*/
	float& Matrix4x4::operator()(size_t row, size_t column)
	{
		return *((&num00) + row * 4 + column);
	}

	/**
	* Matrix4x4��Vector4�̏�Z
	*/
	Vector4 operator*(const Matrix4x4& m, const Vector4& v)
	{
		return
			m.GetRow(0) * Vector4(v.x) +
			m.GetRow(1) * Vector4(v.y) +
			m.GetRow(2) * Vector4(v.z) +
			m.GetRow(3) * Vector4(v.w);
	}

	/**
	* Matrix4x4���m�̏�Z
	*/
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
	{
		return Matrix4x4(
			Vector4(a * b.GetRow(0)),
			Vector4(a * b.GetRow(1)),
			Vector4(a * b.GetRow(2)),
			Vector4(a * b.GetRow(3)));
	}

	/**
	* Matrix4x4���m�̑����Z
	*/
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b)
	{
		a = a * b;
		return a;
	}
}