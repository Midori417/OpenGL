/**
* @file BoxCollider.h
*/
#ifndef FGENGINE_BOXCOLLIDER_H_INCLUDED
#define FGENGINE_BOXCOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* ボックスコライダー
	*/
	class BoxCollider : public Collider
	{
	public:

		// コンストラクタ・デストラクタ
		BoxCollider() = default;
		virtual ~BoxCollider() = default;

	public:

		// ロカール座標でのコライダーの中心座標を返す
		Vector3 center = Vector3::zero;

		// ローカルサイズでのコライダーの大きさを返す
		Vector3 size = Vector3::one;
	};
	using BoxColliderPtr = std::shared_ptr<BoxCollider>;
}

#endif // !FGENGINE_BOXCOLLIDER_H_INCLUDEED
