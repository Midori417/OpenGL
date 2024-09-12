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

		/**
		* �R���W�����^�C�v���擾
		*/
		virtual CollisionType GetType() const;

		/**
		* �}�`���擾
		*/
		const Box& GetShape() const;

		/**
		* ���W��ύX����
		* 
		* @param translate �ړ���
		*/
		virtual void AddPosition(const Vector3& translate) override;

		/**
		* ���W�ϊ������R���C�_�[���擾����
		* 
		* @param transform �ϊ�������W�ϊ��s��
		* 
		* @return �ϊ������R���C�_�[�R���|�[�l���g
		*/
		virtual ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const;

		virtual ComponentPtr Clone() const override;

	public:

		// ���J�[�����W�ł̃R���C�_�[�̒��S���W��Ԃ�
		Vector3 center = Vector3::zero;

		// ���[�J���T�C�Y�ł̃R���C�_�[�̑傫����Ԃ�
		Vector3 size = Vector3::one;

	private:

		// �}�`
		Box box;
	};
}

#endif // !FGENGINE_BOXCOLLIDER_H_INCLUDEED
