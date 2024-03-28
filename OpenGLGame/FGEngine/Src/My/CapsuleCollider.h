/**
* @file CapsuleCollider.h
*/
#ifndef FGENGINE_CAPSULECOLLIDER_H_INCLUDED
#define FGENGINE_CAPSULECOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* カプセルコライダー
	*/
	class CapsuleCollider : public Collider
	{
	public:

		// コンストラクタ・デストラクタ
		CapsuleCollider() = default;
		virtual ~CapsuleCollider() = default;

	public:

		// オブジェクトのローカル座標での計算されたコライダーのの中心座標
		Vector3 center = Vector3::zero;

		// ローカル座標でのコライダーの高さ
		float height = 1;

		// ローカル座標でのコライダーの半径
		float radius = 0.5f;	
	};
	using CapsuleColliderPtr = std::shared_ptr<CapsuleCollider>;
}

#endif // !FGENGINE_CAPSULECOLLIDER_H_INCLUDED
