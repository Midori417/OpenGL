/**
* @file VecMath.h
*/
#ifndef VECMATH_H_INCLUDED
#define VECMATH_H_INCLUDED

#include "VectorPoint.h"
#include "MatrixPoint.h"
#include "Quaternion.h"
#include "Mathf.h"
#include <vector>

// オイラー角から回転行列を作成
inline Matrix3x3 EulerAnglesToRotationMatrix(const Vector3& rotation)
{
	const float sinX = sinf(rotation.x);
	const float cosX = cosf(rotation.x);
	const float sinY = sinf(rotation.y);
	const float cosY = cosf(rotation.y);
	const float sinZ = sinf(rotation.z);
	const float cosZ = cosf(rotation.z);

	//XYZの回転順
	return{
		Vector3{ (cosY * cosZ),								(cosY * sinZ),							(-sinY)},
		Vector3{ (sinX * sinY * cosZ) + (cosX * -sinZ),		(sinX * sinY * sinZ) + (cosX * cosZ),	(sinX * cosY)},
		Vector3{ (cosX * sinY * cosZ) + (sinX * sinZ),		(cosX * sinY * sinZ) + (-sinX * cosZ),	(cosX * cosY)}
	};
}

// 拡大率、回転角度、平行移動量から座標変換行列を作成
inline Matrix4x4 GetTransformMatrix(const Vector3& scale, const Quaternion& rotation, const Vector3& position)
{
	const Matrix4x4 pos = Matrix4x4::Translate(position);
	const Matrix4x4 rot = Quaternion::Matrix4x4Cast(rotation);
	const Matrix4x4 s = Matrix4x4::Scale(scale);
	return pos * rot * s;
}


// 4x4行列から拡大率を抽出する
inline Vector3 ExtractScale(const Matrix4x4& transform)
{
	const float sx = Vector3(transform[0]).magnitude();
	const float sy = Vector3(transform[1]).magnitude();
	const float sz = Vector3(transform[2]).magnitude();
	return { sx,sy,sz };
}

/**
* 座標変換行列を平行移動、拡大率、回転行列の各成分に分解する
*
* @param[in] transform	分解元の座標変換行列
* @param[out] translate 平行移動の格納先となる変数
* @param[out] scale		拡大率の格納先となる変数
* @param[out] rotation	回転行列の格納先となる変数
*/
inline void Decompose(const Matrix4x4& transform, Vector3& translate,
	Vector3& scale, Matrix3x3& rotation)
{
	// 平行移動を分解
	translate = Vector3(transform[3]);

	// 拡大率の分解
	scale = ExtractScale(transform);

	// 回転行列を分解
	rotation = Matrix3x3(transform);
	rotation[0] /= scale.x;
	rotation[1] /= scale.y;
	rotation[2] /= scale.z;
}

/**
* ビュー行列を作成する
*
* @param eye		始点の座標
* @param target		注視点の座標
* @param up			始点の上方向を示す仮のベクトル
*
* @return eye, target, upから作成したビュー行列
*/
inline Matrix4x4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	// ワールド座標系における始点座標系のXYZの向きを計算
	const Vector3 axisZ = Vector3(eye - target).normalized();
	const Vector3 axisX = Vector3::Cross(up, axisZ).normalized();
	const Vector3 axisY = Vector3::Cross(axisZ, axisX).normalized();

	// 座標を軸ベクトルに投影するように行列を設定
	Matrix4x4 m;
	m[0] = Vector4{ axisX.x, axisY.x, axisZ.x, 0 };
	m[1] = Vector4{ axisX.y, axisY.y, axisZ.y, 0 };
	m[2] = Vector4{ axisX.z, axisY.z, axisZ.z, 0 };

	// eyeが原点になるように、eyeを各軸に射影して平行移動量を計算
	m[3] = Vector4{ -Vector3::Dot(axisX, eye), -Vector3::Dot(axisY, eye), -Vector3::Dot(axisZ, eye), 1 };

	return m;
}

inline Matrix4x4 ViewPointToProjectionMatrix(float fov, float aspectRatio, float nearClip = 0.35f, float farClip = 1000)
{
	Matrix4x4 projectionMatrix(0);
	float tanHalfFov = Mathf::Tan(0.5f * fov);
	float rangeInv = 1.0f / (nearClip - farClip);

	projectionMatrix[0][0] = 1.0f / (tanHalfFov * aspectRatio);
	projectionMatrix[1][1] = 1.0f / tanHalfFov;
	projectionMatrix[2][2] = (nearClip + farClip) * rangeInv;
	projectionMatrix[2][3] = -1.0f;
	projectionMatrix[3][2] = 2.0f * nearClip * farClip * rangeInv;

	return projectionMatrix;
}


/**
* 平行投影行列を作成する
*
* @param left	描画範囲の左端までの距離
* @param right	描画範囲の右端までの距離
* @param bottom	描画範囲の下端までの距離
* @param top	描画範囲の上端までの距離
* @param zNear	描画範囲に含まれる最小Z座標
* @param zFar	描画範囲に含まれる最大Z座標
*
* @return 平行投影行列
*/
inline Matrix4x4 Orthogonal(float left, float right, float bottom, float top, float zNear, float zFar)
{
	// 描画範囲のサイズと中心座標を計算
	const Vector3 size = { right - left, top - bottom, zFar - zNear };
	const Vector3 center = { right + left, top + bottom, zFar + zNear };

	// 描画範囲内の座標が-1～+1に変換されるように、拡大率と平行移動を設定
	Matrix4x4 m;
	m[0] = Vector4{ 2 / size.x,	 0,			0,	0 };
	m[1] = Vector4{ 0,		2 / size.y,			0,	0 };
	m[2] = Vector4{ 0,		0,			-2 / size.z,	0 };
	m[3] = Vector4(-center / size, 1);
	return m;
}
#endif // !VECMATH_H_INCLUDED

