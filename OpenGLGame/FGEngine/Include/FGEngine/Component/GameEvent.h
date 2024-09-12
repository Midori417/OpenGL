/**
* @file MonoBehaviour.h
*/
#ifndef FGENGINE_MONOBEHAVIOUR_H_INCLUDED
#define FGENGINE_MONOBEHAVIOUR_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	/**
	* �Փ˂����I�u�W�F�N�g�̏�������
	*/
	struct Collision
	{
		friend class PhysicsEngine;
	public:

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
	using CollisionPtr = std::shared_ptr<Collision>;

	/**
	* �Q�[���C�x���g���R���|�[�l���g
	*/
	class GameEvent : public Component
	{
		friend Scene;
	protected:

		/**
		* �f�t�H���g�R���X�g���N�^
		*/
		GameEvent() = default;

		/**
		* �f�t�H���g�f�X�g���N�^
		*/
		virtual ~GameEvent() = default;

	public:	// �����E�j��C�x���g

		// �������Ɏ��s
		virtual void Awake() {}

		// �I�u�W�F�N�g��j�󎞂Ɏ��s
		virtual void OnDestroy() {}

	public:	// �J�n�E�X�V�C�x���g

		// Update���n�߂�O�Ɉ�x���s
		virtual void Start() {}

		// ���t���[�����s
		virtual void Update() {}

		// Update�̌�Ɏ��s
		virtual void LateUpdate() {}

	public:	// �Փ˃C�x���g

		// ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
		virtual void OnCollisionEnter(const CollisionPtr other) {}

		// ���̃R���W�������痣�ꂽ�Ƃ��Ɏ��s
		virtual void OnCollisionExit(const CollisionPtr other) {}

		// ���̃R���W�����ɐG�ꑱ���Ă���Ƃ��Ɏ��s
		virtual void OnCollisionStay(const CollisionPtr ohter) {}

	public:

		virtual ComponentPtr Clone() const = 0;

	public:

		// true�Ȃ�C�x���g�����s����
		bool isActive = true;

	private:

		// true�Ȃ�O�t���[���Փ˂��Ă���
		bool isOldCollision = false;

		// Start�����s������
		bool isStart = false;
	};
	using GameEventPtr = std::shared_ptr<GameEvent>;
}
#endif // !FGENGINE_MONOBEHAVIOUR_H_INCLUDED
