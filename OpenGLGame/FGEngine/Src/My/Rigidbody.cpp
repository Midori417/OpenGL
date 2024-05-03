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
	* 速度を更新
	*/
	void Rigidbody::VeocityUpdata()
	{
	}

	/**
	* 重力を更新
	*/
	void Rigidbody::GravityUpdate()
	{
		// 重力の有無
		if (isGravity)
		{
			// 下に何かあれば重力をなくす
			if (isGrounded) 
			{
				// 接地フラグが立っていたら、下方向への加速度を0にする
				velocity.y = Mathf::Max(velocity.y, 0.0f);
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
	bool Rigidbody::GetGrounded() const
	{
		return isGrounded;
	}
}