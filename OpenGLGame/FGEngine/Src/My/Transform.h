/**
* @file Transform.h
*/
#ifndef FGENGINE_TRANSFORM_H_INCLUDED
#define FGENGINE_TRANSFORM_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* �I�u�W�F�N�g�̈ʒu�A��]�A�g��k���������R���|�[�l���g
	*/
	class Transform : public Component
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Transform() = default;
		virtual ~Transform() = default;

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
		void LookAt(const TransformPtr target, const Vector3& worldUp = Vector3::up);

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



	public:

		// �ʒu
		Vector3 position = Vector3::zero;

		// ��]
		Quaternion rotation = Quaternion::identity;

		// �g��k��
		Vector3 scale = Vector3::one;

	private:

		// ���[���h���W���烍�[�J�����W�ɕϊ������s��
		Matrix4x4 worldToLocalMatrix = Matrix4x4(1);

		// �e�I�u�W�F�N�g��Transfoom
		std::weak_ptr<Transform> parent;

		// �q�I�u�W�F�N�g��Transform
		std::vector<std::weak_ptr<Transform>> childrens;
	};
}

#endif // !FGENGINE_TRANSFORM_H_INCLUDED
