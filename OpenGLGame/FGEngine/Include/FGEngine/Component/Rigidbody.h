/**
* @file Rigidbody.h
*/
#ifndef FGENGINE_RIGIDBODY_H_INCLUDED
#define FGENGINE_RIGIDBODY_H_INCLUDED
#include "Component.h"
#include "FGEngine/Math/Vector3.h"
namespace FGEngine
{
	/**
	* 物理挙動(剛体)を有効にするコンポーネント
	*/
	class Rigidbody : public Component
	{
		friend class PhysicsEngine;
		friend Scene;
	public:
		// コンストラクタ・デストラクタ
		Rigidbody() = default;
		virtual ~Rigidbody() = default;

	private:

		/**
		* 重力の更新
		*/
		void GravityUpdate();

	public:

		/**
		* 地面についているかを取得
		*/
		bool IsGround() const;

	public:

		virtual ComponentPtr Clone() const override;

	public:

		// 物体の速度
		Vector3 velocity = Vector3::zero;

		// 重力の有無
		bool isGravity = true;

		// 重力の影響を制御する係数
		float gravityScale = 1;

		bool isVelocity = true;

	private:

		// 地面に設置の有無
		bool isGrounded = false;

		// 地面についてるか(処理速度の関係の救済処置)
		bool isGround = false;

		// 地面についていない時間
		float noGroundTimer = 0;

		// この時間を超えたら地面についていない
		float noGroundTime = 0.1f;

		// 重力加速度
		static constexpr float gravity = 9.81f;
	};
}

#endif // !FGENGINE_RIGIDBODY_H_INCLUDED