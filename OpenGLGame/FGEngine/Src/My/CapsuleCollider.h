/**
* @file CapsuleCollider.h
*/
#ifndef FGENGINE_CAPSULECOLLIDER_H_INCLUDED
#define FGENGINE_CAPSULECOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* �J�v�Z���R���C�_�[
	*/
	class CapsuleCollider : public Collider
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		CapsuleCollider() = default;
		virtual ~CapsuleCollider() = default;

	public:

		// �I�u�W�F�N�g�̃��[�J�����W�ł̌v�Z���ꂽ�R���C�_�[�̂̒��S���W
		Vector3 center = Vector3::zero;

		// ���[�J�����W�ł̃R���C�_�[�̍���
		float height = 1;

		// ���[�J�����W�ł̃R���C�_�[�̔��a
		float radius = 0.5f;	
	};
	using CapsuleColliderPtr = std::shared_ptr<CapsuleCollider>;
}

#endif // !FGENGINE_CAPSULECOLLIDER_H_INCLUDED
