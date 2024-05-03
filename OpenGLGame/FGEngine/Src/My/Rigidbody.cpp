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
	* ���x���X�V
	*/
	void Rigidbody::VeocityUpdata()
	{
	}

	/**
	* �d�͂��X�V
	*/
	void Rigidbody::GravityUpdate()
	{
		// �d�̗͂L��
		if (isGravity)
		{
			// ���ɉ�������Ώd�͂��Ȃ���
			if (isGrounded) 
			{
				// �ڒn�t���O�������Ă�����A�������ւ̉����x��0�ɂ���
				velocity.y = Mathf::Max(velocity.y, 0.0f);
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
	bool Rigidbody::GetGrounded() const
	{
		return isGrounded;
	}
}