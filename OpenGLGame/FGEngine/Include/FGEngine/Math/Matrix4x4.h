/**
* @file Matrix4x4.h
*/
#ifndef FGENGINE_MATRIX4X4_H_INCLUDED
#define FGENGINE_MATRIX4X4_H_INCLUDED
#include "FGEngine/UsingNames/UsingMath.h"

namespace FGEngine
{
	/**
	* 4x4�s��
	*/
	struct Matrix4x4
	{
		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		Matrix4x4() = default;

		/**
		* 4��Vector4����Matrix4x4���쐬����R���X�g���N�^
		*/
		explicit Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);

		/**
		* 1��float����Ίp���ɃR�s�[����R���X�g���N�^
		*/
		explicit Matrix4x4(float f);

		/*
		* Matrix3x3����Matrix4x4���쐬����R���X�g���N�^
		*/
		explicit Matrix4x4(const Matrix3x3& m);

		/**
		* �s��̍s���擾����
		*
		* @param index �s�̔ԍ�
		*/
		Vector4 GetRow(size_t index) const;

		/**
		* �s��̍s��ݒ肷��
		*
		* @param index	�s�̔ԍ�
		* @param v		�ݒ肷��Vector3
		*/
		void SetRow(size_t index, const Vector4& v);

		/**
		* �s��̗���擾����
		*
		* @param index ��̔ԍ�
		*/
		Vector4 GerColumn(size_t index) const;

		/**
		* �s��̗��ݒ肷��
		*
		* @param index	��̔ԍ�
		* @param v		�ݒ肷��Vector3
		*/
		void SetColumn(size_t index, const Vector4& v);

		/**
		* �t�s����쐬[
		*
		* @param matrix �t�s��ɂ������s��
		*/
		static Matrix4x4 Invers(const Matrix4x4& matrix);

		/**
		* ���s�ړ��s����쐬
		*
		* @param position �ʒu
		*/
		static Matrix4x4 Translate(const Vector3& position);

		/**
		* �g��k���s����쐬
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
		* ���W�ϊ��s�񂩂畽�s�ړ��𒊏o
		*
		* @param transform ���o���̍��W�ϊ��s��
		*
		* @return ���o�������s�ړ�
		*/
		static Vector3 ExtractTranslate(const Matrix4x4& transform);

		/**
		* ���W�ϊ��s�񂩂�g�嗦�𒊏o
		*
		* @param transform	���o���̍��W�ϊ��s��
		*
		* @return ���o�����g�嗦
		*/
		static Vector3 ExtractScale(const Matrix4x4& transform);

		/**
		* ���W�ϊ��s�񂩂��]�s��𒊏o
		* 
		* @param transform	���o���̍��W�ϊ��s��
		*
		* @return ���o������]�s��
		*/
		static Matrix3x3 ExtractRotation(const Matrix4x4& transform);

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

		static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);

	public:

		float num00;
		float num01;
		float num02;
		float num03;

		float num10;
		float num11;
		float num12;
		float num13;

		float num20;
		float num21;
		float num22;
		float num23;

		float num30;
		float num31;
		float num32;
		float num33;

		// �P���s��
		const static Matrix4x4 identity;

		// �S�Ă̗v�f��0�̍s��
		const static Matrix4x4 zero;

		/**
		* �Q�Ƃ�Ԃ��Y�������Z�q
		*
		* @param row	�s�̃C���f�b�N�X
		* @param column	��̃C���f�b�N�X
		*/
		const float& operator()(size_t row, size_t column) const;
		float& operator()(size_t row, size_t column);
	};

	// Matrix4x4��Vector4�̏�Z
	Vector4 operator*(const Matrix4x4& m, const Vector4& v);

	// Matrix3x3���m�̏�Z
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b);

}

#endif // !FGENGINE_MATRIX4X4_H_INCLUDED