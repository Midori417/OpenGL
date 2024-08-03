/**
* @file Quaternion.cpp
*/
#include "FGEngine/Math/Quaternion.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Matrix3x3.h"
#include "FGEngine/Math/Mathf.h"
#include <cmath>

namespace FGEngine
{
	// �ÓI�ϐ��̏�����
	const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);

	/**
	* 4��float����Quaternion���쐬����R���X�g���N�^
	*
	* @param x X����
	* @param y Y����
	* @param z Z����
	* @param w W����
	*/
	Quaternion::Quaternion(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w)
	{
	}

	/**
	* �I�C���[�p���N�H�[�^�j�I���ɕϊ�����
	*
	* @param x	X�̊p�x(�x���@)
	* @param y	Y�̊p�x(�x���@)
	* @param z	Z�̊p�x(�x���@)
	*/
	Quaternion Quaternion::Euler(float x, float y, float z)
	{
		Quaternion result = Quaternion::identity;

		// �ʓx�@�ɕϊ�
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

		return result;
	}

	/**
	* �I�C���[�p���N�H�[�^�j�I���ɕϊ�����
	*
	* @param v �I�C���[�p
	*/
	Quaternion Quaternion::Euler(const Vector3& v)
	{
		return Euler(v.x, v.y, v.z);
	}

	/**
	* �N�H�[�^�j�I������I�C���[�p�ɕϊ�����
	*/
	Vector3 Quaternion::EulerAngle(const Quaternion& q)
	{
		Vector3 axis = Vector3::zero;

		// ���[���p (x ������̉�])
		float sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
		float cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
		axis.x = Mathf::Atan2(sinr_cosp, cosr_cosp);
		axis.x = Mathf::RadToDeg(axis.x);

		// �s�b�`�p (y ������̉�])
		float sinp = 2 * (q.w * q.y - q.z * q.x);
		if (Mathf::Abs(sinp) >= 1)
		{
			axis.y = std::copysign(Mathf::PI / 2, sinp); // �s�b�`�p�̓��ٓ_������
			axis.y = Mathf::RadToDeg(axis.y);
		}
		else
		{
			axis.y = Mathf::Asin(sinp);
			axis.y = Mathf::RadToDeg(axis.y);
		}

		// ���[�p (z ������̉�])
		float siny_cosp = 2 * (q.w * q.z + q.x * q.y);
		float cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
		axis.z = Mathf::Atan2(siny_cosp, cosy_cosp);
		axis.z = Mathf::RadToDeg(axis.z);

		return axis;
	}

	/**
	* ��]�s����N�H�[�^�j�I���ɕϊ�
	*/
	Quaternion Quaternion::RotationMatrixToQuaternion(const Matrix3x3& m)
	{
		float trace = m(0, 0) + m(1, 1) + m(2, 2);
		float s = 0.0f;
		Quaternion result = Quaternion::identity;
		if (trace > 0.0f)
		{
			s = 0.5f / Mathf::Sqrt(trace + 1.0f);
			result.x = (m(2, 1) - m(1, 2)) * s;
			result.y = (m(0, 2) - m(2, 0)) * s;
			result.z = (m(1, 0) - m(0, 1)) * s;
			result.w = 0.25f / s;
		}
		else if (m(0, 0) > m(1, 1) && m(1, 1) > m(2, 2))
		{
			s = 2.0f * Mathf::Sqrt(1.0f + m(0, 0) - m(1, 1) - m(2, 2));
			result.x = 0.25f * s;
			result.y = (m(0, 1) + m(1, 0)) / s;
			result.z = (m(0, 2) + m(2, 0)) / s;
			result.w = (m(2, 1) - m(1, 2)) / s;
		}
		else if (m(1, 1) > m(2, 2))
		{
			s = 2.0f * Mathf::Sqrt(1.0f + m(1, 1) - m(0, 0) - m(2, 2));
			result.x = (m(0, 1) + m(1, 0)) / s;
			result.y = 0.25f * s;
			result.z = (m(1, 2) + m(2, 1)) / s;
			result.w = (m(0, 2) - m(2, 0)) / s;
		}
		else
		{
			s = 2.0f * Mathf::Sqrt(1.0f + m(2, 2) - m(0, 0) - m(1, 1));
			result.x = (m(0, 2) + m(2, 0)) / s;
			result.y = (m(1, 2) + m(2, 1)) / s;
			result.z = 0.25f * s;
			result.w = (m(1, 0) - m(0, 1)) / s;
		}
		return Normalize(result);
	}

	/**
	* �N�H�[�^�j�I������]�s��ɕϊ�
	*/
	Matrix3x3 Quaternion::QuaternionToRotationMatrix(const Quaternion& q)
	{
		Matrix3x3 rotationMatrix;
		rotationMatrix(0, 0) = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		rotationMatrix(1, 0) = 2.0f * (q.x * q.y - q.z * q.w);
		rotationMatrix(2, 0) = 2.0f * (q.x * q.z + q.y * q.w);

		rotationMatrix(0, 1) = 2.0f * (q.x * q.y + q.z * q.w);
		rotationMatrix(1, 1) = 1.0f - 2.0f * (q.x * q.x + q.z * q.z);
		rotationMatrix(2, 1) = 2.0f * (q.y * q.z - q.x * q.w);

		rotationMatrix(0, 2) = 2.0f * (q.x * q.z - q.y * q.w);
		rotationMatrix(1, 2) = 2.0f * (q.y * q.z + q.x * q.w);
		rotationMatrix(2, 2) = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);

		return rotationMatrix;
	}

	/**
	* �N�H�[�^�j�I���̐��K�����v�Z����
	*/
	Quaternion Quaternion::Normalize(const Quaternion& q)
	{
		float magnitude = Mathf::Sqrt(Dot(q, q));
		if (magnitude > 0.0f)
		{
			return Quaternion(
				q.x / magnitude,
				q.y / magnitude,
				q.z / magnitude,
				q.w / magnitude);
		}
		return Quaternion::identity;
	}

	/**
	* �N�H�[�^�j�I���̋t�����v�Z
	*/
	Quaternion Quaternion::Inverse(const Quaternion& q)
	{
		return Quaternion(-q.x, -q.y, -q.z, q.w);
	}

	/**
	* axis�̎����angle(�x���@)��]����N�H�[�^�j�I����Ԃ�
	*
	* @param axis	��]���鎲
	* @param angle	��]����p�x(�x���@)
	*
	* @return ��]�����N�H�[�^�j�I��
	*/
	Quaternion Quaternion::AngleAxis(const Vector3& axis, float angle)
	{
		float halfAngle = Mathf::DegToRad(angle) * 0.5f;
		Vector3 normalAxis = Vector3::Normalize(axis);
		Quaternion result(
			Mathf::Sin(halfAngle) * normalAxis.x,
			Mathf::Sin(halfAngle) * normalAxis.y,
			Mathf::Sin(halfAngle) * normalAxis.z,
			Mathf::Cos(halfAngle)
		);
		return result;
	}

	/**
	* a��b�̊p�x�𒲂ׂ�
	*
	* @return a��b�̊p�x(�x���@)
	*/
	float Quaternion::Angle(const Quaternion& a, const Quaternion& b)
	{
		// ���ς̐�Βl���擾
		float dot = Mathf::Abs(Quaternion::Dot(a, b));
		return Mathf::RadToDeg(Mathf::Acos(dot) * 2.0f);
	}

	/**
	* �N�H�[�^�j�I���̓��ς��v�Z
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
	Quaternion Quaternion::LookRotation(const Vector3& forward, const Vector3& upward)
	{
		// �O���x�N�g���̐��K��
		Vector3 forwardNormalized = Vector3::Normalize(forward);

		// �E���x�N�g�����v�Z
		Vector3 right = Vector3::Normalize(Vector3::Cross(upward, forwardNormalized));

		// ����x�N�g�����Čv�Z
		Vector3 upwardNormalized = Vector3::Normalize(Vector3::Cross(forwardNormalized, right));

		// ��]�s����쐬
		Matrix3x3 rot(right, upwardNormalized, forwardNormalized);

		float tmp = (rot(0, 0) + rot(1, 1) + rot(2, 2));
		Quaternion result = identity;
		if (tmp > 0)
		{
			float num = 0.5f / Mathf::Sqrt(tmp + 1.0f);
			result.x = (rot(1, 2) - rot(2, 1)) * num;
			result.y = (rot(2, 0) - rot(0, 2)) * num;
			result.z = (rot(0, 1) - rot(1, 0)) * num;
			result.w = 0.25f / num;
			return result;
		}
		else if ((rot(0, 0) >= rot(1, 1)) && (rot(0, 0) >= rot(2, 2)))
		{
			float num = 2.0f * Mathf::Sqrt(((1.0f + rot(0, 0)) - rot(1, 1)) - rot(2, 2));
			result.x = 0.25f * num;
			result.y = (rot(0, 1) + rot(1, 0)) / num;
			result.z = (rot(0, 2) + rot(2, 0)) / num;
			result.w = (rot(1, 2) - rot(2, 1)) / num;
			return result;
		}
		else if (rot(1, 1) > rot(2, 2))
		{
			float num = 2.0f * Mathf::Sqrt(((1.0f + rot(1, 1)) - rot(0, 0)) - rot(2, 2));
			result.x = (rot(1, 0) + rot(0, 1)) / num;
			result.y = 0.25f * num;
			result.z = (rot(2, 1) + rot(1, 2)) / num;
			result.w = (rot(2, 0) - rot(0, 2)) / num;
			return result;
		}
		else
		{
			float num = 2.0f * Mathf::Sqrt(((1.0f + rot(2, 2)) - rot(0, 0)) - rot(1, 1));
			result.x = (rot(2, 0) + rot(0, 2)) / num;
			result.y = (rot(2, 1) + rot(1, 2)) / num;
			result.z = 0.25f * num;
			result.w = (rot(0, 1) - rot(1, 0)) / num;
			return result;
		}
		return result;
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
		return LookRotation(foward, Vector3::up);
	}

	/**
	* Quaternion��float�̏�Z
	*/
	Quaternion operator*(const Quaternion& q, float f)
	{
		return Quaternion(q.x * f, q.y * f, q.z * f, q.w * f);
	}
	Quaternion operator*(float f, const Quaternion& q)
	{
		return q * f;
	}

	/**
	* Quaternio���m�̉��Z
	*/
	Quaternion operator+(const Quaternion& a, const Quaternion& b)
	{
		return Quaternion(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
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
		Quaternion result = Quaternion::identity;

		float tmp = Mathf::Clamp01(t);
		Quaternion tmpA = Normalize(a);
		Quaternion tmpB = Normalize(b);

		// �N�H�[�^�j�I���̓���
		float dotProduct = Dot(a, b);

		// �����t�����Ȃ畄���𔽓]
		if (dotProduct < 0.0f)
		{
			tmpB = Quaternion(-tmpB.x, -tmpB.y, -tmpB.z, -tmpB.w);
			dotProduct = -dotProduct;
		}

		// dotproduct��1�ɋ߂��ꍇ�͉��Z�덷���o��̂Ő��`�ۊǂ���
		const float threshold = 0.9995f;
		if (dotProduct > threshold)
		{
			result = Quaternion{
			   tmpA.x + t * (tmpB.x - tmpA.x),
			   tmpA.y + t * (tmpB.y - tmpA.y),
			   tmpA.z + t * (tmpB.z - tmpA.z),
			   tmpA.w + t * (tmpB.w - tmpA.w)
			};
			return Normalize(result);
		}
		// �T�C���ƃA�[�N�R�T�C�����v�Z
		float theta_0 = Mathf::Acos(dotProduct);
		float theta = theta_0 * t;
		float sinTheta = Mathf::Sin(theta);
		float sinTheta_0 = Mathf::Sin(theta_0);

		// ��Ԃ̌v�Z
		float s0 = Mathf::Cos(theta) - dotProduct * sinTheta / sinTheta_0;
		float s1 = sinTheta / sinTheta_0;
		result = s0 * tmpA + s1 * tmpB;

		return result;
	}

	/**
	* Quaternion���m�̏�Z
	*/
	Quaternion operator*(const Quaternion& a, const Quaternion& b)
	{
		return Quaternion(
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,
			a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w,
			a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z
		);
	}

	/**
	* Quaternion��Vector3�̏�Z
	*/
	Vector3 operator*(const Quaternion& q, const Vector3& v)
	{
		float num = q.x * 2.0f;
		float num2 = q.y * 2.0f;
		float num3 = q.z * 2.0f;
		float num4 = q.x * num;
		float num5 = q.y * num2;
		float num6 = q.z * num3;
		float num7 = q.x * num2;
		float num8 = q.x * num3;
		float num9 = q.y * num3;
		float num10 = q.w * num;
		float num11 = q.w * num2;
		float num12 = q.w * num3;

		return Vector3(
			(1.0f - (num5 + num6)) * v.x + (num7 - num12) * v.y + (num8 + num11) * v.z,
			(num7 + num12) * v.x + (1.0f - (num4 + num6)) * v.y + (num9 - num10) * v.z,
			(num8 - num11) * v.x + (num9 + num10) * v.y + (1.0f - (num4 + num5)) * v.z
		);
	}
}