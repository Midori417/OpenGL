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

		/**
		* �R���W�����^�C�v���擾
		*/
		virtual CollisionType GetType() const;

		/**
		* �}�`���擾
		*/
		const Sphere& GetShape() const;

		/**
		* �}�`��ύX����
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
		virtual ColliderPtr GetTransformedCollider(const Matrix4x4& transform) const override;

	public:

		virtual ComponentPtr Clone() const override;

	public:

		// �I�u�W�F�N�g�̃��[�J�����W�ł̃R���C�_�[�̒��S���W
		Vector3 ceneter = Vector3::zero;

		// �I�u�W�F�N�g�̃��J�[���T�C�Y�̃R���C�_�[�̔��a
		float radius = 1;

	private:

		// �}�`
		Sphere sphere;
	};
}

#endif // !FGENGINE_SPHERECOLLIDER_H_INCLUDED
