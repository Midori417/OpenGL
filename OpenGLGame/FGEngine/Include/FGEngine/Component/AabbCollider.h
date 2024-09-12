/**
* @file AabbCollider.h
*/
#ifndef FGENGINE_AABBCOLLIDER_H_INCLUDED
#define FGENGINE_AABBCOLLIDER_H_INCLUDED
#include "Collider.h"

namespace FGEngine
{
	/**
	* �����s�{�b�N�X�R���C�_�[
	*/
	class AabbCollider : public Collider
	{
	public:

		// �R���X�g���N�^�E�f�X�g���N�^
		AabbCollider() = default;
		virtual ~AabbCollider() = default;

		/**
		* �R���C�_�[�̃^�C�v���擾
		*/
		virtual CollisionType GetType() const;

		/**
		* �}�`���擾����
		*/
		const AABB& GetShape() const;

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

	public:

		virtual ComponentPtr Clone() const override;

	public:

		// �ŏ��l
		Vector3 min = Vector3(-1);

		// �ő�l
		Vector3 max = Vector3(1);

	private:

		// �}�`
		AABB aabb;
	};
}

#endif // !FGENGINE_AABBCOLLIDER_H_INCLUDED
