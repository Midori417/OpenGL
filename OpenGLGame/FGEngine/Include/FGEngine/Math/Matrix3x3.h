/**
* @file Matrix3x3.h
*/
#ifndef FGENGINE_MATRIX3X3_H_INCLUDED
#define FGENGINE_MATRIX3X3_H_INCLUDED
#include "MathFrd.h"

namespace FGEngine
{
	/**
	* 3x3行列
	*/
	struct Matrix3x3
	{
		/**
		* デフォルトコンストラクタ
		*/
		Matrix3x3() = default;

		/**
		* 3個のVector3からMatrix3x3を作成するコンストラクタ
		*
		* @param v0
		* @param v1
		* @param v2
		*/
		explicit Matrix3x3(const Vector3& v0, const Vector3& v1, const Vector3& v2);

		/**
		* 1個のfloatを対角線にMatrix3x3を作成するコンストラクタ
		*
		* @param f
		*/
		explicit Matrix3x3(float f);

		/**
		* Matrix4x4からMatrix3x3を作成するコンストラクタ
		*
		* @param m 変換するMatrix4x4
		*/
		explicit Matrix3x3(const Matrix4x4& m);

		/**
		* 行列の行を取得する
		*
		* @param index 行の番号
		*/
		Vector3 GetRow(size_t index) const;

		/**
		* 行列の行を設定する
		*
		* @param index	行の番号
		* @param v		設定するVector3
		*/
		void SetRow(size_t index, const Vector3& v);

		/**
		* 行列の列を取得する
		*
		* @param index 列の番号
		*/
		Vector3 GerColumn(size_t index) const;

		/**
		* 行列の列を設定する
		*
		* @param index	列の番号
		* @param v		設定するVector3
		*/
		void SetColumn(size_t index, const Vector3& v);

		/**
		* 転置行列を求める
		*/
		static Matrix3x3 Transpose(const Matrix3x3& m);

		/**
		* 逆行列を計算する
		*/
		static Matrix3x3 Inverse(const Matrix3x3& m);

	public:

		float num00;
		float num01;
		float num02;

		float num10;
		float num11;
		float num12;

		float num20;
		float num21;
		float num22;

		// 恒等行列
		const static Matrix3x3 identity;

		// 全ての要素が0の行列
		const static Matrix3x3 zero;

		/**
		* 参照を返す添え字演算子
		*
		* @param row	行のインデックス
		* @param column	列のインデックス
		*/
		const float& operator()(size_t row, size_t column) const;
		float& operator()(size_t row, size_t column);
	};

	// Matrux3x3とVector3の乗算
	Vector3 operator*(const Matrix3x3& m, const Vector3& v);

	// Matrix3x3同士の乗算
	Matrix3x3 operator*(const Matrix3x3& a, const Matrix3x3& b);
	Matrix3x3 operator*=(Matrix3x3& a, const Matrix3x3& b);

}

#endif // !FGENGINE_MATRIX3X3_H_INCLUDED