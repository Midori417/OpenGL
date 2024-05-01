/**
* @file Transform.h
*/
#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "Component.h"
#include "VecMath.h"

/**
* 座標回転拡大率
*/
class Transform : public Component
{
public:

	Transform() = default;
	~Transform() = default;

	// 位置と回転を設定する
	void SetPositionAndRotation(const Vector3& newPosition, const Quaternion& newRotation) 
	{
		position = newPosition;
		rotation = newRotation;
	}

	void LookAt(const Vector3& target, const Vector3& up)
	{
		// ワールド座標系における始点座標系のXYZの向きを計算
		const Vector3 axisZ = Vector3(position - target).normalized();
		const Vector3 axisX = Vector3::Cross(up, axisZ).normalized();
		const Vector3 axisY = Vector3::Cross(axisZ, axisX).normalized();

		// 座標を軸ベクトルに投影するように行列を設定
		Matrix4x4 m;
		m[0] = Vector4{ axisX.x, axisY.x, axisZ.x, 0 };
		m[1] = Vector4{ axisX.y, axisY.y, axisZ.y, 0 };
		m[2] = Vector4{ axisX.z, axisY.z, axisZ.z, 0 };

		// eyeが原点になるように、eyeを各軸に射影して平行移動量を計算
		m[3] = Vector4{ -Vector3::Dot(axisX, position), -Vector3::Dot(axisY, position), -Vector3::Dot(axisZ, position), 1 };

		transform->rotation = Quaternion::RotationMatrixToQuaternio(Matrix3x3(m));

	}

	// 前方ベクトルを取得
	Vector3 forward()
	{
		Vector3 forward = rotation * Vector3::forward;
		return forward.normalized();
	}

	// 右方ベクトルを取得
	Vector3 right()
	{
		Vector3 right = rotation * Vector3::right;
		return right.normalized();

	}

	// 上方ベクトルを取得
	Vector3 up()
	{
		Vector3 up = rotation * Vector3::up;
		return up.normalized();
	}

	/**
	* オイラー角を取得
	*
	* @return オイラー角
	*/
	Vector3 eulerAngles() const
	{
		return rotation.eulerAngles();
	}

	/**
	* オイラー角を設定
	*
	* @pram roll	X軸
	* @param pitch	Y軸
	* @param yaw	Z軸
	*/
	void SetEulerAngles(float roll, float pitch, float yaw)
	{
		rotation = Quaternion::Euler(roll, pitch, yaw);
	}

	/**
	* 座標変換行列を取得する
	*/
	const Matrix4x4& GetTransformMatrix() const 
	{
		return transformMatrix;
	}

	/**
	* 法線変換行列を取得する
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

	// モデル行列を取得
	Matrix4x4 GetModelMatrix() const
	{
		const Vector3 rot = rotation.eulerAngles();
		const auto mt = Matrix4x4::Translate(position);
		const auto mr = Quaternion::Matrix4x4Cast(rotation);
		const auto ms = Matrix4x4::Scale(scale);
		return mt * mr * ms;
	}


public:

	Vector3 position = Vector3::zero;			// 座標
	Quaternion rotation = Quaternion::identity;	// 回転
	Vector3 scale = { 1,1,1 };					// 拡大率

private:

	Matrix4x4 transformMatrix = Matrix4x4(1);	// 座標変換行列
	Matrix3x3 normalMatrix = Matrix3x3(1);		// 法線変換行列

};

using TransformPtr = std::shared_ptr<Transform>;

#endif // !TEANSFORM_H_INCLUDED
