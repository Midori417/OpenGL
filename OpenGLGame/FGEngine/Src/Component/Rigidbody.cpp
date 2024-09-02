/**
* @file Rigidbody.cpp
*/
#include "FGEngine/Component/Rigidbody.h"
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Time.h"

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