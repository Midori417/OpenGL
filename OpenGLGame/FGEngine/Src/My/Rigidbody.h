/**
* @file Rigidbody.h
*/
#ifndef FGENGINE_RIGIDBODY_H_INCLUDED
#define FGENGINE_RIGIDBODY_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* ��������(����)��L���ɂ���R���|�[�l���g
	*/
	class Rigidbody : public Component
	{
	public:

		friend PhysicsSystem::PhysicsEngine;
		friend ObjectSystem::ObjectManager;

		// �R���X�g���N�^�E�f�X�g���N�^
		Rigidbody() = default;
		virtual ~Rigidbody() = default;

	private:

		/**
		* ���x�̍X�V
		*/
		void VeocityUpdata();

		/**
		* �d�͂̍X�V
		*/
		void GravityUpdate();

	public:

		/**
		* �n�ʂɂ��Ă��邩���擾
		*/
		bool IsGround() const;

	public:

		// ���̂̑��x
		Vector3 velocity = Vector3::zero;

		// �d�̗͂L��
		bool isGravity = true;

		// �d�͂̉e���𐧌䂷��W��
		float gravityScale = 1;

		bool isVelocity = true;

	private:

		// �n�ʂɐݒu�̗L��
		bool isGrounded = false;

		// �n�ʂɂ��Ă邩(�������x�̊֌W�̋~�Ϗ��u)
		bool isGround = false;

		// �n�ʂɂ��Ă��Ȃ�����
		float noGroundTimer = 0;

		// ���̎��Ԃ𒴂�����n�ʂɂ��Ă��Ȃ�
		float noGroundTime = 0.2f;

		// �d�͉����x
		static constexpr float gravity = 9.81f;
	};
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;
}

#endif // !FGENGINE_RIGIDBODY_H_INCLUDED