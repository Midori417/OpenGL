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
	* �Q�[���I�u�W�F�N�g�̑��x�Əd�͂������R���|�[�l���g
	*/
	class CharacterMovement : public Component
	{
	public:

		CharacterMovement() = default;
		virtual ~CharacterMovement() = default;

		// ���t���[�����Ăяo�����
		virtual void Update() override {
			auto owner = GetGameObject();

			if (isGravity)
			{

				if (owner->isGrounded) {
					// �ڒn�t���O�������Ă�����A�������ւ̉����x��0�ɂ���
					velocity.y = Mathf::Max(velocity.y, 0.0f);
				}
				else {
					// �d�͉����x�ɂ���đ��x���X�V����
					velocity.y -= gravity * gravityScle * Time::deltaTime();
				}
			}
			// ���x�����W�ɔ��f����
			transform->position += velocity * Time::deltaTime();
		}

	public:

		static constexpr float gravity = 9.81f;	// �d�͉����x
		bool isGravity = true;
		float gravityScle = 1;	// �d�ʂ̉e���𐧌䂷��W��
		Vector3 velocity = { 0,0,0 };	// ���x
	};
	using ChacterMovementPtr = std::shared_ptr<CharacterMovement>;
}