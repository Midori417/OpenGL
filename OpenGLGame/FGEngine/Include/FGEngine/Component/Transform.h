/**
* @file Transform.h
*/
#ifndef FGENGINE_TRANSFORM_H_INCLUDED
#define FGENGINE_TRANSFORM_H_INCLUDED
#include "Component.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Quaternion.h"
#include "FGEngine/Math/Matrix3x3.h"
#include "FGEngine/Math/Matrix4x4.h"

namespace FGEngine
{
	/**
	* �I�u�W�F�N�g�̈ʒu�A��]�A�g��k���������R���|�[�l���g
	*/
	class Transform : public Component
	{
		friend Scene;
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Transform() = default;
		virtual ~Transform() = default;

	public:	// �����x�N�g���̎擾

		/**
		* �O���x�N�g�����擾
		*/
		Vector3 Forward() const;

		/**
		* �E���x�N�g�����擾
		*/
		Vector3	Right() const;

		/**
		* ����x�N�g�����擾
		*/
		Vector3 Up() const;

	public:

		/**
		* �ʒu�Ɖ�]��ݒ肷��
		* 
		* @param pos �ʒu
		* @param rot ��]
		*/
		void SetPositionAndRotation(const Vector3& pos, const Quaternion& rot);

		/**
		* translation�̕����Ƌ����Ɉړ�����
		* 
		* @param translation �ړ���������Ƌ���
		*/
		void Translate(const Vector3& translation);

		/**
		* �I�C���[�p���擾
		*/
		Vector3 GetEulerAngle() const;

		/**
		* ���݂̊p�x����euler���Z����
		* 
		* @param euler ��]��(�I�C���[�p)
		*/
		void Rotate(const Vector3& eulers);

		/**
		* �Ώۂ�Transform��ݒ肵�A���̕����֌���
		* 
		* @param target		������ΏۃI�u�W�F�N�g��Transform
		* @param worldUp	����x�N�g��
		*/
		void LookAt(const Transform* target, const Vector3& worldUp = Vector3::up);
		void LookAt(const TransformPtr target, const Vector3& worldUp = Vector3::up);

	public:		// �e�q

		/**
		* �eTransform��ݒ肷��
		* 
		* @param parent �ݒ肷��e��Transform
		*/
		void SetParent(const TransformPtr parent);

		/**
		* �eTransform���擾����
		*/
		TransformPtr GetParent() const;

		/**
		* �q�I�u�W�F�N�g�̐����擾����
		*/
		size_t GetChildrenCount() const;

		/**
		* index����q��Transform���擾����
		* 
		* @param �qTransform��index
		*/
		TransformPtr GetChildren(size_t index) const;

		/**
		* �S�Ă̎q�I�u�W�F�N�g��؂藣��
		*/
		void AllChildrenPurge();

	public:	// ���W�s��

		/**
		* ���[�J�����W�ϊ��s����擾
		*/
		Matrix4x4 GetLocalTransformMatrix() const;

		/**
		* ���[���h���W�s����擾
		*/
		Matrix4x4 GetWorldTransformMatrix() const;

		/**
		* �@���s����擾
		*/
		Matrix3x3 GetNormalMatrix() const;

	private:

		/**
		* ���[�J�����W�ϊ��s����X�V
		*/
		void LocalTransformUpdate();

	public:

		// �ʒu
		Vector3 position = Vector3::zero;

		// ��]
		Quaternion rotation = Quaternion::identity;

		// �g��k��
		Vector3 scale = Vector3::one;

	private:

		// ���[�J�����W�s��
		Matrix4x4 localTransformMatrix = Matrix4x4(1);

		// ���[���h���W�s��
		Matrix4x4 worldTransformMatrix = Matrix4x4(1);

		// �@���ϊ��s��
		Matrix3x3 normalMatrix = Matrix3x3(1);

		// �e�I�u�W�F�N�g��Transfoom
		std::weak_ptr<Transform> parent;

		// �q�I�u�W�F�N�g��Transform
		std::vector<std::weak_ptr<Transform>> childrens;
	};
}

#endif // !FGENGINE_TRANSFORM_H_INCLUDED
