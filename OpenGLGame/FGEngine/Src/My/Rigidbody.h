/**
* @file Rigidbody.h
*/
#ifndef FGENGINE_RIGIDBODY_H_INCLUDED
#define FGENGINE_RIGIDBODY_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* 物理挙動(剛体)を有効にするコンポーネント
	*/
	class Rigidbody : public Component
	{
	public:

		friend PhysicsSystem::PhysicsEngine;
		friend ObjectSystem::ObjectManager;

		// コンストラクタ・デストラクタ
		Rigidbody() = default;
		virtual ~Rigidbody() = default;

	private:

		/**
		* 速度の更新
		*/
		void VeocityUpdata();

		/**
		* 重力の更新
		*/
		void GravityUpdate();

	public:

		/**
		* 地面についているかを取得
		*/
		bool GetGrounded() const;

	public:

		// 物体の速度
		Vector3 velocity = Vector3::zero;

		// 重力の有無
		bool isGravity = true;

		// 重力の影響を制御する係数
		float gravityScale = 1;

	private:

		// 地面に設置の有無
		bool isGrounded = false;

		// 重力加速度
		static constexpr float gravity = 9.81f;
	};
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;
}

#endif // !FGENGINE_RIGIDBODY_H_INCLUDED
