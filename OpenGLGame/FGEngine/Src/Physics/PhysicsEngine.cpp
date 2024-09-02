/**
* @file PhysicsEngine.cpp
*/
#include "FGEngine/Physics/PhysicsEngine.h"
#include "FGEngine/Physics/Intersect.h"
#include "FGEngine/GameObject.h"
#include "FGEngine/Component/Collider.h"
#include "FGEngine/Component/AabbCollider.h"
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Component/BoxCollider.h"
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Math/Mathf.h"

namespace FGEngine::PhysicsSystem
{
	/**
	* 型によって交差判定関数を呼び分けるための関数テンプレート
	*/
	template<class T, class U>
	bool CallIntersect(const ColliderPtr& a, const ColliderPtr& b, Vector3& p)
	{
		return Intersect(static_cast<T&>(*a).GetShape(), static_cast<U&>(*b).GetShape(), p);
	}

	/**
	* 型によって交差判定関数を呼び分けるための関数テンプレート
	*
	* 交差判定関数に渡す引数を逆にするバージョン
	*/
	template<class T, class U>
	bool CallIntersectRevers(const ColliderPtr& a, const ColliderPtr& b, Vector3& p)
	{
		if (Intersect(static_cast<U&>(*b).GetShape(), static_cast<T&>(*a).GetShape(), p)) {
			p *= -1;	// 貫通ベクトルを逆向きにする
			return true;
		}
		return false;
	}

	/**
	* 常にfalseを返す関数テンプレート
	*
	* 未実装または実装予定のない組み合わせ用
	*/
	template<class T, class U>
	bool NotImplemented(const ColliderPtr& a, const ColliderPtr& b, Vector3& p)
	{
		return false;
	}

	/**
	* 貫通ベクトルをゲームオブジェクトに反映する
	*/
	void PhysicsEngine::ApplyPenetration(WorldColliderList* worldColliders, GameObject* gameObject, const Vector3& penetration)
	{
		// 設置判定
		// 衝突ベクトルが垂直に近い場合、床と触れたとみなす
		static const float cosGround = Mathf::Cos(Mathf::DegToRad(90)); //　床とみなす角度
		if (penetration.y > 0 && gameObject->rigidbody)
		{
			// 対象が単位垂直ベクトルであることを利用して、内積による角度の比較を単純化
			const float d = Vector3::Magnitude(penetration);
			if (penetration.y >= d * cosGround)
			{
				gameObject->rigidbody->isGrounded = true; // 設置した
			}
		}

		// すべてのワールドコライダーを移動
		for (auto& e : *worldColliders)
		{
			Vector3 pen = penetration;
			pen.z *= -1;
			e.AddPosition(pen);
		}
	}

