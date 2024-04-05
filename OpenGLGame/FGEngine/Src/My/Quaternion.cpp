/**
* @file Quaternion.cpp
*/
#include "Quaternion.h"
#include "VectorPoint.h"
#include "MatrixPoint.h"
#include "Mathf.h"

namespace FGEngine
{
	// �X�^�e�B�b�N�ϐ��̏�����
	const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);

	/**
	* 4��float����N�H�[�^�j�I�����\�z����R���X�g���N�^
	*/
	Quaternion::Quaternion(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	/**
	* �N�H�[�^�j�I���𐳋K������
	*/
	void Quaternion::Normalize()
	{
		float magnitude = Mathf::Sqrt(Dot(*this, *this));
		if (magnitude > 0.0f)
		{
			*this = Quaternion(x / magnitude, y / magnitude, z / magnitude, w / magnitude);
		}
	}

	/**
	* ���K�������N�H�[�^�j�I�����擾
	*
	* @return ���K�������N�H�[�^�j�I��
	*/
	Quaternion Quaternion::Normalized() const
	{
		Quaternion result = *this;
		result.Normalize();
		return result;
	}

	/**
	* �I�C���[�p�ɕϊ����Ď擾
	*
	* @return �ϊ������I�C���[�p
	*/
	Vector3 Quaternion::EulerAngle() const
	{
		return Vector3();
	}

	/**
	* �N�H�[�^�j�I���̋t�����擾
	*
	* @param �N�H�[�^�j�I���̋t��
	*/
	Quaternion Quaternion::Inverse() const
	{
		Quaternion result = identity;
		float theta = Mathf::Sqrt(Dot(*this, *this));
		if (theta > 0.0f) 
		{
			result = Quaternion(
				-x / theta,
				-y / theta,
				-z / theta,
				w / theta
			);
		}
		return result;
	}

	/**
	* axis�̎����angle(�x���@)��]����N�H�[�^�j�I����Ԃ�
	*
	* @param angle	��]����p�x(�x���@)
	* @param axis	��]���鎲
	*
	* @return ��]�����N�H�[�^�j�I��
	*/
	Quaternion Quaternion::AngleAxis(float angle, const Vector3& axis)
	{
		float halfAngle = angle * 0.5f;
		Vector3 normalAxis = axis.Normalized();
		Quaternion result(
			Mathf::Sin(halfAngle) * normalAxis.x,
			Mathf::Sin(halfAngle) * normalAxis.y,
			Mathf::Sin(halfAngle) * normalAxis.z,
			Mathf::Cos(halfAngle)
		);
		return result;
	}

	/**
	* 2�̃N�H�[�^�j�I���̓��ς��v�Z����
	*
	* @param a	�N�H�[�^�j�I��1
	* @param b	�N�H�[�^�j�I��2
	*
	* @return a��b�̓���
	*/
	float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}

	/**
	* �O���x�N�g���Ə���x�N�g���̕����ɉ�]����
	*
	* @param foward	�O���x�N�g��
	* @param upward ����׃x�N�g��
	*
	* @return �쐬�����N�H�[�^�j�I��
	*/
	Quaternion Quaternion::LookRotation(const Vector3& foward, const Vector3& upward)
	{
		return Quaternion();
	}

	/**
	* �O���x�N�g���Ə���x�N�g���̕����ɉ�]����
	*
	* @param foward	�O���x�N�g��
	*
	* @return �쐬�����N�H�[�^�j�I��
	*/
	Quaternion Quaternion::LookRotation(const Vector3& foward)
	{
		return Quaternion();
	}

	/**
	* �N�H�[�^�j�I�� a �� �N�H�[�^�j�I�� b �̊Ԃ������Ԃ���
	*
	* @param a ��Ԃ̊J�n�N�H�[�^�j�I��
	* @param b ��Ԃ̏I���N�H�[�^�j�I��
	* @param t ��ԃp�����[�^ (0.0 ~ 1.0 �͈̔�)
	*
	* @return ��Ԃ��ꂽ�N�H�[�^�j�I��
	*/
	Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t)
	{
		return Quaternion();
	}

	/**
	* �I�C���[�p����N�H�[�^�j�I���ɕϊ�
	*
	* @param euler	�I�C���[�p
	*
	* @return �ϊ������N�H�[�^�j�I��
	*/
	Quaternion Quaternion::EulerToQuaternion(const Vector3& euler)
	{
		return EulerToQuaternion(euler.x, euler.y, euler.z);
	}

	/**
	* �I�C���[�p����N�H�[�^�j�I���ɕϊ�
	*
	* @param x	X�̊p�x(�x���@)
	* @param y	Y�̊p�x(�x���@)
	* @param z	Z�̊p�x(�x���@)
	*
	* @return �ϊ������N�H�[�^�j�I��
	*/
	Quaternion Quaternion::EulerToQuaternion(float x, float y, float z)
	{
		Quaternion result = Quaternion::identity;
		float tx = Mathf::DegToRad(x);
		float ty = Mathf::DegToRad(y);
		float tz = Mathf::DegToRad(z);
		// �I�C���[�p�̔����̒l���v�Z
		float cx = Mathf::Cos(tx * 0.5f);
		float sx = Mathf::Sin(tx * 0.5f);
		// Y��
		float cy = Mathf::Cos(ty * 0.5f);
		float sy = Mathf::Sin(ty * 0.5f);
		// Z��
		float cz = Mathf::Cos(tz * 0.5f);
		float sz = Mathf::Sin(tz * 0.5f);
		// �N�H�[�^�j�I���̊e�v�f���v�Z
		result.x = sx * cy * cz - cx * sy * sz;
		result.y = cx * sy * cz + sx * cy * sz;
		result.z = cx * cy * sz - sx * sy * cz;
		result.w = cx * cy * cz + sx * sy * sz;
		return result.Normalized();
	}

	/**
	* �N�H�[�^�j�I������I�C���[�p�ɕϊ�
	*
	* @param qua �N�H�[�^�j�I��
	*
	* @return �ϊ������I�C���[�p
	*/
	Vector3 Quaternion::QuaternionToEuler(const Quaternion& qua)
	{
		Vector3 axis;
		// X��
		float t0 = 2.0f * (qua.w * qua.x + qua.y * qua.z);
		float t1 = 1.0f - 2.0f * (qua.x * qua.x + qua.y * qua.y);
		axis.x = Mathf::Atan2(t0, t1);

		// Y��
		float t2 = 2.0f * (qua.w * qua.y - qua.z * qua.x);
		t2 = Mathf::Min(Mathf::Max(t2, -1.0f), 1.0f); 
		axis.y = Mathf::Asin(t2);

		// Z��
		float t3 = 2.0f * (qua.w * qua.z + qua.x * qua.y);
		float t4 = 1.0f - 2.0f * (qua.y * qua.y + qua.z * qua.z);
		axis.z = Mathf::Atan2(t3, t4);
		return axis;
	}

	/**
	* ��]�s��(Matrix3x3)����N�H�[�^�j�I���ɕϊ�
	*
	* @param mat ��]�s��(Matrix3x3)
	*
	* @return �ϊ������N�H�[�^�j�I��
	*/
	Quaternion Quaternion::RotationMatrixToQuaternion(const Matrix3x3& rotationMatrix)
	{
		float trace = rotationMatrix[0][0] + rotationMatrix[1][1] + rotationMatrix[2][2];
		float s = 0.0f;
		Quaternion result = Quaternion::identity;
		if (trace > 0.0f) {
			s = 0.5f / Mathf::Sqrt(trace + 1.0f);
			result.x = (rotationMatrix[2][1] - rotationMatrix[1][2]) * s;
			result.y = (rotationMatrix[0][2] - rotationMatrix[2][0]) * s;
			result.z = (rotationMatrix[1][0] - rotationMatrix[0][1]) * s;
			result.w = 0.25f / s;
		}
		else if (rotationMatrix[0][0] > rotationMatrix[1][1] && rotationMatrix[1][1] > rotationMatrix[2][2]) {
			s = 2.0f * Mathf::Sqrt(1.0f + rotationMatrix[0][0] - rotationMatrix[1][1] - rotationMatrix[2][2]);
			result.x = 0.25f * s;
			result.y = (rotationMatrix[0][1] + rotationMatrix[1][0]) / s;
			result.z = (rotationMatrix[0][2] + rotationMatrix[2][0]) / s;
			result.w = (rotationMatrix[2][1] - rotationMatrix[1][2]) / s;
		}
		else if (rotationMatrix[1][1] > rotationMatrix[2][2]) {
			s = 2.0f * Mathf::Sqrt(1.0f + rotationMatrix[1][1] - rotationMatrix[0][0] - rotationMatrix[2][2]);
			result.x = (rotationMatrix[0][1] + rotationMatrix[1][0]) / s;
			result.y = 0.25f * s;
			result.z = (rotationMatrix[1][2] + rotationMatrix[2][1]) / s;
			result.w = (rotationMatrix[0][2] - rotationMatrix[2][0]) / s;
		}
		else {
			s = 2.0f * Mathf::Sqrt(1.0f + rotationMatrix[2][2] - rotationMatrix[0][0] - rotationMatrix[1][1]);
			result.x = (rotationMatrix[0][2] + rotationMatrix[2][0]) / s;
			result.y = (rotationMatrix[1][2] + rotationMatrix[2][1]) / s;
			result.z = 0.25f * s;
			result.w = (rotationMatrix[1][0] - rotationMatrix[0][1]) / s;
		}
		return result.Normalized();
	}

	/**
	* ��]�s��(Matrix4x4)����N�H�[�^�j�I���ɕϊ�
	*
	* @param rotationMatrix ��]�s��(Matrix4x4)
	*
	* @return �ϊ������N�H�[�^�j�I��
	*/
	Quaternion Quaternion::RotationMatrixToQuaternion(const Matrix4x4& rotationMatrix)
	{
		return RotationMatrixToQuaternion(Matrix3x3(rotationMatrix));
	}

	/**
	* �N�H�[�^�j�I�������]�s��(Matrix3x3)�ɕϊ�
	*
	* @param qua �N�H�[�^�j�I��
	*
	* @return �ϊ�������]�s��(Matrix3x3)
	*/
	Matrix3x3 Quaternion::QuaternionToRotationMatrix3x3(const Quaternion& qua)
	{
		Matrix3x3 rotationMatrix;
		rotationMatrix.data[0].x = 1.0f - 2.0f * (qua.y * qua.y + qua.z * qua.z);
		rotationMatrix.data[1].x = 2.0f * (qua.x * qua.y - qua.z * qua.w);
		rotationMatrix.data[2].x = 2.0f * (qua.x * qua.z + qua.y * qua.w);

		rotationMatrix.data[0].y = 2.0f * (qua.x * qua.y + qua.z * qua.w);
		rotationMatrix.data[1].y = 1.0f - 2.0f * (qua.x * qua.x + qua.z * qua.z);
		rotationMatrix.data[2].y = 2.0f * (qua.y * qua.z - qua.x * qua.w);

		rotationMatrix.data[0].z = 2.0f * (qua.x * qua.z - qua.y * qua.w);
		rotationMatrix.data[1].z = 2.0f * (qua.y * qua.z + qua.x * qua.w);
		rotationMatrix.data[2].z = 1.0f - 2.0f * (qua.x * qua.x + qua.y * qua.y);

		return rotationMatrix;
	}

	/**
	* �N�H�[�^�j�I�������]�s��(Matrix4x4)�ɕϊ�
	*
	* @param qua �N�H�[�^�j�I��
	*
	* @return �ϊ�������]�s��(Matrix4x4)
	*/
	Matrix4x4 Quaternion::QuaternionToRotationMatrix4x4(const Quaternion& qua)
	{
		return Matrix4x4(QuaternionToRotationMatrix3x3(qua));
	}

	/**
	* �N�H�[�^�j�I�����m�̏�Z
	*/
	Quaternion operator*(const Quaternion& a, const Quaternion& b)
	{
		Quaternion result(
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
			a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
		);
		return result;
	}

	/**
	* �N�H�[�^�j�I���ƃx�N�g��3�̏�Z
	*/
	Vector3 operator*(const Quaternion& qua, const Vector3& v)
	{
		float num = qua.x * 2.0f;
		float num2 = qua.y * 2.0f;
		float num3 = qua.z * 2.0f;
		float num4 = qua.x * num;
		float num5 = qua.y * num2;
		float num6 = qua.z * num3;
		float num7 = qua.x * num2;
		float num8 = qua.x * num3;
		float num9 = qua.y * num3;
		float num10 = qua.w * num;
		float num11 = qua.w * num2;
		float num12 = qua.w * num3;
		Vector3 result = v;
		result.x = (1.0f - (num5 + num6)) * v.x + (num7 - num12) * v.y + (num8 + num11) * v.z;
		result.y = (num7 + num12) * v.x + (1.0f - (num4 + num6)) * v.y + (num9 - num10) * v.z;
		result.z = (num8 - num11) * v.x + (num9 + num10) * v.y + (1.0f - (num4 + num5)) * v.z;
		return result;
	}

	/**
	* �N�H�[�^�j�I���̔�r���Z
	*/
	bool operator==(const Quaternion& a, const Quaternion& b)
	{
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w);
	}

}