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
	* �d�͂��X�V
	*/
	void Rigidbody::GravityUpdate()
	{
		// �d�̗͂L��
		if (isGravity)
		{
			// ���}�ݒu����
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
				// �d�͉����x�ɂ���đ��x���X�V����
				velocity.y -= gravity * gravityScale * Time::DeltaTime();

			}

		}
		// ���x�����W�ɔ��f����
		GetTransform()->position += velocity * Time::DeltaTime();
	}

	/**
	* �n�ʂɐG��Ă��邩���擾
	*/
	bool Rigidbody::IsGround() const
	{
		return isGround;
	}
}