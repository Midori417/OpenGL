/**
* @file Matrix3x3.cpp
*/
#include "FGEngine/Math/Matrix3x3.h"
#include "FGEngine/Math/Vector3.h"
#include "FGEngine/Math/Matrix4x4.h"

namespace FGEngine
{
	// 静的変数の初期化
	const Matrix3x3 Matrix3x3::identity = Matrix3x3(1);
	const Matrix3x3 Matrix3x3::zero = Matrix3x3(0);

	/**
	* 3個のVector3からMatrix3x3を作成するコンストラクタ
	*
	* @param v0
	* @param v1
	* @param v2
	*/
	Matrix3x3::Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2)
		: num00(v0.x), num01(v0.y), num02(v0.z)
		, num10(v1.x), num11(v1.y), num12(v1.z)
		, num20(v2.x), num21(v2.y), num22(v2.z)
	{

	}

	/**
	* 1個のfloatを対角線にMatrix3x3を作成するコンストラクタ
	*
	* @param f
	*/
	Matrix3x3::Matrix3x3(float f)
		: num00(f), num01(0), num02(0)
		, num10(0), num11(f), num12(0)
		, num20(0), num21(0), num22(f)
	{
	}

	/**
	* Matrix4x4からMatrix3x3を作成するコンストラクタ
	*
	* @param m 変換するMatrix4x4
	*/
	Matrix3x3::Matrix3x3(const Matrix4x4& m)
		: num00(m.num00), num01(m.num01), num02(m.num02)
		, num10(m.num10), num11(m.num11), num12(m.num12)
		, num20(m.num20), num21(m.num21), num22(m.num22)
	{
	}

	/**
	* 行列の行を取得する
	*
	* @param index 行の番号
	*/
	Vector3 Matrix3x3::GetRow(size_t index) const
	{
		Vector3 result = Vector3::zero;

		switch (index)
		{
		case 0:
			result.x = num00;
			result.y = num01;
			result.z = num02;
			break;
		case 1:
			result.x = num10;
			result.y = num11;
			result.z = num12;
			break;
		case 2:
			result.x = num20;
			result.y = num21;
			result.z = num22;
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
	void Matrix3x3::SetRow(size_t index, const Vector3& v)
	{
		switch (index)
		{
		case 0:
			num00 = v.x;
			num01 = v.y;
			num02 = v.z;
			break;
		case 1:
			num10 = v.x;
			num11 = v.y;
			num12 = v.z;
			break;
		case 2:
			num20 = v.x;
			num21 = v.y;
			num22 = v.z;
			break;
		}
	}

	/**
	* 行列の列を取得する
	*
	* @param index 列の番号
	*/
	Vector3 Matrix3x3::GerColumn(size_t index) const
	{
		Vector3 result = Vector3::zero;

		switch (index)
		{
		case 0:
			result.x = num00;
			result.y = num10;
			result.z = num20;
			break;
		case 1:
			result.x = num01;
			result.y = num11;
			result.z = num21;
			break;
		case 2:
			result.x = num02;
			result.y = num12;
			result.z = num22;
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
	void Matrix3x3::SetColumn(size_t index, const Vector3& v)
	{
		switch (index)
		{
		case 0:
			num00 = v.x;
			num10 = v.y;
			num20 = v.z;
			break;
		case 1:
			num01 = v.x;
			num11 = v.y;
			num21 = v.z;
			break;
		case 2:
			num02 = v.x;
			num12 = v.y;
			num22 = v.z;
			break;
		}
	}

	/**
	* 転置行列を求める
	*/
	Matrix3x3 Matrix3x3::Transpose(const Matrix3x3& m)
	{
		Matrix3x3 result = Matrix3x3::identity;

		result(0, 0) = m(0, 0);
		result(0, 1) = m(1, 0);
		result(0, 2) = m(2, 0);

		result(1, 0) = m(0, 1);
		result(1, 1) = m(1, 1);
		result(1, 2) = m(2, 1);

		result(2, 0) = m(0, 2);
		result(2, 1) = m(1, 2);
		result(2, 2) = m(2, 2);

		return result;
	}

	/**
	* 逆行列を計算する
	*/
	Matrix3x3 Matrix3x3::Inverse(const Matrix3x3& m)
	{
		// 四因子行列を計算
		Matrix3x3 adjugate = Matrix3x3::identity;

		adjugate(0, 0) = m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1);
		adjugate(0, 1) = -m(0, 1) * m(2, 2) + m(0, 2) * m(2, 1);
		adjugate(0, 2) = m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1);

		adjugate(1, 0) = -m(1, 0) * m(2, 2) + m(1, 2) * m(2, 0);
		adjugate(1, 1) = m(0, 0) * m(2, 2) - m(0, 2) * m(2, 0);
		adjugate(1, 2) = -m(0, 0) * m(1, 2) + m(0, 2) * m(1, 0);

		adjugate(2, 0) = m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0);
		adjugate(2, 1) = -m(0, 0) * m(2, 1) + m(0, 1) * m(2, 0);
		adjugate(2, 2) = m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);

		// 行列式を計算
		const float det =
			m(0, 0) * m(1, 1) * m(2, 2) - m(0, 0) * m(1, 2) * m(2, 1) +
			m(0, 1) * m(1, 2) * m(2, 0) - m(0, 1) * m(1, 0) * m(2, 2) +
			m(0, 2) * m(1, 0) * m(2, 1) - m(0, 2) * m(1, 1) * m(2, 0);

		// 行列式の逆数を掛ける
		const float invDet = 1.0f / det;
		adjugate.SetRow(0, adjugate.GetRow(0) * Vector3(invDet));
		adjugate.SetRow(1, adjugate.GetRow(1) * Vector3(invDet));
		adjugate.SetRow(2, adjugate.GetRow(2) * Vector3(invDet));

		return adjugate;
	}

	/**
	* 参照を返す添え字演算子
	*
	* @param row	行のインデックス
	* @param column	列のインデックス
	*/
	const float& Matrix3x3::operator()(size_t row, size_t column) const
	{
		return *((&num00) + row * 3 + column);
	}

	/**
	* 参照を返す添え字演算子
	*
	* @param row	行のインデックス
	* @param column	列のインデックス
	*/
	float& Matrix3x3::operator()(size_t row, size_t column)
	{
		return *((&num00) + row * 3 + column);
	}

	/**
	* Matrix3x3とVector3の乗算
	*/
	Vector3 operator*(const Matrix3x3& m, const Vector3& v)
	{
		return
			m.GetRow(0) * Vector3(v.x) +
			m.GetRow(1) * Vector3(v.y) +
			m.GetRow(2) * Vector3(v.z);
	}

	/**
	* Matrix3x3同士の乗算
	*/
	Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b)
	{
		return Matrix3x3(
			Vector3(a * b.GetRow(0)),
			Vector3(a * b.GetRow(1)),
			Vector3(a * b.GetRow(2)));
	}

	/**
	* Matrix3x3同士の代入乗算
	*/
	Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b)
	{
		a = a * b;
		return a;
	}
}