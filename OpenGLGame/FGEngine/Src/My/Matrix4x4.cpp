/**
* @file Matrix4x4.cpp
*/
#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "Vector3.h"
#include "Mathf.h"

namespace FGEngine
{
	/**
	* 4��Vector4����Matrix4x4���\������R���X�g���N�^
	*/
	Matrix4x4::Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
	{
		data[0] = v0;
		data[1] = v1;
		data[2] = v2;
		data[3] = v3;
	}

	/**
	* 1��float��Ίp���ɃR�s�[����R���X�g���N�^
	*/
	Matrix4x4::Matrix4x4(float f)
	{
		data[0] = Vector4{ f, 0, 0, 0 };
		data[1] = Vector4{ 0, f, 0, 0 };
		data[2] = Vector4{ 0, 0, f, 0 };
		data[3] = Vector4{ 0, 0, 0, f };
	}

	/**
	* Matrix3x3����Matrix4x4�ɕϊ�����R���X�g���N�^
	*/
	Matrix4x4::Matrix4x4(const Matrix3x3& m)
	{
		data[0] = Vector4{ m.data[0], 0 };
		data[1] = Vector4{ m.data[1], 0 };
		data[2] = Vector4{ m.data[2], 0 };
		data[3] = Vector4{ 0, 0, 0, 1 };
	}

	/**
	* ���s�ړ��s����쐬
	*
	* @param position �ʒu
	*/
	Matrix4x4 Matrix4x4::Translate(const Vector3& position)
	{
		Matrix4x4 m(1);
		m[3][0] = position.x;
		m[3][1] = position.y;
		m[3][2] = position.z;
		return m;
	}

	/**
	*  �g��k���s����쐬
	*
	* @param scale �X�P�[��
	*/
	Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
	{
		Matrix4x4 m(1);
		m[0][0] = scale.x;
		m[1][1] = scale.y;
		m[2][2] = scale.z;
		return m;
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
		Matrix4x4 m(1);
		// y' = y * c - z * s
		// z' = y * s + z * c
		m[1][1] = c;
		m[2][1] = -s;
		m[1][2] = s;
		m[2][2] = c;
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
		Matrix4x4 m(1);
		// x' = x * c + z * s
		// z' = x * -s + z * c
		m[0][0] = c;
		m[2][0] = s;
		m[0][2] = -s;
		m[2][2] = c;
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
		Matrix4x4 m(1);
		// x' = x * c - y * s
		// y' = x * s + y * c
		m[0][0] = c;
		m[1][0] = -s;
		m[0][1] = s;
		m[1][1] = c;
		return m;
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
		const Vector3 axisZ = -Vector3(eye - target).Normalized();
		const Vector3 axisX = Vector3::Cross(up, axisZ).Normalized();
		const Vector3 axisY = Vector3::Cross(axisZ, axisX).Normalized();

		// ���W�����x�N�g���ɓ��e����悤�ɍs���ݒ�
		Matrix4x4 m;
		m[0] = Vector4{ axisX.x, axisY.x, axisZ.x, 0 };
		m[1] = Vector4{ axisX.y, axisY.y, axisZ.y, 0 };
		m[2] = Vector4{ axisX.z, axisY.z, axisZ.z, 0 };

		// eye�����_�ɂȂ�悤�ɁAeye���e���Ɏˉe���ĕ��s�ړ��ʂ��v�Z
		m[3] = Vector4{ -Vector3::Dot(axisX, eye), -Vector3::Dot(axisY, eye), -Vector3::Dot(axisZ, eye), 1 };

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
		m[0] = Vector4{ 2 / size.x,	 0,			0,	0 };
		m[1] = Vector4{ 0,		2 / size.y,			0,	0 };
		m[2] = Vector4{ 0,		0,			-2 / size.z,	0 };
		m[3] = Vector4(-center / size, 1);
		return m;
	}

	/**
	* ���W�ϊ��s�񂩂�g�嗦�𒊏o����
	* 
	* @param transform �������̍��W�ϊ��s��
	* 
	* @return ���o�����g�嗦
	*/
	Vector3 ExtractScale(const Matrix4x4& transform)
	{
		const float sx = Vector3(transform[0]).Magnitude();
		const float sy = Vector3(transform[1]).Magnitude();
		const float sz = Vector3(transform[2]).Magnitude();
		return Vector3{ sx,sy,sz };
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
		translate = Vector3(transform[3]);

		// �g�嗦�̕���
		scale = ExtractScale(transform);

		// ��]�s��𕪉�
		rotation = Matrix3x3(transform);
		rotation[0] /= scale.x;
		rotation[1] /= scale.y;
		rotation[2] /= scale.z;
	}

	/**
	* ���W�ϊ��s�񂩂�g�嗦�𒊏o
	*
	* @param transform	���o���̍��W�ϊ��s��
	*
	* @return ���o�����g�嗦��
	*/
	Vector3 Matrix4x4::ExtractScale(const Matrix4x4& transform)
	{
		const float sx = Vector3(transform[0]).Magnitude();
		const float sy = Vector3(transform[1]).Magnitude();
		const float sz = Vector3(transform[2]).Magnitude();
		return Vector3{ sx,sy,sz };
	}

	/**
	* Matrix3x3��Vector3�̏�Z
	*/
	Vector4 operator*(const Matrix4x4& m, const Vector4& v)
	{
		return m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3] * v.w;
	}

	/**
	* Matrix3x3���m�̏�Z
	*/
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
	{
		Matrix4x4 m;
		m.data[0] = a * b.data[0];
		m.data[1] = a * b.data[1];
		m.data[2] = a * b.data[2];
		m.data[3] = a * b.data[3];

		return m;
	}

	/**
	* Matrix3x3���m�̑����Z
	*/
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b)
	{
		a = a * b;
		return a;
	}
}