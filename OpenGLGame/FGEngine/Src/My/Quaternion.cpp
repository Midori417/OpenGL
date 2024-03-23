/**
* @file Quaternion.cpp
*/
#include "Quaternion.h"
#include "VecMath.h"

namespace FGEngine
{

	// �X�^�e�B�b�N�ϐ��̏�����
	const Quaternion Quaternion::identity = Quaternion(0, 0, 0, 1);

	/**
	* axis����angle�̃N�H�[�^�j�I����Ԃ�
	*
	* @param axis ��]���������C�ӎ�
	* @parma angle ��]������p�x
	*
	* @reutrn axis����angle�̃N�H�[�^�j�I��
	*/
	Quaternion Quaternion::AngleAxis(float angle, const Vector3& axis)
	{
		float halfAngle = angle * 0.5f;
		Vector3 normalAxis = axis.normalized();
		Quaternion result(
			Mathf::Sin(halfAngle) * normalAxis.x,
			Mathf::Sin(halfAngle) * normalAxis.y,
			Mathf::Sin(halfAngle) * normalAxis.z,
			Mathf::Cos(halfAngle)
		);
		return result;
	}
	/**
	* a��b�̃N�H�[�^�j�I���̓��ς�Ԃ�
	*
	* @param a �v�Z�Ώۂ���1
	* @param b �v�Z�Ώۂ���2
	*
	* @return a��b�̓���
	*/
	float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
	{
		return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	}
	/**
	* �I�C���[�p����N�H�[�^�j�I���ɕϊ�
	*/
	Quaternion Quaternion::Euler(float x, float y, float z)
	{
		Quaternion result = Quaternion::identity;
		float tx = x * Mathf::Deg2Rad;
		float ty = y * Mathf::Deg2Rad;
		float tz = z * Mathf::Deg2Rad;
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
		return result.normalized();
	}
	/**
	* �I�C���[�p����N�H�[�^�j�I���ɕϊ����ĕԂ�
	*
	* @param v �I�C���[�p
	*
	* @return �ϊ������N�H�[�^�j�I��
	*/
	Quaternion Quaternion::Euler(const Vector3& v)
	{
		return Euler(v.x, v.y, v.z);
	}
	/**
	* �w�肳�ꂽforward��upward�̕����ɉ�]����
	*
	* @param foward �O���x�N�g��
	* @param upward ����x�N�g��
	*
	* @return foward��upward�̕����̃N�H�[�^�j�I��
	*/
	Quaternion Quaternion::LookRotation(const Vector3& forward, const Vector3& upward)
	{
		Vector3 forwardNormalized = -forward.normalized();
		Vector3 right = Vector3::Cross(upward, forwardNormalized).normalized();
		Vector3 upAdjusted = Vector3::Cross(forwardNormalized, right).normalized();
		float trace = right.x + upAdjusted.y + forwardNormalized.z;
		Quaternion result = identity;
		if (trace > 0) {
			float s = 0.5f / Mathf::Sqrt(trace + 1.0f);
			result = Quaternion(
				(upAdjusted.z - forwardNormalized.y) * s,
				(forwardNormalized.x - right.z) * s,
				(right.y - upAdjusted.x) * s,
				0.25f / s
			);
		}
		else if (right.x > upAdjusted.y && right.x > forwardNormalized.z) {
			float s = 2.0f * Mathf::Sqrt(1.0f + right.x - upAdjusted.y - forwardNormalized.z);
			result = Quaternion(
				0.25f * s,
				(upAdjusted.x + right.y) / s,
				(forwardNormalized.x + right.z) / s,
				(upAdjusted.z - forwardNormalized.y) / s
			);
		}
		else if (upAdjusted.y > forwardNormalized.z) {
			float s = 2.0f * Mathf::Sqrt(1.0f + upAdjusted.y - right.x - forwardNormalized.z);
			result = Quaternion(
				(upAdjusted.x + right.y) / s,
				0.25f * s,
				(forwardNormalized.y + upAdjusted.z) / s,
				(forwardNormalized.x - right.z) / s
			);
		}
		else {
			float s = 2.0f * Mathf::Sqrt(1.0f + forwardNormalized.z - right.x - upAdjusted.y);
			result = Quaternion(
				(forwardNormalized.x + right.z) / s,
				(forwardNormalized.y + upAdjusted.z) / s,
				0.25f * s,
				(right.y - upAdjusted.x) / s
			);
		}
		Quaternion tmp = result.normalized();
		return tmp;
	}
	Quaternion Quaternion::LookRotation(const Vector3& foward)
	{
		return LookRotation(foward, Vector3::up);
	}