	/**
	* ゲームオブジェクトのコライダーの衝突判定
	*
	* @param a 判定対象のワールドコライダー配列その１
	* @param b 判定対象のワールドコライダー配列その２
	*/
	void PhysicsEngine::HandleWorldColliderCollision(WorldColliderList* a, WorldColliderList* b)
	{
		// 関数ポインタ型を定義
		using FuncType = bool(*)(const ColliderPtr&, const ColliderPtr&, Vector3&);

		// 組み合わせに対応する交差判定関数を選ぶための配列
		static const FuncType funcList[3][3] = {
			{
				CallIntersect<AabbCollider, AabbCollider>,
				CallIntersect<AabbCollider, SphereCollider>,
				NotImplemented<AabbCollider, BoxColliderPtr>,
			},
			{
				CallIntersectRevers<SphereCollider, AabbCollider>,
				CallIntersect<SphereCollider, SphereCollider>,
				CallIntersect<SphereCollider, BoxCollider>,
			},
			{
				NotImplemented<BoxCollider, AabbCollider>,
				CallIntersectRevers<BoxCollider, SphereCollider>,
				NotImplemented<BoxCollider, BoxCollider>,
			},
		};

		// コライダー単位の衝突判定
		for (auto& colA : *a)
		{
			for (auto& colB : *b)
			{
				// どちらかのコライダーにRigidbodyがついていなければ衝突しない
				if (!colA.origin->GetAttachedRigidbody() && !colB.origin->GetAttachedRigidbody())
				{
					continue;
				}
				// コライダーが機能していなければしなければ衝突しない
				if (!colA.origin->enabled || !colB.origin->enabled)
				{
					continue;
				}
				// 衝突判定を行う
				Vector3 penetration;
				const int typeA = static_cast<int>(colA.origin->GetType());
				const int typeB = static_cast<int>(colB.origin->GetType());
				if (funcList[typeA][typeB](colA.world, colB.world, penetration))
				{
					// オブジェクトを取得
					GameObjectPtr goA = colA.origin->OwnerObject();
					GameObjectPtr goB = colB.origin->OwnerObject();

					// コライダーが重ならないように座標を調整
					if (!colA.origin->isTrigger && !colB.origin->isTrigger)
					{
						if (!colA.origin->GetAttachedRigidbody())
						{
							// Aは動かないのでBを移動させる
							ApplyPenetration(b, goB.get(), penetration);
						}
						else if (!colB.origin->GetAttachedRigidbody())
						{
							// Bは動かないのでAを移動させる
							ApplyPenetration(a, goA.get(), -penetration);
						}
						else
						{
							// AとBを均等に移動させる
							ApplyPenetration(b, goB.get(), penetration * 0.5f);
							ApplyPenetration(a, goA.get(), penetration * -0.5f);
						}
					}

					// イベント処理
					if (!goA->gameEvents.empty())
					{
						// 衝突情報を作成
						CollisionPtr colInfoB = std::make_shared<Collision>();
						colInfoB->gameObject = goB;
						colInfoB->transform = goB->GetTransform();
						colInfoB->rigidBody = goB->rigidbody;
						colInfoB->collider = colB.origin;
						for (auto x : goA->gameEvents)
						{
							// 前回の時衝突していなければOnCollisionEnterを呼び出す
							if (!colA.origin->old)
							{
								x->OnCollisionEnter(colInfoB);
							}
							x->OnCollisionStay(colInfoB);
						}
					}
					if (!goB->gameEvents.empty())
					{
						// 衝突情報を作成
						CollisionPtr colInfoA = std::make_shared<Collision>();
						colInfoA->gameObject = goA;
						colInfoA->transform = goA->GetTransform();
						colInfoA->rigidBody = goA->rigidbody;
						colInfoA->collider = colA.origin;
						for (auto x : goB->gameEvents)
						{
							// 前回の時衝突していなければOnCollisionEnterを呼び出す
							if (!colB.origin->old)
							{
								x->OnCollisionEnter(colInfoA);
							}
							x->OnCollisionStay(colInfoA);
						}

					}

					// コライダー前回の状態を衝突したにする
					colA.origin->old = true;
					colB.origin->old = true;
					// イベントの結果、どちらかのゲームオブジェクトが破壊されたらループ終了
					if (goA->GetState() == GameObjectState::Destroyed || goB->GetState() == GameObjectState::Destroyed)
					{
						return;	// 関数終了
					}
				}
				else
				{
					// オブジェクトを取得
					GameObjectPtr goA = colA.origin->OwnerObject();
					GameObjectPtr goB = colB.origin->OwnerObject();

					// イベント処理
					if (!goA->gameEvents.empty())
					{
						// 衝突情報を作成
						CollisionPtr colInfoB = std::make_shared<Collision>();
						colInfoB->gameObject = goB;
						colInfoB->transform = goB->GetTransform();
						colInfoB->rigidBody = goB->rigidbody;
						colInfoB->collider = colB.origin;
						for (auto x : goA->gameEvents)
						{
							if (colA.origin->old)
							{
								x->OnCollisionExit(colInfoB);
							}
						}
					}
					if (!goB->gameEvents.empty())
					{
						// 衝突情報を作成
						CollisionPtr colInfoA = std::make_shared<Collision>();
						colInfoA->gameObject = goA;
						colInfoA->transform = goA->GetTransform();
						colInfoA->rigidBody = goA->rigidbody;
						colInfoA->collider = colA.origin;
						for (auto x : goB->gameEvents)
						{
							if (colB.origin->old)
							{
								x->OnCollisionExit(colInfoA);
							}
						}
					}


					// コライダー前回の状態を衝突していないにする
					colA.origin->old = false;
					colB.origin->old = false;

					// イベントの結果、どちらかのゲームオブジェクトが破壊されたらループ終了
					if (goA->GetState() == GameObjectState::Destroyed || goB->GetState() == GameObjectState::Destroyed)
					{
						return;	// 関数終了
					}
				}
			}
		}

	}
}