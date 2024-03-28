/**
* @file Collider.h
*/
#ifndef FGENGINE_COLLIDER_H_INCLUDED
#define FGENGINE_COLLIDER_H_INCLUDED
#include "Component.h"

namespace FGEngine
{
	// ��s�錾
	class Rigidbody;
	using RigidbodyPtr = std::shared_ptr<Rigidbody>;

	/**
	* �R���C�_�[�R���|�[�l���g���N���X
	*/
	class Collider : public Component
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		Collider() = default;
		virtual ~Collider() = default;

	public:

		// �R���C�_�[���A�b�^�b�`����Ă���Rigidbody
		RigidbodyPtr attachedRigidbody;

		// �L����������
		bool enabled = true;

		// �ђʂ��邩�̗L��
		bool isTrigger = false;
	};
	using ColliderPtr = std::shared_ptr<Collider>;
}

#endif // !FGENGINE_COLLIDER_H_INCLUDED
