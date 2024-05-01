/**
* @file AabbCollider.h
*/
#ifndef AABBCOLLIDER_H_INCLUDED
#define AABBCOLLIDER_H_INCLUDED

#include "Collider.h"
#include "Collision.h"


/**
* AAB�R���C�_�[
*/
class AabbCollider : public Collider
{
public:

	AabbCollider() = default;
	virtual ~AabbCollider() = default;

	// �}�`�̎��
	Type GetType() const override
	{
		return Type::AABB;
	}

	// ���W��ύX����
	void AddPosition(const Vector3& translate) override
	{
		aabb.min += translate;
		aabb.max += translate;
	}

	// ���W�ϊ������R���C�_�[���擾����
	// ��]�p�x��90���P�ʂŎw�肷�邱�ƁA����ȊO�̊p�x�ł͐������������肪�s���Ȃ�
	ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const override
	{
		// ���W�ϊ������R�s�[���쐬
		auto p = std::make_shared<AabbCollider>();
		p->aabb.min = Vector3(transform * Vector4(aabb.min, 1));
		p->aabb.max = Vector3(transform * Vector4(aabb.max, 1));

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

	// �}�`���擾����
	const AABB& GetShape() const
	{
		return aabb;
	}

public:

	AABB aabb = { {-1,-1,-1}, {1,1,1} };	// �}�`(�����s���E�{�b�N�X)
};
using AabbColliderPtr = std::shared_ptr<AabbCollider>;
#endif // !AABBCOLLIDER_H_INCLUDED
