/**
* @file Rigidbody.cpp
*/
#include "Rigidbody.h"
#include "Transform.h"
#include "Time.h"
#include "Mathf.h"

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
}