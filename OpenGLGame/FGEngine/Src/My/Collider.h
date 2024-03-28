/**
* @file Collider.h
*/
#ifndef FGENGINE_COLLIDER_H_INCLUDED
#define FGENGINE_COLLIDER_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	// 先行宣言
	class Rigidbody;
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;

	/**
	* コライダーコンポーネント基底クラス
	*/
	class Collider : public Component
	{
	public:

		// コンストラクタ・デストラクタ
		Collider() = default;
		virtual ~Collider() = default;

	public:

		// コライダーがアッタッチされているRigidbody
		RigidbodyPtr attachedRigidbody;

		// 有効か無効化
		bool enabled = true;

		// 貫通するかの有無
		bool isTrigger = false;
	};
	using ColliderPtr = std::shared_ptr<Collider>;
}

#endif // !FGENGINE_COLLIDER_H_INCLUDED
