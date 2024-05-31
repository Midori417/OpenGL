/**
* @file Matrix4x4.h
*/
#ifndef FGENGINE_MATRIX4X4_H_INCLUDED
#define FGENGINE_MATRIX4X4_H_INCLUDED
#include "MatrixFrd.h"
#include "Vector4.h"

namespace FGEngine
{

	/**
	* 4x4�s��
	*/
	struct Matrix4x4
	{
	public:

		// �f�t�H���g�R���X�g���N�^
		Matrix4x4() = default;

		// 4��Vector4����Matrix4x4���\������R���X�g���N�^
		explicit Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);

		// 1��float��Ίp���ɃR�s�[����R���X�g���N�^
		explicit Matrix4x4(float f);

		// Matrix3x3����Matrix4x4�ɕϊ�����R���X�g���N�^
		explicit Matrix4x4(const Matrix3x3& m);

		/**
		* ���s�ړ��s����쐬
		* 
		* @param position �ʒu
		*/
		static Matrix4x4 Translate(const Vector3& position);

		/**
		*  �g��k���s����쐬
		* 
		* @param scale �X�P�[��
		*/
		static Matrix4x4 Scale(const Vector3& scale);

		/**
		* X���̉�]�s����쐬
		* 
		* @param angle x�̊p�x
		*/
		static Matrix4x4 RotateX(float angle);

		/**
		* Y���̉�]�s����쐬
		* 
		* @param angle y�̊p�x
		*/
		static Matrix4x4 RotateY(float angle);

		/**
		* Z���̉�]�s����쐬
		* 
		* @param angle z�̊p�x
		*/
		static Matrix4x4 RotateZ(float angle);

		static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);

		/**
		* �r���[�s����쐬����
		*
		* @param eye		�n�_�̍��W
		* @param target		�����_�̍��W
		* @param up			�n�_�̏�������������̃x�N�g��
		*
		* @return eye, target, up����쐬�����r���[�s��
		*/
		static Matrix4x4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

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
		static Matrix4x4 Orthogonal(float left, float right, float bottom, float top, float zNear, float zFar);

		/**
		* ���W�ϊ��s��𕽍s�ړ��A�g�嗦�A��]�s��̊e�����ɕ�������
		*
		* @param[in] transform	�������̍��W�ϊ��s��
		* @param[out] translate ���s�ړ��̊i�[��ƂȂ�ϐ�
		* @param[out] scale		�g�嗦�̊i�[��ƂȂ�ϐ�
		* @param[out] rotation	��]�s��̊i�[��ƂȂ�ϐ�
		*/
		static void Decompose(const Matrix4x4& transform, Vector3& translate, Vector3& scale, Matrix3x3& rotation);

		/**
		* ���W�ϊ��s�񂩂�g�嗦�𒊏o
		* 
		* @param transform	���o���̍��W�ϊ��s��
		* 
		* @return ���o�����g�嗦��
		*/
		static Vector3 ExtractScale(const Matrix4x4& transform);

		// �Y�������Z�q
		Vector4& operator[](size_t i)
		{
			return data[i];
		}
		const Vector4& operator[](size_t i) const
		{
			return data[i];
		}

	public:

		Vector4 data[4];

	};

	/**
	* Matrix3x3��Vector3�̏�Z
	*/
	Vector4 operator*(const Matrix4x4& m, const Vector4& v);

	/**
	* Matrix3x3���m�̏�Z
	*/
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b);
}
#endif // !MATRIX4X4_H_INCLUDED