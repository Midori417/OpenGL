/**
* @file Quaternion.h
*/
#ifndef FGENGINE_QUATERNION_H_INCLUDED
#define FGENGINE_QUATERNION_H_INCLUDED
#include "MathFrd.h"

namespace FGEngine
{
	/**
	* �N�H�[�^�j�I��
	*/
	struct Quaternion
	{
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Quaternion() = default;

		/**
		* 4��float����Quaternion���쐬����R���X�g���N�^
		*
		* @param x X����
		* @param y Y����
		* @param z Z����
		* @param w W����
		*/
		explicit Quaternion(float x, float y, float z, float w);

		/**
		* �I�C���[�p���N�H�[�^�j�I���ɕϊ�����
		*
		* @param x	X�̊p�x(�x���@)
		* @param y	Y�̊p�x(�x���@)
		* @param z	Z�̊p�x(�x���@)
		*/
		static Quaternion Euler(float x, float y, float z);

		/**
		* �I�C���[�p���N�H�[�^�j�I���ɕϊ�����
		*
		* @param v �I�C���[�p
		*/
		static Quaternion Euler(const Vector3& v);

		/**
		* �N�H�[�^�j�I������I�C���[�p�ɕϊ�����
		*/
		static Vector3 EulerAngle(const Quaternion& q);

		/**
		* ��]�s����N�H�[�^�j�I���ɕϊ�
		*/
		static Quaternion RotationMatrixToQuaternion(const Matrix3x3& m);

		/**
		* �N�H�[�^�j�I������]�s��ɕϊ�
		*/
		static Matrix3x3 QuaternionToRotationMatrix(const Quaternion& q);

		/**
		* �N�H�[�^�j�I���̐��K�����v�Z����
		*/
		static Quaternion Normalize(const Quaternion& q);

		/**
		* �N�H�[�^�j�I���̋t�����v�Z
		*/
		static Quaternion Inverse(const Quaternion& q);

		/**
		* axis�̎����angle(�x���@)��]����N�H�[�^�j�I����Ԃ�
		*
		* @param axis	��]���鎲
		* @param angle	��]����p�x(�x���@)
		*
		* @return ��]�����N�H�[�^�j�I��
		*/
		static Quaternion AngleAxis(const Vector3& axis, float angle);

		/**
		* a��b�̊p�x�𒲂ׂ�
		*
		* @return a��b�̊p�x(�x���@)
		*/
		static float Angle(const Quaternion& a, const Quaternion& b);

		/**
		* �N�H�[�^�j�I���̓��ς��v�Z
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
		static Quaternion LookRotation(const Vector3& forward, const Vector3& upward);

		/**
		* �O���x�N�g���Ə���x�N�g���̕����ɉ�]����
		*
		* @param foward	�O���x�N�g��
		*
		* @return �쐬�����N�H�[�^�j�I��
		*/
		static Quaternion LookRotation(const Vector3& forward);

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

	public:

		// X����
		float x;

		// Y����
		float y;

		// Z����
		float z;

		// W����
		float w;

		// �f�t�H���g�N�H�[�^�j�I��
		static const Quaternion identity;
	};

	// Quaternion���m�̏�Z
	Quaternion operator*(const Quaternion& a, const Quaternion& b);

	// Quaternion��Vector3�̏�Z
	Vector3 operator*(const Quaternion& q, const Vector3& v);
}

#endif // !FGENGINE_QUATERNION_H_INCLUDED