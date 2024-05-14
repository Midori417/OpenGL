/**
* @file Matrix4x4.cpp
*/
#include "Matrix4x4.h"
#include "Matrix3x3.h"
#include "Vector3.h"
#include "Mathf.h"

namespace FGEngine
{
	/**
	* 4個のVector4からMatrix4x4を構成するコンストラクタ
	*/
	Matrix4x4::Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
	{
		data[0] = v0;
		data[1] = v1;
		data[2] = v2;
		data[3] = v3;
	}

	/**
	* 1個のfloatを対角線にコピーするコンストラクタ
	*/
	Matrix4x4::Matrix4x4(float f)
	{
		data[0] = Vector4{ f, 0, 0, 0 };
		data[1] = Vector4{ 0, f, 0, 0 };
		data[2] = Vector4{ 0, 0, f, 0 };
		data[3] = Vector4{ 0, 0, 0, f };
	}

	/**
	* Matrix3x3からMatrix4x4に変換するコンストラクタ
	*/
	Matrix4x4::Matrix4x4(const Matrix3x3& m)
	{
		data[0] = Vector4{ m.data[0], 0 };
		data[1] = Vector4{ m.data[1], 0 };
		data[2] = Vector4{ m.data[2], 0 };
		data[3] = Vector4{ 0, 0, 0, 1 };
	}

	/**
	* 平行移動行列を作成
	*
	* @param position 位置
	*/
	Matrix4x4 Matrix4x4::Translate(const Vector3& position)
	{
		Matrix4x4 m(1);
		m[3][0] = position.x;
		m[3][1] = position.y;
		m[3][2] = position.z;
		return m;
	}

	/**
	*  拡大縮小行列を作成
	*
	* @param scale スケール
	*/
	Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
	{
		Matrix4x4 m(1);
		m[0][0] = scale.x;
		m[1][1] = scale.y;
		m[2][2] = scale.z;
		return m;
	}

	/**
	* X軸の回転行列を作成
	*
	* @param angle xの角度
	*/
	Matrix4x4 Matrix4x4::RotateX(float angle)
	{
		const float c = Mathf::Cos(angle);
		const float s = Mathf::Sin(angle);
		Matrix4x4 m(1);
		// y' = y * c - z * s
		// z' = y * s + z * c
		m[1][1] = c;
		m[2][1] = -s;
		m[1][2] = s;
		m[2][2] = c;
		return m;
	}

	/**
	* Y軸の回転行列を作成
	*
	* @param angle yの角度
	*/
	Matrix4x4 Matrix4x4::RotateY(float angle)
	{
		const float c = Mathf::Cos(angle);
		const float s = Mathf::Sin(angle);
		Matrix4x4 m(1);
		// x' = x * c + z * s
		// z' = x * -s + z * c
		m[0][0] = c;
		m[2][0] = s;
		m[0][2] = -s;
		m[2][2] = c;
		return m;
	}

	/**
	* Z軸の回転行列を作成
	*
	* @param angle zの角度
	*/
	Matrix4x4 Matrix4x4::RotateZ(float angle)
	{
		const float c = Mathf::Cos(angle);
		const float s = Mathf::Sin(angle);
		Matrix4x4 m(1);
		// x' = x * c - y * s
		// y' = x * s + y * c
		m[0][0] = c;
		m[1][0] = -s;
		m[0][1] = s;
		m[1][1] = c;
		return m;
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
	Matrix4x4 Matrix4x4::LookAt(const Vector3& eye, const Vector3& target, const Vector3& up)
	{
		// ワールド座標系における始点座標系のXYZの向きを計算
		const Vector3 axisZ = -Vector3(eye - target).Normalized();
		const Vector3 axisX = Vector3::Cross(up, axisZ).Normalized();
		const Vector3 axisY = Vector3::Cross(axisZ, axisX).Normalized();

		// 座標を軸ベクトルに投影するように行列を設定
		Matrix4x4 m;
		m[0] = Vector4{ axisX.x, axisY.x, axisZ.x, 0 };
		m[1] = Vector4{ axisX.y, axisY.y, axisZ.y, 0 };
		m[2] = Vector4{ axisX.z, axisY.z, axisZ.z, 0 };

		// eyeが原点になるように、eyeを各軸に射影して平行移動量を計算
		m[3] = Vector4{ -Vector3::Dot(axisX, eye), -Vector3::Dot(axisY, eye), -Vector3::Dot(axisZ, eye), 1 };

		return m;
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
	Matrix4x4 Matrix4x4::Orthogonal(float left, float right, float bottom, float top, float zNear, float zFar)
	{
		// 描画範囲のサイズと中心座標を計算
		const Vector3 size = Vector3{ right - left, top - bottom, zFar - zNear };
		const Vector3 center = Vector3{ right + left, top + bottom, zFar + zNear };

		// 描画範囲内の座標が-1～+1に変換されるように、拡大率と平行移動を設定
		Matrix4x4 m;
		m[0] = Vector4{ 2 / size.x,	 0,			0,	0 };
		m[1] = Vector4{ 0,		2 / size.y,			0,	0 };
		m[2] = Vector4{ 0,		0,			-2 / size.z,	0 };
		m[3] = Vector4(-center / size, 1);
		return m;
	}

	/**
	* 座標変換行列から拡大率を抽出する
	* 
	* @param transform 分解元の座標変換行列
	* 
	* @return 抽出した拡大率
	*/
	Vector3 ExtractScale(const Matrix4x4& transform)
	{
		const float sx = Vector3(transform[0]).Magnitude();
		const float sy = Vector3(transform[1]).Magnitude();
		const float sz = Vector3(transform[2]).Magnitude();
		return Vector3{ sx,sy,sz };
	}

	/**
	* 座標変換行列を平行移動、拡大率、回転行列の各成分に分解する
	*
	* @param[in] transform	分解元の座標変換行列
	* @param[out] translate 平行移動の格納先となる変数
	* @param[out] scale		拡大率の格納先となる変数
	* @param[out] rotation	回転行列の格納先となる変数
	*/
	void Matrix4x4::Decompose(const Matrix4x4& transform, Vector3& translate, Vector3& scale, Matrix3x3& rotation)
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
	* 座標変換行列から拡大率を抽出
	*
	* @param transform	抽出元の座標変換行列
	*
	* @return 抽出した拡大率を
	*/
	Vector3 Matrix4x4::ExtractScale(const Matrix4x4& transform)
	{
		const float sx = Vector3(transform[0]).Magnitude();
		const float sy = Vector3(transform[1]).Magnitude();
		const float sz = Vector3(transform[2]).Magnitude();
		return Vector3{ sx,sy,sz };
	}

	/**
	* Matrix3x3とVector3の乗算
	*/
	Vector4 operator*(const Matrix4x4& m, const Vector4& v)
	{
		return m.data[0] * v.x + m.data[1] * v.y + m.data[2] * v.z + m.data[3] * v.w;
	}

	/**
	* Matrix3x3同士の乗算
	*/
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
	{
		Matrix4x4 m;
		m.data[0] = a * b.data[0];
		m.data[1] = a * b.data[1];
		m.data[2] = a * b.data[2];
		m.data[3] = a * b.data[3];

		return m;
	}

	/**
	* Matrix3x3同士の代入乗算
	*/
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b)
	{
		a = a * b;
		return a;
	}
}