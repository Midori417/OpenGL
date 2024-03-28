/**
* @file BoxCollider.h
*/
#ifndef FGENGINE_BOXCOLLIDER_H_INCLUDED
#define FGENGINE_BOXCOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* �{�b�N�X�R���C�_�[
	*/
	class BoxCollider : public Collider
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		BoxCollider() = default;
		virtual ~BoxCollider() = default;

	public:

		// ���J�[�����W�ł̃R���C�_�[�̒��S���W��Ԃ�
		Vector3 center = Vector3::zero;

		// ���[�J���T�C�Y�ł̃R���C�_�[�̑傫����Ԃ�
		Vector3 size = Vector3::one;
	};
	using BoxColliderPtr = std::shared_ptr<BoxCollider>;
}

#endif // !FGENGINE_BOXCOLLIDER_H_INCLUDEED
