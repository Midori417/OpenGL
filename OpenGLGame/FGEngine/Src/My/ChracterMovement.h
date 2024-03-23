/**
* @file ChracterMovement.hpp
*/
#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Time.h"
#include "Transform.h"

namespace FGEngine
{

	/**
	* ゲームオブジェクトの速度と重力を扱うコンポーネント
	*/
	class CharacterMovement : public Component
	{
	public:

		CharacterMovement() = default;
		virtual ~CharacterMovement() = default;

		// 毎フレーム一回呼び出される
		virtual void Update() override {
			auto owner = GetGameObject();

			if (isGravity)
			{

				if (owner->isGrounded) {
					// 接地フラグが立っていたら、下方向への加速度を0にする
					velocity.y = Mathf::Max(velocity.y, 0.0f);
				}
				else {
					// 重力加速度によって速度を更新する
					velocity.y -= gravity * gravityScle * Time::deltaTime();
				}
			}
			// 速度を座標に反映する
			transform->position += velocity * Time::deltaTime();
		}

	public:

		static constexpr float gravity = 9.81f;	// 重力加速度
		bool isGravity = true;
		float gravityScle = 1;	// 重量の影響を制御する係数
		Vector3 velocity = { 0,0,0 };	// 速度
	};
	using ChacterMovementPtr = std::shared_ptr<CharacterMovement>;
}