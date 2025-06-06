/**
* @file BoxCollider.cpp
*/
#include "FGEngine/Component/BoxCollider.h"
#include "FGEngine/Math/Math.h"

namespace FGEngine
{
	/**
	* コリジョンタイプを取得
	*/
	CollisionType BoxCollider::GetType() const
	{
		return CollisionType::Box;
	}

	/**
	* 図形を取得
	*/
	const Box& BoxCollider::GetShape() const
	{
		return box;
	}
	
	/**
	* 座標を変更する
	* 
	* @param translate 移動量
	*/
	void BoxCollider::AddPosition(const Vector3& translate)
	{
		center += translate;
	}

	/**
	* 座標変換したコライダーを取得する
	*
	* @param transform 変換する座標変換行列
	*
	* @return 変換したコライダーコンポーネント
	*/
	ColliderPtr BoxCollider::GetTransformedCollider(const Matrix4x4& transform) const
	{
		// 座標変換行列を分解
		Vector3 translate; // 未使用
		Vector3 scale;
		Matrix3x3 rotation;
		Matrix4x4::Decompose(transform, translate, scale, rotation);

		// 座標変換したコピーを作成
		auto p = std::make_shared<BoxCollider>();
		p->box.position = Vector3(transform * Vector4(center, 1));
		for (int i = 0; i < 3; ++i)
		{
			p->box.axis[i] = rotation * box.axis[i];	// 軸ベクトル
			p->box.scale[i] = size[i] * scale[i];	// 拡大率
		}
		return p;
	}

	/**
	* Boxコライダーのクローンを作成
	*/
	ComponentPtr BoxCollider::Clone() const
	{
		BoxColliderPtr p = std::make_shared<BoxCollider>();

		// 基底クラスの変数をコピー
		p->enabled = this->enabled;
		p->isTrigger = this->isTrigger;

		p->center = this->center;
		p->size = this->size;
		p->box = this->box;

		return p;
	}
}