/**
* @file PhysicsEngine.h
*/
#ifndef FGENGINE_PHYSICSENGINE_H_INCLUDED
#define FGENGINE_PHYSICSENGINE_H_INCLUDED
#include "FGEngine/Singleton.h"
#include "FGEngine/SystemFrd.h"
#include "WorldCollider.h"

namespace FGEngine::PhysicsSystem
{
	/**
	* 物理エンジン
	*/
	class PhysicsEngine : public Singleton<PhysicsEngine>
	{
	private:

		friend Singleton<PhysicsEngine>;
		friend MainSystem::EngineCore;

		// コンストラクタ
		PhysicsEngine() = default;

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
