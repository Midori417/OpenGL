/**
* @file Quaternion.h
*/
#ifndef QUATERNION_H_INCLUDED
#define QUATERNION_H_INCLUDED

#include "VectorFrd.h"
#include "MatrixFrd.h"

/**
* �N�H�[�^�j�I��
*/
struct Quaternion
{
public:		
	
	Quaternion() = default;
	constexpr explicit Quaternion(float x, float y, float z, float w)
		: x(x), y(y), z(z), w(w) {}
	constexpr Quaternion(const Quaternion& q)
		: x(q.x), y(q.y), z(q.z), w(q.w){}
	~Quaternion() = default;
	
	// axis�̎����angle�x��]�����]��Ԃ�
	static Quaternion AngleAxis(float angle, const Vector3& axis);
	
	// a��b�̓��ς�Ԃ�
	static float Dot(const Quaternion& a, const Quaternion& b);
	
	// �I�C���[�p����N�H�[�^�j�I���ɕϊ�
	static Quaternion Euler(float x, float y, float z);
	static Quaternion Euler(const Vector3& v);

	// �w�肳�ꂽforward��upwards�����ɉ�]����
	static Quaternion LookRotation(const Vector3& forward, const Vector3& upward);
	static Quaternion LookRotation(const Vector3& foward);

	// q�𐳋K�����ĕԂ�
	static Quaternion Normalize(const Quaternion& q);
	
	// a��b�������Ԃ���t[0�`1]�ŕԂ�
	static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);
	
	// a��b������ۊǂ���t�ŕԂ�
	static Quaternion SlerpUnclamped(const Quaternion& a, const Quaternion& b, float t);

public:

	float x, y, z, w;

	static const Quaternion identity;

	// �N�H�[�^�j�I���̐��K��
	Quaternion normalized() const;

	// �I�C���[�p���擾
	Vector3 eulerAngles() const;

	// �N�H�[�^�j�I���̋t�����擾
	Quaternion inverse() const;


	float operator[](size_t i)const {
		return *(&x + i);
	}
	float& operator[](size_t i) {
		return *(&x + i);
	}

	// ��]�s�񂩂�N�H�[�^�j�I���ɕϊ�
	static Quaternion RotationMatrixToQuaternio(const Matrix3x3& rotationMatrix);

	// �N�H�[�^�j�I�����s��ɕϊ�����
	static Matrix3x3 Matrix3x3Cast(const Quaternion& qua); 
	static Matrix4x4 Matrix4x4Cast(const Quaternion& qua);

private:

	// �I�C���[�p����N�H�[�^�j�I���ɕϊ�
	static Quaternion EulerToQuaternion(const Vector3& v);
	
	// �N�H�[�^�j�I������I�C���[�p�ɕϊ�
	static Vector3 QuaternionToEuler(const Quaternion& q);
	
	// �I�C���[�p�����]�s��ɕϊ�
	static Matrix3x3 EulerToRotationMatrix(const Vector3& rotation);
};

// �N�H�[�^�j�I�����m�̏�Z
Quaternion operator*(const Quaternion& a, const Quaternion& b);

// �N�H�[�^�j�I���ƃx�N�g���̏�Z
Vector3 operator*(const Quaternion& q, const Vector3& v);

// ��̃N�H�[�^�j�I������v���邩�ǂ���
bool operator==(const Quaternion& a, const Quaternion& b);
#endif // !QUATERNION_H_INCLUDED