	/**
	* �N�H�[�^�j�I���𐳋K�����ĕԂ�
	*
	* @param q ���K���������N�H�[�^�j�I��
	*
	* @return q�̐��K�������N�H�[�^�j�I��
	*/
	Quaternion Quaternion::Normalize(const Quaternion& q)
	{
		float magnitude = Mathf::Sqrt(Dot(q, q));
		if (magnitude > 0.0f) {
			return Quaternion(q.x / magnitude, q.y / magnitude, q.z / magnitude, q.w / magnitude);
		}
		else {
			return Quaternion::identity;
		}
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
	* a��b�������Ԃ���t[0�`1]�ŕԂ�
	*
	* @param a �v�Z�Ώۂ��̂P
	* @param b �v�Z�Ώۂ��̂Q
	* @param t ���[0�`1]
	*/
	Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t)
	{
		Quaternion result = Quaternion::identity;

		float tmp = Mathf::Clamp01(t);
		auto tmpA = Normalize(a);
		auto tmpB = Normalize(b);

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
	* a��b�������Ԃ���t�ŕԂ�
	*
	* @param a �v�Z�Ώۂ��̂P
	* @param b �v�Z�Ώۂ��̂Q
	* @param t ���
	*/
	Quaternion Quaternion::SlerpUnclamped(const Quaternion& a, const Quaternion& b, float t)
	{
		// �N�H�[�^�j�I���̓���
		float dotProduct = Quaternion::Dot(a, b);
		// a����b�ւ̉�]�p�x
		float theta = Mathf::Acos(dotProduct);
		// ��ԃp�����[�^�Ɋ�Â�Slerp���
		float sinTheta = Mathf::Sin(theta);
		float coeff1 = Mathf::Sin((1 - t) * theta) / sinTheta;
		float coeff2 = Mathf::Sin(t * theta) / sinTheta;
		Quaternion result = coeff1 * a + coeff2 * b;
		return result.normalized();
	}

	/**
	* ���g�̃N�H�[�^�j�I���̐��K����Ԃ�
	*/
	Quaternion Quaternion::normalized() const
	{
		return Normalize(*this);
	}

	/**
	* ���g�̃N�H�[�^�j�I���̃I�C���[�p��Ԃ�
	*/
	Vector3 Quaternion::eulerAngles() const
	{
		return QuaternionToEuler(*this);
	}

	/**
	* �N�H�[�^�j�I���̋t�����擾
	*/
	Quaternion Quaternion::inverse() const
	{
		Quaternion result = identity;
		float theta = Mathf::Sqrt(Dot(*this, *this));
		if (theta > 0.0f) {
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
	* �I�C���[�p����N�H�[�^�j�I���ɕϊ�����
	*/
	Quaternion Quaternion::EulerToQuaternion(const Vector3& v)
	{
		float cx = cosf(v.x * 0.5f);
		float sx = sinf(v.x * 0.5f);
		float cy = cosf(v.y * 0.5f);
		float sy = sinf(v.y * 0.5f);
		float cz = cosf(v.z * 0.5f);
		float sz = sinf(v.z * 0.5f);
		// �e���ɑ΂���N�H�[�^�j�I�����v�Z
		Quaternion qx(sx, 0.0, 0.0, cx);
		Quaternion qy(0.0, sy, 0.0, cy);
		Quaternion qz(0.0, 0.0, sz, cz);
		// �e���̃N�H�[�^�j�I��������
		return qx * qy * qz;
	}

	/**
	* �N�H�[�^�j�I������I�C���[�p�ɕϊ�
	*
	* @param q �ϊ��������N�H�[�^�j�I��
	*
	* @reutrn �N�H�[�^�j�I������ϊ������I�C���[�p
	*/
	Vector3 Quaternion::QuaternionToEuler(const Quaternion& q)
	{
		Vector3 axis;
		// Roll (X-axis)
		float t0 = 2.0f * (q.w * q.x + q.y * q.z);
		float t1 = 1.0f - 2.0f * (q.x * q.x + q.y * q.y);
		axis.x = Mathf::Atan2(t0, t1);
		// Pitch (Y-axis)
		float t2 = 2.0f * (q.w * q.y - q.z * q.x);
		t2 = Mathf::Min(Mathf::Max(t2, -1.0f), 1.0f); // �N���b�s���O
		axis.y = Mathf::Asin(t2);
		// Yaw (Z-axis)
		float t3 = 2.0f * (q.w * q.z + q.x * q.y);
		float t4 = 1.0f - 2.0f * (q.y * q.y + q.z * q.z);
		axis.z = Mathf::Atan2(t3, t4);
		return axis;
	}

	/**
	* �I�C���[�p�����]�s��ɕϊ����ĕԂ�
	*
	* @param eulerAngle �ϊ��������I�C���[�p
	*
	* @return �I�C���[�p����ϊ�������]�s��
	*/
	Matrix3x3 Quaternion::EulerToRotationMatrix(const Vector3& eulerAngle)
	{
		const float sinX = sinf(eulerAngle.x);
		const float cosX = cosf(eulerAngle.x);
		const float sinY = sinf(eulerAngle.y);
		const float cosY = cosf(eulerAngle.y);
		const float sinZ = sinf(eulerAngle.z);
		const float cosZ = cosf(eulerAngle.z);
		//XYZ�̉�]��
		return{
			Vector3{ (cosY * cosZ),							(cosY * sinZ),							(-sinY)},
			Vector3{ (sinX * sinY * cosZ) + (cosX * -sinZ),	(sinX * sinY * sinZ) + (cosX * cosZ),	(sinX * cosY)},
			Vector3{ (cosX * sinY * cosZ) + (sinX * sinZ),		(cosX * sinY * sinZ) + (-sinX * cosZ),	(cosX * cosY)}
		};
	}
	/**
	* ��]�s�񂩂�N�H�[�^�j�I���ɕϊ����ĕԂ�
	*�@
	* @param rotationMatrix �ϊ���������]�s��
	*
	*/
	Quaternion Quaternion::RotationMatrixToQuaternio(const Matrix3x3& rotationMatrix)
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
		return result.normalized();
	}

	/**
	* �N�H�[�^�j�I������3x3�s��ɕϊ�
	*
	* @param qua �ϊ�����N�H�[�^�j�I��
	*
	* @return 3x3�s��ɕϊ�����qua
	*/
	Matrix3x3 Quaternion::Matrix3x3Cast(const Quaternion& qua)
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
	* �N�H�[�^�j�I������4x4�s��ɕϊ�
	*
	* @param qua �ϊ�����N�H�[�^�j�I��
	*
	* @return 4x4�s��ɕϊ�����qua
	*/
	Matrix4x4 Quaternion::Matrix4x4Cast(const Quaternion& qua)
	{
		return Matrix4x4(Matrix3x3Cast(qua));
	}

	//=======================================
	//
	//  Operator
	//
	//=======================================
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
	* �N�H�[�^�j�I���ƃx�N�g���̏�Z
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
		Vector3 result = v;
		result.x = (1.0f - (num5 + num6)) * v.x + (num7 - num12) * v.y + (num8 + num11) * v.z;
		result.y = (num7 + num12) * v.x + (1.0f - (num4 + num6)) * v.y + (num9 - num10) * v.z;
		result.z = (num8 - num11) * v.x + (num9 + num10) * v.y + (1.0f - (num4 + num5)) * v.z;
		return result;
	}
	/**
	* ��̃N�H�[�^�j�I������v���邩�ǂ���
	*/
	bool operator==(const Quaternion& a, const Quaternion& b)
	{
		return (a.x == b.x) && (a.y == b.y) && (a.z == b.z) && (a.w == b.w);
	}
}