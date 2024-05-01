/**
* @file SphereCollider.h
*/
#ifndef SPHERECOLLIDER_H_INCLUDED
#define SPHERECOLLIDER_H_INCLUDED

#include "Collider.h"
#include "Collision.h"

/**
* ���̃R���C�_�[
*/
class SphereCollider : public Collider
{
public:

	SphereCollider() = default;
	virtual ~SphereCollider() = default;

	// �}�`�̎��
	Type GetType() const override {
		return Type::Sphere;
	}

	// �}�`��ύX����
	void AddPosition(const Vector3& translate) override {
		sphere.position += translate;
	}

	ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const override {
		// ���S���W�����W�ϊ�����
		auto p = std::make_shared<SphereCollider>();
		p->sphere.position = Vector3(transform * Vector4(sphere.position, 1));

		// ���̂̊g�嗦�̓I�u�W�F�N�g��XYZ�g�嗦�̂����ő�̂��̂Ƃ���(Uinty�)
		const Vector3 scale = ExtractScale(transform);
		const float maxScale = std::max({ scale.x,scale.y,scale.z });
		p->sphere.radius = sphere.radius * maxScale;
		return p;
	}

	// �}�`���擾����
	const Sphere& GetShape() const {
		return sphere;
	}

public:

	Sphere sphere = { Vector3(0), 1 };	// �}�`(����)
};
using SphereColliderPtr = std::shared_ptr<SphereCollider>;
#endif // !SPHERECOLLIDER_H_INCLUDED
