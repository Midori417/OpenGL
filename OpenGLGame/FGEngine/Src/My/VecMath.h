/**
* @file VecMath.h
*/
#ifndef VECMATH_H_INCLUDED
#define VECMATH_H_INCLUDED

#include "VectorPoint.h"
#include "MatrixPoint.h"
#include "Quaternion.h"
#include "Mathf.h"
#include <vector>

// �I�C���[�p�����]�s����쐬
inline Matrix3x3 EulerAnglesToRotationMatrix(const Vector3& rotation)
{
	const float sinX = sinf(rotation.x);
	const float cosX = cosf(rotation.x);
	const float sinY = sinf(rotation.y);
	const float cosY = cosf(rotation.y);
	const float sinZ = sinf(rotation.z);
	const float cosZ = cosf(rotation.z);

	//XYZ�̉�]��
	return{
		Vector3{ (cosY * cosZ),								(cosY * sinZ),							(-sinY)},
		Vector3{ (sinX * sinY * cosZ) + (cosX * -sinZ),		(sinX * sinY * sinZ) + (cosX * cosZ),	(sinX * cosY)},
		Vector3{ (cosX * sinY * cosZ) + (sinX * sinZ),		(cosX * sinY * sinZ) + (-sinX * cosZ),	(cosX * cosY)}
	};
}

// �g�嗦�A��]�p�x�A���s�ړ��ʂ�����W�ϊ��s����쐬
inline Matrix4x4 GetTransformMatrix(const Vector3& scale, const Quaternion& rotation, const Vector3& position)
{
	const Matrix4x4 pos = Matrix4x4::Translate(position);
	const Matrix4x4 rot = Quaternion::Matrix4x4Cast(rotation);
	const Matrix4x4 s = Matrix4x4::Scale(scale);
	return pos * rot * s;
}


// 4x4�s�񂩂�g�嗦�𒊏o����
inline Vector3 ExtractScale(const Matrix4x4& transform)
{
	const float sx = Vector3(transform[0]).magnitude();
	const float sy = Vector3(transform[1]).magnitude();
	const float sz = Vector3(transform[2]).magnitude();
	return { sx,sy,sz };
}

/**
* ���W�ϊ��s��𕽍s�ړ��A�g�嗦�A��]�s��̊e�����ɕ�������
*
* @param[in] transform	�������̍��W�ϊ��s��
* @param[out] translate ���s�ړ��̊i�[��ƂȂ�ϐ�
* @param[out] scale		�g�嗦�̊i�[��ƂȂ�ϐ�
* @param[out] rotation	��]�s��̊i�[��ƂȂ�ϐ�
*/
inline void Decompose(const Matrix4x4& transform, Vector3& translate,
	Vector3& scale, Matrix3x3& rotation)
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
* �r���[�s����쐬����
*
* @param eye		�n�_�̍��W
* @param target		�����_�̍��W
* @param up			�n�_�̏�������������̃x�N�g��
*
* @return eye, target, up����쐬�����r���[�s��
*/
inline Matrix4x4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	// ���[���h���W�n�ɂ�����n�_���W�n��XYZ�̌������v�Z
	const Vector3 axisZ = Vector3(eye - target).normalized();
	const Vector3 axisX = Vector3::Cross(up, axisZ).normalized();
	const Vector3 axisY = Vector3::Cross(axisZ, axisX).normalized();

	// ���W�����x�N�g���ɓ��e����悤�ɍs���ݒ�
	Matrix4x4 m;
	m[0] = Vector4{ axisX.x, axisY.x, axisZ.x, 0 };
	m[1] = Vector4{ axisX.y, axisY.y, axisZ.y, 0 };
	m[2] = Vector4{ axisX.z, axisY.z, axisZ.z, 0 };

	// eye�����_�ɂȂ�悤�ɁAeye���e���Ɏˉe���ĕ��s�ړ��ʂ��v�Z
	m[3] = Vector4{ -Vector3::Dot(axisX, eye), -Vector3::Dot(axisY, eye), -Vector3::Dot(axisZ, eye), 1 };

	return m;
}

inline Matrix4x4 ViewPointToProjectionMatrix(float fov, float aspectRatio, float nearClip = 0.35f, float farClip = 1000)
{
	Matrix4x4 projectionMatrix(0);
	float tanHalfFov = Mathf::Tan(0.5f * fov);
	float rangeInv = 1.0f / (nearClip - farClip);

	projectionMatrix[0][0] = 1.0f / (tanHalfFov * aspectRatio);
	projectionMatrix[1][1] = 1.0f / tanHalfFov;
	projectionMatrix[2][2] = (nearClip + farClip) * rangeInv;
	projectionMatrix[2][3] = -1.0f;
	projectionMatrix[3][2] = 2.0f * nearClip * farClip * rangeInv;

	return projectionMatrix;
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
inline Matrix4x4 Orthogonal(float left, float right, float bottom, float top, float zNear, float zFar)
{
	// �`��͈͂̃T�C�Y�ƒ��S���W���v�Z
	const Vector3 size = { right - left, top - bottom, zFar - zNear };
	const Vector3 center = { right + left, top + bottom, zFar + zNear };

	// �`��͈͓��̍��W��-1�`+1�ɕϊ������悤�ɁA�g�嗦�ƕ��s�ړ���ݒ�
	Matrix4x4 m;
	m[0] = Vector4{ 2 / size.x,	 0,			0,	0 };
	m[1] = Vector4{ 0,		2 / size.y,			0,	0 };
	m[2] = Vector4{ 0,		0,			-2 / size.z,	0 };
	m[3] = Vector4(-center / size, 1);
	return m;
}
#endif // !VECMATH_H_INCLUDED

