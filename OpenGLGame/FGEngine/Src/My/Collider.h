/**
* @file Collider.h
*/
#ifndef FGENGINE_COLLIDER_H_INCLUDED
#define FGENGINE_COLLIDER_H_INCLUDED
#include "Component.h"
#include "CollisionType.h"

namespace FGEngine
{
	// ��s�錾
	class Rigidbody;
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;


	/**
	* �R���C�_�[�R���|�[�l���g���N���X
	*/
	class Collider : public Component
	{
	public:

		friend PhysicsSystem::PhysicsEngine;

		// �R���X�g���N�^�E�f�X�g���N�^
		Collider() = default;
		virtual ~Collider() = default;

	public:


		/**
		* �R���C�_�[�̃^�C�v���擾
		*/
		virtual PhysicsSystem::CollisionType GetType() const = 0;

		/**
		* ���W��ύX����
		* 
		* @param v �ύX����l
		*/
		virtual void AddPosition(const Vector3& translate) = 0;

		/**
		* ���W�ϊ������R���C�_�[���擾����
		*
		* @param transform �ϊ�������W�ϊ��s��
		*
		* @return �ϊ������R���C�_�[�R���|�[�l���g
		*/
		virtual ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const = 0;

		/**
		* �I�[�i�[�Q�[���I�u�W�F�N�g��Rigidbody���擾
		* 
		* @return �I�[�i�[��Rigidbody
		*/
		RigidbodyPtr GetAttachedRigidbody() const;

	public:

		// �L����������
		bool enabled = true;

		// �ђʂ��邩�̗L��
		bool isTrigger = false;

	private:

		// �O��̃t���[���ŏՓ˂��Ă��邩
		bool old = false;
	};
}

#endif // !FGENGINE_COLLIDER_H_INCLUDED
