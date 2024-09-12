/**
* @file SphereCollider.cpp
*/
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Math/Mathf.h"
#include "FGEngine/Math/Math.h"

namespace FGEngine
{
	/**
	* コリジョンタイプを取得
	*/
	CollisionType SphereCollider::GetType() const
	{
		return CollisionType::Sphere;
	}

	/**
	* 図形を取得
	*/
	const Sphere& SphereCollider::GetShape() const
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

	ComponentPtr SphereCollider::Clone() const
	{
		SphereColliderPtr p = std::make_shared<SphereCollider>();

		// 基底クラスの変数をコピー
		p->enabled = this->enabled;
		p->isTrigger = this->isTrigger;

		p->ceneter = this->ceneter;
		p->radius = this->radius;
		p->sphere = this->sphere;

		return p;
	}

}