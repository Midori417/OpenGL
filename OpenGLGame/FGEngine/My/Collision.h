/**
* @file Collision.h
*/
#ifndef FGENGINE_COLLISION_H_INCLUDED
#define FGENGINE_COLLISION_H_INCLUDED
#include <memory>
#include "SystemFrd.h"

namespace FGEngine
{
	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
	class Transform;
	using TransformPtr = std::shared_ptr<Transform>;
	class Rigidbody;
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;


	/**
	* 衝突したオブジェクトの情報を扱う
	*/
	class Collision
	{
	public:

		friend PhysicsSystem::PhysicsEngine;

		// コンストラクタ・デストラクタ
		Collision() = default;
		~Collision() = default;

		/**
		* ヒットしたゲームオブジェクトの情報を取得
		*/
		GameObjectPtr GetGameObject() const
		{
			return gameObject;
		}

		/**
		* ヒットしたTransformの情報を取得
		*/
		TransformPtr GetTransform() const
		{
			return transform;
		}

		/**
		* ヒットしたColliderの情報を取得
		*/
		ColliderPtr GetCollider() const
		{
			return collider;
		}

		/**
		* ヒットしたRigidbodyの情報を取得
		*/
		RigidbodyPtr GetRigidbody() const
		{
			return rigidBody;
		}

	private:

		// ヒットしたゲームオブジェクト情報
		GameObjectPtr gameObject;

		// ヒットしたTransform
		TransformPtr transform;

		// ヒットしたCollider情報
		ColliderPtr collider;

		// ヒットしたRigidbody情報
		RigidbodyPtr rigidBody;

	};
}
#endif // !FGENGINE_COLLISION_H_INCLUDED
