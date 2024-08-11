/**
* @file MonoBehaviour.h
*/
#ifndef FGENGINE_MONOBEHAVIOUR_H_INCLUDED
#define FGENGINE_MONOBEHAVIOUR_H_INCLUDED
#include "Behaviour.h"

namespace FGEngine
{
	// ��s�錾
	class Collision;
	using CollisionPtr = std::shared_ptr<Collision>;

	/**
	* �Q�[���C�x���g���R���|�[�l���g
	*/
	class MonoBehaviour : public Behaviour
	{
	public:

		friend ObjectSystem::ObjectManager;

		// �R���X�g���N�^�E�f�X�g���N�^
		MonoBehaviour() = default;
		virtual ~MonoBehaviour() = default;

		// �������Ɏ��s
		virtual void Awake() {}

		// Update���n�߂�O�Ɉ�x���s
		virtual void Start() {}

		// ���t���[�����s
		virtual void Update() {}

		// Update�̌�Ɏ��s
		virtual void LateUpdate() {}

		// �I�u�W�F�N�g��j�󎞂Ɏ��s
		virtual void OnDestory() {}

		// �I�u�W�F�N�g���L���E�A�N�e�B�u�ɂȂ������Ɏ��s
		virtual void OnEnable() {}

		// �I�u�W�F�N�g�������ɂȂ������Ɏ��s
		virtual void OnDisable() {}

		// ���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
		virtual void OnCollisionEnter(const CollisionPtr other) {}

		// ���̃R���W�������痣�ꂽ�Ƃ��Ɏ��s
		virtual void OnCollisionExit(const CollisionPtr other) {}

		// ���̃R���W�����ɐG�ꑱ���Ă���Ƃ��Ɏ��s
		virtual void OnCollisionStay(const CollisionPtr ohter) {}

		// (Trigger)���̃R���W�����ɐG�ꂽ�Ƃ��Ɏ��s
		virtual void OnTriggerEnter(const CollisionPtr other) {}

		// (Trigger)���̃R���W�������痣�ꂽ�Ƃ��Ɏ��s
		virtual void OnTriggerExit(const CollisionPtr other) {}

		// (Trigger)���̃R���W�����ɐG�ꑱ���Ă���Ƃ��Ɏ��s
		virtual void OnTriggerStay(const CollisionPtr ohter) {}

		// �I�u�W�F�N�g��Ԃ�ݒ肷��
		virtual void SetEnable(bool value)
		{
			enabled = value;
			if (enabled)
			{
				OnEnable();
			}
			else
			{
				OnDisable();
			}
		}

	private:

		// Start�����s������
		bool isStart = false;
	};
	using MonoBehaviourPtr = std::shared_ptr<MonoBehaviour>;
}
#endif // !FGENGINE_MONOBEHAVIOUR_H_INCLUDED
