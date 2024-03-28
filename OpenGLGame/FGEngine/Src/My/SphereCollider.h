/**
* @file SphereCollider.h
*/
#ifndef FGENGINE_SPHERECOLLIDER_H_INCLUDED
#define FGENGINE_SPHERECOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* �X�t�B�A�R���C�_�[
	*/
	class SphereCollider : public Collider
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		SphereCollider() = default;
		virtual ~SphereCollider() = default;

	public:

		// �I�u�W�F�N�g�̃��[�J�����W�ł̃R���C�_�[�̒��S���W
		Vector3 ceneter = Vector3::zero;

		// �I�u�W�F�N�g�̃��J�[���T�C�Y�̃R���C�_�[�̔��a
		float radius = 1;
	};
	using SphereColliderPtr = std::shared_ptr<SphereCollider>;
}

#endif // !FGENGINE_SPHERECOLLIDER_H_INCLUDED
