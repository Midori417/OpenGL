/**
* @file MonoBehaviour.h
*/
#ifndef FGENGINE_MONOBEHAVIOUR_H_INCLUDED
#define FGENGINE_MONOBEHAVIOUR_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* 衝突したオブジェクトの情報を扱う
	*/
	struct Collision
	{
		friend class PhysicsEngine;
	public:

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
	using CollisionPtr = std::shared_ptr<Collision>;

	/**
	* ゲームイベント基底コンポーネント
	*/
	class GameEvent : public Component
	{
		friend Scene;
	protected:

		/**
		* デフォルトコンストラクタ
		*/
		GameEvent() = default;

		/**
		* デフォルトデストラクタ
		*/
		virtual ~GameEvent() = default;

	public:	// 生成・破壊イベント

		// 生成時に実行
		virtual void Awake() {}

		// オブジェクトを破壊時に実行
		virtual void OnDestroy() {}

	public:	// 開始・更新イベント

		// Updateが始める前に一度実行
		virtual void Start() {}

		// 毎フレーム実行
		virtual void Update() {}

		// Updateの後に実行
		virtual void LateUpdate() {}

	public:	// 衝突イベント

		// 他のコリジョンに触れたときに実行
		virtual void OnCollisionEnter(const CollisionPtr other) {}

		// 他のコリジョンから離れたときに実行
		virtual void OnCollisionExit(const CollisionPtr other) {}

		// 他のコリジョンに触れ続けているときに実行
		virtual void OnCollisionStay(const CollisionPtr ohter) {}

	public:

		virtual ComponentPtr Clone() const = 0;

	public:

		// trueならイベントを実行する
		bool isActive = true;

	private:

		// trueなら前フレーム衝突している
		bool isOldCollision = false;

		// Startを実行したか
		bool isStart = false;
	};
	using GameEventPtr = std::shared_ptr<GameEvent>;
}
#endif // !FGENGINE_MONOBEHAVIOUR_H_INCLUDED
