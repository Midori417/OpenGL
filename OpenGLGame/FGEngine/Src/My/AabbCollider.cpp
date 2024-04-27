/**
* @file AabbCollider.cpp
*/
#include "AabbCollider.h"

namespace FGEngine
{
	/**
	* �R���C�_�[�̃^�C�v���擾
	*/
	ColliderType AabbCollider::GetType() const
	{
		return ColliderType::AABB;
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

}