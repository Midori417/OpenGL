/**
* @file PhysicsEngine.h
*/
#ifndef FGENGINE_PHYSICSENGINE_H_INCLUDED
#define FGENGINE_PHYSICSENGINE_H_INCLUDED
#include "FGEngine/Other/Singleton.h"
#include "FGEngine/Component/Collider.h"
#include "FGEngine/Component/Transform.h"

namespace FGEngine
{
	/**
	* ワールド座標系のコライダー
	*/
	struct WorldCollider
	{
		/**
		* 座標を変更する
		*
		* @param v 変更する値
		*/
		void AddPosition(const Vector3& v)
		{
			origin->GetTransform()->position += v;
			world->AddPosition(v);
		}
		ColliderPtr origin;
		ColliderPtr world;
	};
	using WorldColliderList = std::vector<WorldCollider>;

	/**
	* 物理エンジン
	*/
	class PhysicsEngine : public Singleton<PhysicsEngine>
	{
		friend Singleton<PhysicsEngine>;
		friend class EngineCore;
	private:

		/**
		* デフォルトコンストラクタ
		*/
		PhysicsEngine() = default;

	private:

		/**
		* 貫通ベクトルをゲームオブジェクトに反映する
		*/
		void ApplyPenetration(WorldColliderList* worldColliders, GameObject* gameObject, const Vector3& penetration);

	public:

		/**
		* ゲームオブジェクトのコライダーの衝突判定
		*
		* @param a 判定対象のワールドコライダー配列その１
		* @param b 判定対象のワールドコライダー配列その２
		*/
		void HandleWorldColliderCollision(WorldColliderList* a, WorldColliderList* b);
	};
}

#endif // !FGENGINE_PHYSICSENGINE_H_INCLUDED
