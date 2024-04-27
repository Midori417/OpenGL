/**
* @file AabbCollider.cpp
*/
#include "AabbCollider.h"

namespace FGEngine
{
	/**
	* コライダーのタイプを取得
	*/
	ColliderType AabbCollider::GetType() const
	{
		return ColliderType::AABB;
	}

	/**
	* 図形を取得
	*/
	const AABB& AabbCollider::GetShape() const
	{
		return aabb;
	}

	/**
	* 座標を変更する
	*
	* @param translate 移動量
	*/
	void AabbCollider::AddPosition(const Vector3& translate)
	{
		min += translate;
		max += translate;
	}

	ColliderPtr AabbCollider::GetTransformedCollider(const Matrix4x4& transform) const
	{
		// 座標変換したコピーを作成
		auto p = std::make_shared<AabbCollider>();
		p->aabb.min = Vector3(transform * Vector4(min, 1));
		p->aabb.max = Vector3(transform * Vector4(max, 1));

		// minのほうが大きかったら入れ替える
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