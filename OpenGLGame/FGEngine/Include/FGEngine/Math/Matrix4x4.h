/**
* @file Matrix4x4.h
*/
#ifndef FGENGINE_MATRIX4X4_H_INCLUDED
#define FGENGINE_MATRIX4X4_H_INCLUDED
#include "FGEngine/UsingNames/UsingMath.h"

namespace FGEngine
{
	/**
	* 4x4行列
	*/
	struct Matrix4x4
	{
		/**
		* デフォルトコンストラクタ
		*/
		Matrix4x4() = default;

		/**
		* 4個のVector4からMatrix4x4を作成するコンストラクタ
		*/
		explicit Matrix4x4(const Vector4& v0, const Vector4& v1, const Vector4& v2, const Vector4& v3);

		/**
		* 1個のfloatから対角線にコピーするコンストラクタ
		*/
		explicit Matrix4x4(float f);

		/*
		* Matrix3x3からMatrix4x4を作成するコンストラクタ
		*/
		explicit Matrix4x4(const Matrix3x3& m);

		/**
		* 行列の行を取得する
		*
		* @param index 行の番号
		*/
		Vector4 GetRow(size_t index) const;

		/**
		* 行列の行を設定する
		*
		* @param index	行の番号
		* @param v		設定するVector3
		*/
		void SetRow(size_t index, const Vector4& v);

		/**
		* 行列の列を取得する
		*
		* @param index 列の番号
		*/
		Vector4 GerColumn(size_t index) const;

		/**
		* 行列の列を設定する
		*
		* @param index	列の番号
		* @param v		設定するVector3
		*/
		void SetColumn(size_t index, const Vector4& v);

		/**
		* 逆行列を作成[
		*
		* @param matrix 逆行列にしたい行列
		*/
		static Matrix4x4 Invers(const Matrix4x4& matrix);

		/**
		* 平行移動行列を作成
		*
		* @param position 位置
		*/
		static Matrix4x4 Translate(const Vector3& position);

		/**
		* 拡大縮小行列を作成
		*
		* @param scale スケール
		*/
		static Matrix4x4 Scale(const Vector3& scale);

		/**
		* X軸の回転行列を作成
		*
		* @param angle xの角度
		*/
		static Matrix4x4 RotateX(float angle);

		/**
		* Y軸の回転行列を作成
		*
		* @param angle yの角度
		*/
		static Matrix4x4 RotateY(float angle);

		/**
		* Z軸の回転行列を作成
		*
		* @param angle zの角度
		*/
		static Matrix4x4 RotateZ(float angle);

		/**
		* 座標変換行列を平行移動、拡大率、回転行列の各成分に分解する
		*
		* @param[in] transform	分解元の座標変換行列
		* @param[out] translate 平行移動の格納先となる変数
		* @param[out] scale		拡大率の格納先となる変数
		* @param[out] rotation	回転行列の格納先となる変数
		*/
		static void Decompose(const Matrix4x4& transform, Vector3& translate, Vector3& scale, Matrix3x3& rotation);

		/**
		* 座標変換行列から平行移動を抽出
		*
		* @param transform 抽出元の座標変換行列
		*
		* @return 抽出した平行移動
		*/
		static Vector3 ExtractTranslate(const Matrix4x4& transform);

		/**
		* 座標変換行列から拡大率を抽出
		*
		* @param transform	抽出元の座標変換行列
		*
		* @return 抽出した拡大率
		*/
		static Vector3 ExtractScale(const Matrix4x4& transform);

		/**
		* 座標変換行列から回転行列を抽出
		* 
		* @param transform	抽出元の座標変換行列
		*
		* @return 抽出した回転行列
		*/
		static Matrix3x3 ExtractRotation(const Matrix4x4& transform);

		/**
		* ビュー行列を作成する
		*
		* @param eye		始点の座標
		* @param target		注視点の座標
		* @param up			始点の上方向を示す仮のベクトル
		*
		* @return eye, target, upから作成したビュー行列
		*/
		static Matrix4x4 LookAt(const Vector3& eye, const Vector3& target, const Vector3& up);

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
		static Matrix4x4 Orthogonal(float left, float right, float bottom, float top, float zNear, float zFar);

		static Matrix4x4 Perspective(float fov, float aspect, float zNear, float zFar);

	public:

		float num00;
		float num01;
		float num02;
		float num03;

		float num10;
		float num11;
		float num12;
		float num13;

		float num20;
		float num21;
		float num22;
		float num23;

		float num30;
		float num31;
		float num32;
		float num33;

		// 恒等行列
		const static Matrix4x4 identity;

		// 全ての要素が0の行列
		const static Matrix4x4 zero;

		/**
		* 参照を返す添え字演算子
		*
		* @param row	行のインデックス
		* @param column	列のインデックス
		*/
		const float& operator()(size_t row, size_t column) const;
		float& operator()(size_t row, size_t column);
	};

	// Matrix4x4とVector4の乗算
	Vector4 operator*(const Matrix4x4& m, const Vector4& v);

	// Matrix3x3同士の乗算
	Matrix4x4 operator*(const Matrix4x4& a, const Matrix4x4& b);
	Matrix4x4 operator*=(Matrix4x4& a, const Matrix4x4& b);

}

#endif // !FGENGINE_MATRIX4X4_H_INCLUDED