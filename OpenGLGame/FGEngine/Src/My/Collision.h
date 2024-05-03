/**
* @file Collision.h
*/
#ifndef FGENGINE_COLLISION_H_INCLUDED
#define FGENGINE_COLLISION_H_INCLUDED
#include <memory>
#include "SystemFrd.h"

namespace FGEngine
{
	class GameObject;
	using GameObjectPtr = std::shared_ptr<GameObject>;
	class Transform;
	using TransformPtr = std::shared_ptr<Transform>;
	class Rigidbody;
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;
	class Collider;
	using ColliderPtr = std::shared_ptr<Collider>;


	/**
	* �Փ˂����I�u�W�F�N�g�̏�������
	*/
	class Collision
	{
	public:

		friend PhysicsSystem::PhysicsEngine;

		// �R���X�g���N�^�E�f�X�g���N�^
		Collision() = default;
		~Collision() = default;

		/**
		* �q�b�g�����Q�[���I�u�W�F�N�g�̏����擾
		*/
		GameObjectPtr GetGameObject() const
		{
			return gameObject;
		}

		/**
		* �q�b�g����Transform�̏����擾
		*/
		TransformPtr GetTransform() const
		{
			return transform;
		}

		/**
		* �q�b�g����Collider�̏����擾
		*/
		ColliderPtr GetCollider() const
		{
			return collider;
		}

		/**
		* �q�b�g����Rigidbody�̏����擾
		*/
		RigidbodyPtr GetRigidbody() const
		{
			return rigidBody;
		}

	private:

		// �q�b�g�����Q�[���I�u�W�F�N�g���
		GameObjectPtr gameObject;

		// �q�b�g����Transform
		TransformPtr transform;

		// �q�b�g����Collider���
		ColliderPtr collider;

		// �q�b�g����Rigidbody���
		RigidbodyPtr rigidBody;

	};
}
#endif // !FGENGINE_COLLISION_H_INCLUDED
