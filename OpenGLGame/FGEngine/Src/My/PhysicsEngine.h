/**
* @file PhysicsEngine.h
*/
#ifndef FGENGINE_PHYSICSENGINE_H_INCLUDED
#define FGENGINE_PHYSICSENGINE_H_INCLUDED
#include "Singleton.h"
#include "SystemFrd.h"
#include "WorldCollider.h"

namespace FGEngine::PhysicsSystem
{
	/**
	* 物理エンジン
	*/
	class PhysicsEngine : Singleton<PhysicsEngine>
	{
	private:

		friend Singleton<PhysicsEngine>;
		friend ObjectSystem::ObjectManager;
		friend MainSystem::EngineCore;

		// コンストラクタ
		PhysicsEngine() = default;

		/**
		* 貫通ベクトルをゲームオブジェクトに反映する
		*/
		void ApplyPenetration(WorldColliderList* worldColliders, GameObjectPtr gameObject, const Vector3& penetration);

		/**
		* ゲームオブジェクトのコライダーの衝突判定
		* 
		* @param a 判定対象のワールドコライダー配列その１
		* @param b 判定対象のワールドコライダー配列その２
		*/
		void HandleWorldColliderCollision(WorldColliderList* a, WorldColliderList* b);

	private:

		/**
		* 物理エンジンを更新
		*/
		void Update();

	};
}

#endif // !FGENGINE_PHYSICSENGINE_H_INCLUDED
