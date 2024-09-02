/**
* @file Rigidbody.cpp
*/
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Time.h"

namespace FGEngine
{
	/**
	* 重力を更新
	*/
	void Rigidbody::GravityUpdate()
	{
		// 重力の有無
		if (isGravity)
		{
			// 応急設置判定
			if (isGrounded) 
			{
				isGround = true;
				noGroundTimer = 0;
			}
			else 
			{
				noGroundTimer += Time::DeltaTime();
				if (noGroundTimer > 0.3f)
				{
					isGround = false;
				}
			}
			if (isGround)
			{

				if (isVelocity)
				{
					velocity = Vector3::zero;
				}
			}
			else
			{
				// 重力加速度によって速度を更新する
				velocity.y -= gravity * gravityScale * Time::DeltaTime();

			}

		}
		// 速度を座標に反映する
		GetTransform()->position += velocity * Time::DeltaTime();
	}

	/**
	* 地面に触れているかを取得
	*/
	bool Rigidbody::IsGround() const
	{
		return isGround;
	}
	ComponentPtr Rigidbody::Clone() const
	{
		RigidbodyPtr p = std::make_shared<Rigidbody>();

		p->velocity = this->velocity;
		p->isGravity = this->isGravity;
		p->gravityScale = this->gravityScale;
		p->isVelocity = this->isVelocity;

		p->isGrounded = this->isGrounded;
		p->isGround = this->isGround;

		return p;
	}
}