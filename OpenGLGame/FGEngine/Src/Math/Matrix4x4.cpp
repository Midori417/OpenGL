/**
* @file Matrix4x4.cpp
*/
#include "FGEngine/Math/Matrix4x4.h"
#include "FGEngine/Math/Matrix3x3.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Vector4.h"
#include "FGEngine/Math/Mathf.h"

namespace FGEngine
{
	// 静的変数の初期化
	const Matrix4x4 Matrix4x4::identity = Matrix4x4(1);
	const Matrix4x4 Matrix4x4::zero = Matrix4x4(0);

	/**
	* 4個のVector4からMatrix4x4を作成するコンストラクタ
	*/
	Matrix4x4::Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3)
		: num00(v0.x), num01(v0.y), num02(v0.z), num03(v0.w)
		, num10(v1.x), num11(v1.y), num12(v1.z), num13(v1.w)
		, num20(v2.x), num21(v2.y), num22(v2.z), num23(v2.w)
		, num30(v3.x), num31(v3.y), num32(v3.z), num33(v3.w)
	{
	}

	/**
	* 1個のfloatから対角線にコピーするコンストラクタ
	*/
	Matrix4x4::Matrix4x4(float f)
		: num00(f), num01(0), num02(0), num03(0)
		, num10(0), num11(f), num12(0), num13(0)
		, num20(0), num21(0), num22(f), num23(0)
		, num30(0), num31(0), num32(0), num33(f)
	{
	}

	/*
	* Matrix3x3からMatrix4x4を作成するコンストラクタ
	*/
	Matrix4x4::Matrix4x4(const Matrix3x3& m)
		: num00(m.num00), num01(m.num01), num02(m.num02), num03(0)
		, num10(m.num10), num11(m.num11), num12(m.num12), num13(0)
		, num20(m.num20), num21(m.num21), num22(m.num22), num23(0)
		, num30(0), num31(0), num32(0), num33(1)
	{
	}

	/**
	* 行列の行を取得する
	*
	* @param index 行の番号
	*/
	Vector4 Matrix4x4::GetRow(size_t index) const
	{
		Vector4 result = Vector4::zero;

		switch (index)
		{
		case 0:
			result.x = num00;
			result.y = num01;
			result.z = num02;
			result.w = num03;
			break;
		case 1:
			result.x = num10;
			result.y = num11;
			result.z = num12;
			result.w = num13;
			break;
		case 2:
			result.x = num20;
			result.y = num21;
			result.z = num22;
			result.w = num23;
			break;
		case 3:
			result.x = num30;
			result.y = num31;
			result.z = num32;
			result.w = num33;
			break;
		}

		return result;
	}

	/**
	* 行列の行を設定する
	*
	* @param index	行の番号
	* @param v		設定するVector3
	*/
	void Matrix4x4::SetRow(size_t index, const Vector4& v)
	{
		switch (index)
		{
		case 0:
			num00 = v.x;
			num01 = v.y;
			num02 = v.z;
			num03 = v.w;
			break;
		case 1:
			num10 = v.x;
			num11 = v.y;
			num12 = v.z;
			num13 = v.w;
			break;
		case 2:
			num20 = v.x;
			num21 = v.y;
			num22 = v.z;
			num23 = v.w;
			break;
		case 3:
			num30 = v.x;
			num31 = v.y;
			num32 = v.z;
			num33 = v.w;
			break;
		}
	}

	/**
	* 行列の列を取得する
	*
	* @param index 列の番号
	*/
	Vector4 Matrix4x4::GerColumn(size_t index) const
	{
		Vector4 result = Vector4::zero;

		switch (index)
		{
		case 0:
			result.x = num00;
			result.y = num10;
			result.z = num20;
			result.w = num30;
			break;
		case 1:
			result.x = num01;
			result.y = num11;
			result.z = num21;
			result.w = num31;
			break;
		case 2:
			result.x = num02;
			result.y = num12;
			result.z = num22;
			result.w = num32;
			break;
		case 3:
			result.x = num03;
			result.y = num13;
			result.z = num23;
			result.w = num33;
			break;
		}

		return result;
	}

	/**
	* 行列の列を設定する
	*
	* @param index	列の番号
	* @param v		設定するVector3
	*/
	void Matrix4x4::SetColumn(size_t index, const Vector4& v)
	{
		switch (index)
		{
		case 0:
			num00 = v.x;
			num10 = v.y;
			num20 = v.z;
			num30 = v.w;
			break;
		case 1:
			num01 = v.x;
			num11 = v.y;
			num21 = v.z;
			num31 = v.w;
			break;
		case 2:
			num02 = v.x;
			num12 = v.y;
			num22 = v.z;
			num32 = v.w;
			break;
		case 3:
			num03 = v.x;
			num13 = v.y;
			num23 = v.z;
			num33 = v.w;
			break;
		}
	}

	/**
	* 逆行列を作成[
	* 
	* @param matrix 逆行列にしたい行列
	*/
	Matrix4x4 Matrix4x4::Invers(const Matrix4x4& matrix)
	{
		Matrix4x4 result(1);
		float det;
		int i;

		result.num00 = matrix.num11 * matrix.num22 * matrix.num33 - matrix.num11 * matrix.num23 * matrix.num32 - matrix.num21 * matrix.num12 * matrix.num33 + matrix.num21 * matrix.num13 * matrix.num32 + matrix.num31 * matrix.num12 * matrix.num23 - matrix.num31 * matrix.num13 * matrix.num22;
		result.num01 = -matrix.num01 * matrix.num22 * matrix.num33 + matrix.num01 * matrix.num23 * matrix.num32 + matrix.num21 * matrix.num02 * matrix.num33 - matrix.num21 * matrix.num03 * matrix.num32 - matrix.num31 * matrix.num02 * matrix.num23 + matrix.num31 * matrix.num03 * matrix.num22;
		result.num02 = matrix.num01 * matrix.num12 * matrix.num33 - matrix.num01 * matrix.num13 * matrix.num32 - matrix.num11 * matrix.num02 * matrix.num33 + matrix.num11 * matrix.num03 * matrix.num32 + matrix.num31 * matrix.num02 * matrix.num13 - matrix.num31 * matrix.num03 * matrix.num12;
		result.num03 = -matrix.num01 * matrix.num12 * matrix.num23 + matrix.num01 * matrix.num13 * matrix.num22 + matrix.num11 * matrix.num02 * matrix.num23 - matrix.num11 * matrix.num03 * matrix.num22 - matrix.num21 * matrix.num02 * matrix.num13 + matrix.num21 * matrix.num03 * matrix.num12;

		result.num10 = -matrix.num10 * matrix.num22 * matrix.num33 + matrix.num10 * matrix.num23 * matrix.num32 + matrix.num20 * matrix.num12 * matrix.num33 - matrix.num20 * matrix.num13 * matrix.num32 - matrix.num30 * matrix.num12 * matrix.num23 + matrix.num30 * matrix.num13 * matrix.num22;
		result.num11 = matrix.num00 * matrix.num22 * matrix.num33 - matrix.num00 * matrix.num23 * matrix.num32 - matrix.num20 * matrix.num02 * matrix.num33 + matrix.num20 * matrix.num03 * matrix.num32 + matrix.num30 * matrix.num02 * matrix.num23 - matrix.num30 * matrix.num03 * matrix.num22;
		result.num12 = -matrix.num00 * matrix.num12 * matrix.num33 + matrix.num00 * matrix.num13 * matrix.num32 + matrix.num10 * matrix.num02 * matrix.num33 - matrix.num10 * matrix.num03 * matrix.num32 - matrix.num30 * matrix.num02 * matrix.num13 + matrix.num30 * matrix.num03 * matrix.num12;
		result.num13 = matrix.num00 * matrix.num12 * matrix.num23 - matrix.num00 * matrix.num13 * matrix.num22 - matrix.num10 * matrix.num02 * matrix.num23 + matrix.num10 * matrix.num03 * matrix.num22 + matrix.num20 * matrix.num02 * matrix.num13 - matrix.num20 * matrix.num03 * matrix.num12;

		result.num20 = matrix.num10 * matrix.num21 * matrix.num33 - matrix.num10 * matrix.num23 * matrix.num31 - matrix.num20 * matrix.num11 * matrix.num33 + matrix.num20 * matrix.num13 * matrix.num31 + matrix.num30 * matrix.num11 * matrix.num23 - matrix.num30 * matrix.num13 * matrix.num21;
		result.num21 = -matrix.num00 * matrix.num21 * matrix.num33 + matrix.num00 * matrix.num23 * matrix.num31 + matrix.num20 * matrix.num01 * matrix.num33 - matrix.num20 * matrix.num03 * matrix.num31 - matrix.num30 * matrix.num01 * matrix.num23 + matrix.num30 * matrix.num03 * matrix.num21;
		result.num22 = matrix.num00 * matrix.num11 * matrix.num33 - matrix.num00 * matrix.num13 * matrix.num31 - matrix.num10 * matrix.num01 * matrix.num33 + matrix.num10 * matrix.num03 * matrix.num31 + matrix.num30 * matrix.num01 * matrix.num13 - matrix.num30 * matrix.num03 * matrix.num11;
		result.num23 = -matrix.num00 * matrix.num11 * matrix.num23 + matrix.num00 * matrix.num13 * matrix.num21 + matrix.num10 * matrix.num01 * matrix.num23 - matrix.num10 * matrix.num03 * matrix.num21 - matrix.num20 * matrix.num01 * matrix.num13 + matrix.num20 * matrix.num03 * matrix.num11;

		result.num30 = -matrix.num10 * matrix.num21 * matrix.num32 + matrix.num10 * matrix.num22 * matrix.num31 + matrix.num20 * matrix.num11 * matrix.num32 - matrix.num20 * matrix.num12 * matrix.num31 - matrix.num30 * matrix.num11 * matrix.num22 + matrix.num30 * matrix.num12 * matrix.num21;
		result.num31 = matrix.num00 * matrix.num21 * matrix.num32 - matrix.num00 * matrix.num22 * matrix.num31 - matrix.num20 * matrix.num01 * matrix.num32 + matrix.num20 * matrix.num02 * matrix.num31 + matrix.num30 * matrix.num01 * matrix.num22 - matrix.num30 * matrix.num02 * matrix.num21;
		result.num32 = -matrix.num00 * matrix.num11 * matrix.num32 + matrix.num00 * matrix.num12 * matrix.num31 + matrix.num10 * matrix.num01 * matrix.num32 - matrix.num10 * matrix.num02 * matrix.num31 - matrix.num30 * matrix.num01 * matrix.num12 + matrix.num30 * matrix.num02 * matrix.num11;
		result.num33 = matrix.num00 * matrix.num11 * matrix.num22 - matrix.num00 * matrix.num12 * matrix.num21 - matrix.num10 * matrix.num01 * matrix.num22 + matrix.num10 * matrix.num02 * matrix.num21 + matrix.num20 * matrix.num01 * matrix.num12 - matrix.num20 * matrix.num02 * matrix.num11;

		det = matrix.num00 * result.num00 + matrix.num01 * result.num10 + matrix.num02 * result.num20 + matrix.num03 * result.num30;

		if (det == 0)
		{
			return Matrix4x4::zero;
		}
		det = 1.0f / det;

		for (i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++) 
			{
				result(i, j) *= det;
			}
		}

		return result;
	}

	/**
	* 平行移動行列を作成
	*
	* @param position 位置
	*/
	Matrix4x4 Matrix4x4::Translate(const Vector3& position)
	{
		Matrix4x4 result = Matrix4x4::identity;

		result(3, 0) = position.x;
		result(3, 1) = position.y;
		result(3, 2) = position.z;
		return result;
	}

	/**
	* 拡大縮小行列を作成
	*
	* @param scale スケール
	*/
	Matrix4x4 Matrix4x4::Scale(const Vector3& scale)
	{
		Matrix4x4 result = Matrix4x4::identity;
		result(0, 0) = scale.x;
		result(1, 1) = scale.y;
		result(2, 2) = scale.z;
		return result;
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
		Matrix4x4 m = Matrix4x4::identity;
		// y' = y * c - z * s
		// z' = y * s + z * c
		m(1, 1) = c;
		m(2, 1) = -s;
		m(1, 2) = s;
		m(2, 2) = c;
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
		Matrix4x4 m = Matrix4x4::identity;
		// x' = x * c + z * s
		// z' = x * -s + z * c
		m(0, 0) = c;
		m(2, 0) = s;
		m(0, 2) = -s;
		m(2, 2) = c;
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
		Matrix4x4 m = Matrix4x4::identity;
		// x' = x * c - y * s
		// y' = x * s + y * c
		m(0, 0) = c;
		m(1, 0) = -s;
		m(0, 1) = s;
		m(1, 1) = c;
		return m;
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
		translate = ExtractTranslate(transform);

		// 拡大率の分解
		scale = ExtractScale(transform);

		// 回転行列を分解
		rotation = Matrix3x3(transform);
		rotation.SetRow(0, rotation.GetRow(0) / Vector3(scale.x));
		rotation.SetRow(1, rotation.GetRow(1) / Vector3(scale.y));
		rotation.SetRow(2, rotation.GetRow(2) / Vector3(scale.z));
	}

	/**
	* 座標変換行列から平行移動を抽出
	*
	* @param transform 抽出元の座標変換行列
	*
	* @return 抽出した平行移動
	*/
	Vector3 Matrix4x4::ExtractTranslate(const Matrix4x4& transform)
	{
		return Vector3(transform.GetRow(3));
	}

	/**
	* 座標変換行列から拡大率を抽出
	*
	* @param transform	抽出元の座標変換行列
	*
	* @return 抽出した拡大率
	*/
	Vector3 Matrix4x4::ExtractScale(const Matrix4x4& transform)
	{
		const float sx = Vector3::Magnitude(Vector3(transform.GetRow(0)));
		const float sy = Vector3::Magnitude(Vector3(transform.GetRow(1)));
		const float sz = Vector3::Magnitude(Vector3(transform.GetRow(2)));
		return Vector3(sx, sy, sz);
	}

	/**
	* 座標変換行列から回転行列を抽出
	*
	* @param transform	抽出元の座標変換行列
	*
	* @return 抽出した回転行列
	*/
	Matrix3x3 Matrix4x4::ExtractRotation(const Matrix4x4& transform)
	{
		// 拡大率の分解
		Vector3 scale = ExtractScale(transform);

		// 回転行列を分解
		Matrix3x3 rotation = Matrix3x3(transform);
		rotation.SetRow(0, rotation.GetRow(0) / Vector3(scale.x));
		rotation.SetRow(1, rotation.GetRow(1) / Vector3(scale.y));
		rotation.SetRow(2, rotation.GetRow(2) / Vector3(scale.z));

		return rotation;
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
		const Vector3 axisZ = Vector3::Normalize(Vector3(eye - target));
		const Vector3 axisX = Vector3::Normalize(Vector3::Cross(up, axisZ));
		const Vector3 axisY = Vector3::Normalize(Vector3::Cross(axisZ, axisX));

		// 座標を軸ベクトルに投影するように行列を設定
		Matrix4x4 m;
		m.SetRow(0, Vector4{ axisX.x, axisY.x, axisZ.x, 0 });
		m.SetRow(1, Vector4{ axisX.y, axisY.y, axisZ.y, 0 });
		m.SetRow(2, Vector4{ axisX.z, axisY.z, axisZ.z, 0 });

		// eyeが原点になるように、eyeを各軸に射影して平行移動量を計算
		m.SetRow(3, Vector4{ -Vector3::Dot(axisX, eye),
			-Vector3::Dot(axisY, eye),
			-Vector3::Dot(axisZ, eye),
			1 });

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
		m.SetRow(0, Vector4{ 2 / size.x,  0, 0,	0 });
		m.SetRow(1, Vector4{ 0,	2 / size.y,	0, 0 });
		m.SetRow(2, Vector4{ 0,	0, -2 / size.z,	0 });
		m.SetRow(3, Vector4(-center / size, 1));
		return m;
	}

	/**
	* 参照を返す添え字演算子
	*
	* @param row	行のインデックス
	* @param column	列のインデックス
	*/
	const float& Matrix4x4::operator()(size_t row, size_t column) const
	{
		return *((&num00) + row * 4 + column);
	}

	/**
	* 参照を返す添え字演算子
	*
	* @param row	行のインデックス
	* @param column	列のインデックス
	*/
	float& Matrix4x4::operator()(size_t row, size_t column)
	{
		return *((&num00) + row * 4 + column);
	}

	/**
	* Matrix4x4とVector4の乗算
	*/
	Vector4 operator*(const Matrix4x4& m, const Vector4& v)
	{
		return
			m.GetRow(0) * Vector4(v.x) +
			m.GetRow(1) * Vector4(v.y) +
			m.GetRow(2) * Vector4(v.z) +
			m.GetRow(3) * Vector4(v.w);
	}

	/**
	* Matrix4x4同士の乗算
	*/
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b)
	{
		return Matrix4x4(
			Vector4(a * b.GetRow(0)),
			Vector4(a * b.GetRow(1)),
			Vector4(a * b.GetRow(2)),
			Vector4(a * b.GetRow(3)));
	}

	/**
	* Matrix4x4同士の代入乗算
	*/
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b)
	{
		a = a * b;
		return a;
	}
}