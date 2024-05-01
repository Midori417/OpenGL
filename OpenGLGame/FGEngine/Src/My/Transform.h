/**
* @file Transform.h
*/
#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "Component.h"
#include "VecMath.h"

/**
* ���W��]�g�嗦
*/
class Transform : public Component
{
public:

	Transform() = default;
	~Transform() = default;

	// �ʒu�Ɖ�]��ݒ肷��
	void SetPositionAndRotation(const Vector3& newPosition, const Quaternion& newRotation) 
	{
		position = newPosition;
		rotation = newRotation;
	}

	void LookAt(const Vector3& target, const Vector3& up)
	{
		// ���[���h���W�n�ɂ�����n�_���W�n��XYZ�̌������v�Z
		const Vector3 axisZ = Vector3(position - target).normalized();
		const Vector3 axisX = Vector3::Cross(up, axisZ).normalized();
		const Vector3 axisY = Vector3::Cross(axisZ, axisX).normalized();

		// ���W�����x�N�g���ɓ��e����悤�ɍs���ݒ�
		Matrix4x4 m;
		m[0] = Vector4{ axisX.x, axisY.x, axisZ.x, 0 };
		m[1] = Vector4{ axisX.y, axisY.y, axisZ.y, 0 };
		m[2] = Vector4{ axisX.z, axisY.z, axisZ.z, 0 };

		// eye�����_�ɂȂ�悤�ɁAeye���e���Ɏˉe���ĕ��s�ړ��ʂ��v�Z
		m[3] = Vector4{ -Vector3::Dot(axisX, position), -Vector3::Dot(axisY, position), -Vector3::Dot(axisZ, position), 1 };

		transform->rotation = Quaternion::RotationMatrixToQuaternio(Matrix3x3(m));

	}

	// �O���x�N�g�����擾
	Vector3 forward()
	{
		Vector3 forward = rotation * Vector3::forward;
		return forward.normalized();
	}

	// �E���x�N�g�����擾
	Vector3 right()
	{
		Vector3 right = rotation * Vector3::right;
		return right.normalized();

	}

	// ����x�N�g�����擾
	Vector3 up()
	{
		Vector3 up = rotation * Vector3::up;
		return up.normalized();
	}

	/**
	* �I�C���[�p���擾
	*
	* @return �I�C���[�p
	*/
	Vector3 eulerAngles() const
	{
		return rotation.eulerAngles();
	}

	/**
	* �I�C���[�p��ݒ�
	*
	* @pram roll	X��
	* @param pitch	Y��
	* @param yaw	Z��
	*/
	void SetEulerAngles(float roll, float pitch, float yaw)
	{
		rotation = Quaternion::Euler(roll, pitch, yaw);
	}

	/**
	* ���W�ϊ��s����擾����
	*/
	const Matrix4x4& GetTransformMatrix() const 
	{
		return transformMatrix;
	}

	/**
	* �@���ϊ��s����擾����
	*/
	const Matrix3x3& GetNormalMatrix() const
	{
		return normalMatrix;
	}

	void SetTransformMatrix(const Matrix4x4& transformMatrix)
	{
		this->transformMatrix = transformMatrix;
	}

	void SetNormalMatrix(const Matrix3x3& normalMatrix)
	{
		this->normalMatrix = normalMatrix;
	}

	// ���f���s����擾
	Matrix4x4 GetModelMatrix() const
	{
		const Vector3 rot = rotation.eulerAngles();
		const auto mt = Matrix4x4::Translate(position);
		const auto mr = Quaternion::Matrix4x4Cast(rotation);
		const auto ms = Matrix4x4::Scale(scale);
		return mt * mr * ms;
	}


public:

	Vector3 position = Vector3::zero;			// ���W
	Quaternion rotation = Quaternion::identity;	// ��]
	Vector3 scale = { 1,1,1 };					// �g�嗦

private:

	Matrix4x4 transformMatrix = Matrix4x4(1);	// ���W�ϊ��s��
	Matrix3x3 normalMatrix = Matrix3x3(1);		// �@���ϊ��s��

};

using TransformPtr = std::shared_ptr<Transform>;

#endif // !TEANSFORM_H_INCLUDED
