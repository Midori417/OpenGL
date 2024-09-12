/**
* @file SphereCollider.cpp
*/
#include "FGEngine/Component/SphereCollider.h"
#include "FGEngine/Math/Mathf.h"
#include "FGEngine/Math/Math.h"

namespace FGEngine
{
	/**
	* �R���W�����^�C�v���擾
	*/
	CollisionType SphereCollider::GetType() const
	{
		return CollisionType::Sphere;
	}

	/**
	* �}�`���擾
	*/
	const Sphere& SphereCollider::GetShape() const
	{
		return sphere;
	}

	/**
	* �}�`��ύX����
	*
	* @param translate �ړ���
	*/
	void SphereCollider::AddPosition(const Vector3& translate)
	{
		ceneter += translate;
	}

	/**
	* ���W�ϊ������R���C�_�[���擾����
	*
	* @param transform �ϊ�������W�ϊ��s��
	*
	* @return �ϊ������R���C�_�[�R���|�[�l���g
	*/
	ColliderPtr SphereCollider::GetTransformedCollider(const Matrix4x4& transform) const
	{
		// ���S���W�����W�ϊ�����
		auto p = std::make_shared<SphereCollider>();
		p->sphere.position = Vector3(transform * Vector4(ceneter, 1));

		// ���̂̊g�嗦�̓I�u�W�F�N�g��XYZ�g�嗦�̂����ő�̂��̂Ƃ���(Uinty�)
		const Vector3 scale = Matrix4x4::ExtractScale(transform);
		const float maxScale = Mathf::Max(Mathf::Max(scale.x,scale.y),scale.z);
		p->sphere.radius = radius * maxScale;
		return p;
	}

	ComponentPtr SphereCollider::Clone() const
	{
		SphereColliderPtr p = std::make_shared<SphereCollider>();

		// ���N���X�̕ϐ����R�s�[
		p->enabled = this->enabled;
		p->isTrigger = this->isTrigger;

		p->ceneter = this->ceneter;
		p->radius = this->radius;
		p->sphere = this->sphere;

		return p;
	}

}