/**
* @file Transform.cpp
*/
#include "FGEngine/Component/Transform.h"
#include "FGEngine/Math/Math.h"

namespace FGEngine
{
	/**
	* �O���x�N�g�����擾
	*/
	Vector3 Transform::Forward() const
	{
		auto foward = rotation * Vector3::forward;
		return Vector3::Normalize(foward);
	}

	/**
	* �E���x�N�g�����擾
	*/
	Vector3 Transform::Right() const
	{
		auto right = rotation * Vector3::right;
		return Vector3::Normalize(right);
	}

	/**
	* ����x�N�g�����擾
	*/
	Vector3 Transform::Up() const
	{
		auto up = rotation * Vector3::up;
		return Vector3::Normalize(up);
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
		return Quaternion::EulerAngle(rotation);
	}

	/**
	* ���݂̊p�x����euler���Z����
	*
	* @param euler ��]��(�I�C���[�p)
	*/
	void Transform::Rotate(const Vector3& eulers)
	{
		rotation = Quaternion::Euler(eulers) * rotation;
	}

	/**
	* �Ώۂ�Transform��ݒ肵�A���̕����֌���
	*
	* @param target		������ΏۃI�u�W�F�N�g��Transform
	* @param worldUp	����x�N�g��
	*/
	void Transform::LookAt(const Transform* target, const Vector3& worldUp)
	{
		// ���[���h���W�n�ɂ�����n�_���W�n��XYZ�̌������v�Z
		const Vector3 axisZ = Vector3::Normalize(-Vector3(position - target->position));
		const Vector3 axisX = Vector3::Normalize(Vector3::Cross(worldUp, axisZ));
		const Vector3 axisY = Vector3::Normalize(Vector3::Cross(axisZ, axisX));

		// ���W�����x�N�g���ɓ��e����悤�ɍs���ݒ�
		Matrix4x4 m;
		m.SetRow(0, Vector4{ axisX.x, axisY.x, axisZ.x, 0 });
		m.SetRow(1, Vector4{ axisX.y, axisY.y, axisZ.y, 0 });
		m.SetRow(2, Vector4{ axisX.z, axisY.z, axisZ.z, 0 });

		// eye�����_�ɂȂ�悤�ɁAeye���e���Ɏˉe���ĕ��s�ړ��ʂ��v�Z
		m.SetRow(3, Vector4{ -Vector3::Dot(axisX, position), -Vector3::Dot(axisY, position), -Vector3::Dot(axisZ, position), 1 });

		rotation = Quaternion::RotationMatrixToQuaternion(Matrix3x3(m));

	}

	/**
	* �Ώۂ�Transform��ݒ肵�A���̕����֌���
	*
	* @param target		������ΏۃI�u�W�F�N�g��Transform
	* @param worldUp	����x�N�g��
	*/
	void Transform::LookAt(const TransformPtr target, const Vector3& worldUp)
	{
		LookAt(target.get(), worldUp);
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
		auto ptr = parent.lock();
		if (!ptr)
		{
			return nullptr;
		}
		return ptr;
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
	* ���[�J�����W�s����擾
	*/
	Matrix4x4 Transform::GetLocalTransformMatrix() const
	{
		return localTransformMatrix;
	}

	/**
	* ���[���h���W�s����擾
	*/
	Matrix4x4 Transform::GetWorldTransformMatrix() const
	{
		return worldTransformMatrix;
	}

	/**
	* �@���s����擾
	*/
	Matrix3x3 Transform::GetNormalMatrix() const
	{
		return normalMatrix;
	}

	/**
	* 
	*/
	ComponentPtr Transform::Clone() const
	{
		TransformPtr p = std::make_shared<Transform>();

		p->position = this->position;
		p->rotation = this->rotation;
		p->scale = this->scale;

		p->localTransformMatrix = this->localTransformMatrix;
		p->worldTransformMatrix = this->worldTransformMatrix;
		p->normalMatrix = this->normalMatrix;

		p->parent = this->parent;

		return p;
	}

	/**
	* ���[�J�����W�s����X�V
	*/
	void Transform::LocalTransformUpdate()
	{
		auto pos = Matrix4x4::Translate(Vector3(position.x, position.y, -position.z));
		auto rot = Quaternion::QuaternionToRotationMatrix(Quaternion(-rotation.x, -rotation.y, rotation.z, rotation.w));
		auto s = Matrix4x4::Scale(scale);
		localTransformMatrix = pos * Matrix4x4(rot) * s;
		normalMatrix = (rot);
	}

}