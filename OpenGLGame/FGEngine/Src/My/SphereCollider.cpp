/**
* @file SphereCollider.cpp
*/
#include "SphereCollider.h"
#include "Mathf.h"

namespace FGEngine
{
	/**
	* コリジョンタイプを取得
	*/
	PhysicsSystem::CollisionType SphereCollider::GetType() const
	{
		return PhysicsSystem::CollisionType::Sphere;
	}

	/**
	* 図形を取得
	*/
	const PhysicsSystem::Sphere& SphereCollider::GetShape() const
	{
		return sphere;
	}

	/**
	* 図形を変更する
	*
	* @param translate 移動量
	*/
	void SphereCollider::AddPosition(const Vector3& translate)
	{
		ceneter += translate;
	}

	/**
	* 座標変換したコライダーを取得する
	*
	* @param transform 変換する座標変換行列
	*
	* @return 変換したコライダーコンポーネント
	*/
	ColliderPtr SphereCollider::GetTransformedCollider(const Matrix4x4& transform) const
	{
		// 中心座標を座標変換する
		auto p = std::make_shared<SphereCollider>();
		p->sphere.position = Vector3(transform * Vector4(ceneter, 1));

		// 球体の拡大率はオブジェクトのXYZ拡大率のうち最大のものとする(Uinty基準)
		const Vector3 scale = Matrix4x4::ExtractScale(transform);
		const float maxScale = Mathf::Max(Mathf::Max(scale.x,scale.y),scale.z);
		p->sphere.radius = radius * maxScale;
		return p;
	}

}