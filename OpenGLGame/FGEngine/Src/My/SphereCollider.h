/**
* @file SphereCollider.h
*/
#ifndef SPHERECOLLIDER_H_INCLUDED
#define SPHERECOLLIDER_H_INCLUDED

#include "Collider.h"
#include "Collision.h"

/**
* 球体コライダー
*/
class SphereCollider : public Collider
{
public:

	SphereCollider() = default;
	virtual ~SphereCollider() = default;

	// 図形の種類
	Type GetType() const override {
		return Type::Sphere;
	}

	// 図形を変更する
	void AddPosition(const Vector3& translate) override {
		sphere.position += translate;
	}

	ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const override {
		// 中心座標を座標変換する
		auto p = std::make_shared<SphereCollider>();
		p->sphere.position = Vector3(transform * Vector4(sphere.position, 1));

		// 球体の拡大率はオブジェクトのXYZ拡大率のうち最大のものとする(Uinty基準)
		const Vector3 scale = ExtractScale(transform);
		const float maxScale = std::max({ scale.x,scale.y,scale.z });
		p->sphere.radius = sphere.radius * maxScale;
		return p;
	}

	// 図形を取得する
	const Sphere& GetShape() const {
		return sphere;
	}

public:

	Sphere sphere = { Vector3(0), 1 };	// 図形(球体)
};
using SphereColliderPtr = std::shared_ptr<SphereCollider>;
#endif // !SPHERECOLLIDER_H_INCLUDED
