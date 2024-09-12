/**
* @file AabbCollider.cpp
*/
#include "FGEngine/Component/AabbCollider.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Matrix4x4.h"

namespace FGEngine
{
	/**
	* �R���W�����^�C�v���擾
	*/
	CollisionType AabbCollider::GetType() const
	{
		return CollisionType::AABB;
	}

	/**
	* �}�`���擾
	*/
	const AABB& AabbCollider::GetShape() const
	{
		return aabb;
	}

	/**
	* ���W��ύX����
	*
	* @param translate �ړ���
	*/
	void AabbCollider::AddPosition(const Vector3& translate)
	{
		min += translate;
		max += translate;
	}

	ColliderPtr AabbCollider::GetTransformedCollider(const Matrix4x4& transform) const
	{
		// ���W�ϊ������R�s�[���쐬
		auto p = std::make_shared<AabbCollider>();
		p->aabb.min = Vector3(transform * Vector4(min, 1));
		p->aabb.max = Vector3(transform * Vector4(max, 1));

		// min�̂ق����傫�����������ւ���
		for (int i = 0; i < 3; ++i)
		{
			if (p->aabb.min[i] > p->aabb.max[i])
			{
				const float tmp = p->aabb.min[i];
				p->aabb.min[i] = p->aabb.max[i];
				p->aabb.max[i] = tmp;
			}
		}
		return p;
	}

	/**
	* Aabb�R���C�_�[�̃N���[�����쐬
	*/
	ComponentPtr AabbCollider::Clone() const
	{
		AabbColliderPtr p = std::make_shared<AabbCollider>();

		// ���N���X�̕ϐ����R�s�[
		p->enabled = this->enabled;
		p->isTrigger = this->isTrigger;

		p->min = this->min;
		p->max = this->max;
		p->aabb = this->aabb;

		return ComponentPtr();
	}

}