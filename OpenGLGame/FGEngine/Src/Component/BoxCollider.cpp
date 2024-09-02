/**
* @file BoxCollider.cpp
*/
#include "FGEngine/Component/BoxCollider.h"
#include "FGEngine/Math/Math.h"

namespace FGEngine
{
	/**
	* �R���W�����^�C�v���擾
	*/
	PhysicsSystem::CollisionType BoxCollider::GetType() const
	{
		return PhysicsSystem::CollisionType::Box;
	}

	/**
	* �}�`���擾
	*/
	const PhysicsSystem::Box& BoxCollider::GetShape() const
	{
		return box;
	}
	
	/**
	* ���W��ύX����
	* 
	* @param translate �ړ���
	*/
	void BoxCollider::AddPosition(const Vector3& translate)
	{
		center += translate;
	}

	/**
	* ���W�ϊ������R���C�_�[���擾����
	*
	* @param transform �ϊ�������W�ϊ��s��
	*
	* @return �ϊ������R���C�_�[�R���|�[�l���g
	*/
	ColliderPtr BoxCollider::GetTransformedCollider(const Matrix4x4& transform) const
	{
		// ���W�ϊ��s��𕪉�
		Vector3 translate; // ���g�p
		Vector3 scale;
		Matrix3x3 rotation;
		Matrix4x4::Decompose(transform, translate, scale, rotation);

		// ���W�ϊ������R�s�[���쐬
		auto p = std::make_shared<BoxCollider>();
		p->box.position = Vector3(transform * Vector4(center, 1));
		for (int i = 0; i < 3; ++i)
		{
			p->box.axis[i] = rotation * box.axis[i];	// ���x�N�g��
			p->box.scale[i] = size[i] * scale[i];	// �g�嗦
		}
		return p;
	}

	/**
	* Box�R���C�_�[�̃N���[�����쐬
	*/
	ComponentPtr BoxCollider::Clone() const
	{
		BoxColliderPtr p = std::make_shared<BoxCollider>();

		// ���N���X�̕ϐ����R�s�[
		p->enabled = this->enabled;
		p->isTrigger = this->isTrigger;

		p->center = this->center;
		p->size = this->size;
		p->box = this->box;

		return p;
	}
}