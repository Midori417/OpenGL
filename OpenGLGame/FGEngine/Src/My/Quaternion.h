/**
* @file Quaternion.h
*/
#ifndef FGENGINE_QUATERNION_H_INCLUDED
#define FGENGINE_QUATERNION_H_INCLUDED

#include "VectorFrd.h"
#include "MatrixFrd.h"

namespace FGEngine
{

	/**
	* �N�H�[�^�j�I��
	*/
	struct Quaternion
	{
	public:

		// �f�t�H���g�R���X�g���N�^
		Quaternion() = default;

		// 4��float����N�H�[�^�j�I�����\�z����R���X�g���N�^
		explicit Quaternion(float x, float y, float z, float w);

		/**
		* �N�H�[�^�j�I���𐳋K������
		*/
		void Normalize();

		/**
		* ���K�������N�H�[�^�j�I�����擾
		* 
		* @return ���K�������N�H�[�^�j�I��
		*/
		Quaternion Normalized() const;

		/**
		* �I�C���[�p�ɕϊ����Ď擾
		* 
		* @return �ϊ������I�C���[�p
		*/
		Vector3 EulerAngle() const;

		/**
		* �N�H�[�^�j�I���̋t�����擾
		* 
		* @param �N�H�[�^�j�I���̋t��
		*/
		Quaternion Inverse() const;

		/**
		* axis�̎����angle(�x���@)��]����N�H�[�^�j�I����Ԃ�
		* 
		* @param angle	��]����p�x(�x���@)
		* @param axis	��]���鎲
		* 
		* @return ��]�����N�H�[�^�j�I��
		*/
		static Quaternion AngleAxis(float angle, const Vector3& axis);

		/**
		* 2�̃N�H�[�^�j�I���̓��ς��v�Z����
		* 
		* @param a	�N�H�[�^�j�I��1
		* @param b	�N�H�[�^�j�I��2
		* 
		* @return a��b�̓���
		*/
		static float Dot(const Quaternion& a, const Quaternion& b);

		/**
		* �O���x�N�g���Ə���x�N�g���̕����ɉ�]����
		*
		* @param foward	�O���x�N�g��
		* @param upward ����׃x�N�g��
		*
		* @return �쐬�����N�H�[�^�j�I��
		*/
		static Quaternion LookRotation(const Vector3& foward, const Vector3& upward);

		/**
		* �O���x�N�g���Ə���x�N�g���̕����ɉ�]����
		*
		* @param foward	�O���x�N�g��
		*
		* @return �쐬�����N�H�[�^�j�I��
		*/
		static Quaternion LookRotation(const Vector3& foward);

		/**
		* �N�H�[�^�j�I�� a �� �N�H�[�^�j�I�� b �̊Ԃ������Ԃ���
		*
		* @param a ��Ԃ̊J�n�N�H�[�^�j�I��
		* @param b ��Ԃ̏I���N�H�[�^�j�I��
		* @param t ��ԃp�����[�^ (0.0 ~ 1.0 �͈̔�)
		*
		* @return ��Ԃ��ꂽ�N�H�[�^�j�I��
		*/
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);

		/**
		* �I�C���[�p����N�H�[�^�j�I���ɕϊ�
		* 
		* @param euler	�I�C���[�p
		* 
		* @return �ϊ������N�H�[�^�j�I��
		*/
		static Quaternion EulerToQuaternion(const Vector3& euler);

		/**
		* �I�C���[�p����N�H�[�^�j�I���ɕϊ�
		* 
		* @param x	X�̊p�x(�x���@)
		* @param y	Y�̊p�x(�x���@)
		* @param z	Z�̊p�x(�x���@)
		* 
		* @return �ϊ������N�H�[�^�j�I��
		*/
		static Quaternion EulerToQuaternion(float x, float y, float z);

		/**
		* �N�H�[�^�j�I������I�C���[�p�ɕϊ�
		* 
		* @param qua �N�H�[�^�j�I��
		* 
		* @return �ϊ������I�C���[�p
		*/
		static Vector3 QuaternionToEuler(const Quaternion& qua);

		/**
		* ��]�s��(Matrix3x3)����N�H�[�^�j�I���ɕϊ�
		*
		* @param rotationMatrix ��]�s��(Matrix3x3)
		*
		* @return �ϊ������N�H�[�^�j�I��
		*/
		static Quaternion RotationMatrixToQuaternion(const Matrix3x3& rotationMatrix);

		/**
		* ��]�s��(Matrix4x4)����N�H�[�^�j�I���ɕϊ�
		* 
		* @param rotationMatrix ��]�s��(Matrix4x4)
		* 
		* @return �ϊ������N�H�[�^�j�I��
		*/
		static Quaternion RotationMatrixToQuaternion(const Matrix4x4& rotationMatrix);

		/**
		* �N�H�[�^�j�I�������]�s��(Matrix3x3)�ɕϊ�
		* 
		* @param qua �N�H�[�^�j�I��
		* 
		* @return �ϊ�������]�s��(Matrix3x3)
		*/
		static Matrix3x3 QuaternionToRotationMatrix3x3(const Quaternion& qua);

		/**
		* �N�H�[�^�j�I�������]�s��(Matrix4x4)�ɕϊ�
		*
		* @param qua �N�H�[�^�j�I��
		*
		* @return �ϊ�������]�s��(Matrix4x4)
		*/
		static Matrix4x4 QuaternionToRotationMatrix4x4(const Quaternion& qua);

	public:

		// �N�H�[�^�j�I����X����
		float x;

		// �N�H�[�^�j�I����Y����
		float y;

		// �N�H�[�^�j�I����Z����
		float z;

		// �N�H�[�^�j�I����W����
		float w;

		const static Quaternion identity;

		float operator[](size_t i) const
		{
			return *(&x + i);
		}
		float& operator[](size_t i) 
		{
			return *(&x + i);
		}

	};

	// �N�H�[�^�j�I�����m�̏�Z
	Quaternion operator*(const Quaternion& a, const Quaternion& b);

	// �N�H�[�^�j�I���ƃx�N�g���̏�Z
	Vector3 operator*(const Quaternion& qua, const Vector3& v);

	// �N�H�[�^�j�I���̔�r���Z
	bool operator==(const Quaternion& a, const Quaternion& b);

}
#endif // !QUATERNION_H_INCLUDED
