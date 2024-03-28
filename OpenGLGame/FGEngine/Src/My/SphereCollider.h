/**
* @file SphereCollider.h
*/
#ifndef FGENGINE_SPHERECOLLIDER_H_INCLUDED
#define FGENGINE_SPHERECOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* スフィアコライダー
	*/
	class SphereCollider : public Collider
	{
	public:

		// コンストラクタ・デストラクタ
		SphereCollider() = default;
		virtual ~SphereCollider() = default;

	public:

		// オブジェクトのローカル座標でのコライダーの中心座標
		Vector3 ceneter = Vector3::zero;

		// オブジェクトのロカールサイズのコライダーの半径
		float radius = 1;
	};
	using SphereColliderPtr = std::shared_ptr<SphereCollider>;
}

#endif // !FGENGINE_SPHERECOLLIDER_H_INCLUDED
