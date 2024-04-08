/**
* @file Transform.cpp
*/
#include "Transform.h"

namespace FGEngine
{
	/**
	* �O���x�N�g�����擾
	*/
	Vector3 Transform::Forward() const
	{
		auto foward = rotation * Vector3::forward;
		return foward.Normalized();
	}

	/**
	* �E���x�N�g�����擾
	*/
	Vector3 Transform::Right() const
	{
		auto right = rotation * Vector3::right;
		return right.Normalized();
	}

	/**
	* ����x�N�g�����擾
	*/
	Vector3 Transform::Up() const
	{
		auto up = rotation * Vector3::up;
		return up.Normalized();
	}
	
	/**
	* �ʒu�Ɖ�]��ݒ肷��
	*
	* @param pos �ʒu
	* @param rot ��]
	*/
	void Transform::SetPositionAndRotation(const Vector3& pos, const Quaternion& rot)
	{
		position = pos;
		rotation = rot;
	}

	/**
	* translation�̕����Ƌ����Ɉړ�����
	*
	* @param translation �ړ���������Ƌ���
	*/
	void Transform::Translate(const Vector3& translation)
	{
		position += translation;
	}

	/**
	* �I�C���[�p���擾
	*/
	Vector3 Transform::GetEulerAngle() const
	{
		return rotation.EulerAngle();
	}

	/**
	* ���݂̊p�x����euler���Z����
	*
	* @param euler ��]��(�I�C���[�p)
	*/
	void Transform::Rotate(const Vector3& eulers)
	{
		rotation = Quaternion::EulerToQuaternion(eulers + rotation.EulerAngle());
	}

	/**
	* �Ώۂ�Transform��ݒ肵�A���̕����֌���
	*
	* @param target		������ΏۃI�u�W�F�N�g��Transform
	* @param worldUp	����x�N�g��
	*/
	void Transform::LookAt(const TransformPtr target, const Vector3& worldUp)
	{
		// ���[���h���W�n�ɂ�����n�_���W�n��XYZ�̌������v�Z
		const Vector3 axisZ = Vector3(position - target->position).Normalized();
		const Vector3 axisX = Vector3::Cross(worldUp, axisZ).Normalized();
		const Vector3 axisY = Vector3::Cross(axisZ, axisX).Normalized();

		// ���W�����x�N�g���ɓ��e����悤�ɍs���ݒ�
		Matrix4x4 m;
		m[0] = Vector4{ axisX.x, axisY.x, axisZ.x, 0 };
		m[1] = Vector4{ axisX.y, axisY.y, axisZ.y, 0 };
		m[2] = Vector4{ axisX.z, axisY.z, axisZ.z, 0 };

		// eye�����_�ɂȂ�悤�ɁAeye���e���Ɏˉe���ĕ��s�ړ��ʂ��v�Z
		m[3] = Vector4{ -Vector3::Dot(axisX, position), -Vector3::Dot(axisY, position), -Vector3::Dot(axisZ, position), 1 };

		rotation = Quaternion::RotationMatrixToQuaternion(Matrix3x3(m));

	}

	/**
	* �eTransform��ݒ肷��
	*
	* @param parent �ݒ肷��e��Transform
	*/
	void Transform::SetParent(const TransformPtr parent)
	{
		// �����e���w�肵�Ă����牽�����Ȃ�
		if (this->parent.lock() == parent)
		{
			return;
		}

		// �ʂ̐e���w�肳�ꂽ�ꍇ���̐e�Ɗ֌W����������
		auto par = this->parent.lock();
		if (par)
		{
			// �����̈ʒu������
			auto itr = std::find_if(par->childrens.begin(), par->childrens.end(),
				[this](const std::weak_ptr<Transform>& child) {
					return child.lock() == this->GetTransform();
				});

			// �e�̎q���z��̒��̎����Ƃ̊֌W���e������
			if (itr != par->childrens.end())
			{
				par->childrens.erase(itr);
			}
		}

		// �V���Ȑe�q�֌W��ݒ�
		if (parent)
		{
			parent->childrens.push_back(GetTransform());
		}
		this->parent = parent;
	}

	/**
	* �eTransform���擾����
	*/
	TransformPtr Transform::GetParent() const
	{
		return parent.lock();
	}

	/**
	* �q�I�u�W�F�N�g�̐����擾����
	*/
	size_t Transform::GetChildrenCount() const
	{
		return childrens.size();
	}

	/**
	* index����q��Transform���擾����
	*
	* @param �qTransform��index
	*/
	TransformPtr Transform::GetChildren(size_t index) const
	{
		return childrens[index].lock();
	}

	/**
	* �S�Ă̎q�I�u�W�F�N�g��؂藣��
	*/
	void Transform::AllChildrenPurge()
	{
		childrens.clear();
	}

	/**
	* ���[���h���W�s����擾
	*/
	Matrix4x4 Transform::GetTransformMatrix() const
	{
		return worldToLocalMatrix;
	}

	/**
	* �@���s����擾
	*/
	Matrix3x3 Transform::GetNormalMatrix() const
	{
		return normalMatrix;
	}

}