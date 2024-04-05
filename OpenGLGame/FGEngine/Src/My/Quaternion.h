/**
* @file Quaternion.h
*/
#ifndef FGENGINE_QUATERNION_H_INCLUDED
#define FGENGINE_QUATERNION_H_INCLUDED

#include "VectorFrd.h"
#include "MatrixFrd.h"

namespace FGEngine
{

	/**
	* クォータニオン
	*/
	struct Quaternion
	{
	public:

		// デフォルトコンストラクタ
		Quaternion() = default;

		// 4個のfloatからクォータニオンを構築するコンストラクタ
		explicit Quaternion(float x, float y, float z, float w);

		/**
		* クォータニオンを正規化する
		*/
		void Normalize();

		/**
		* 正規化したクォータニオンを取得
		* 
		* @return 正規化したクォータニオン
		*/
		Quaternion Normalized() const;

		/**
		* オイラー角に変換して取得
		* 
		* @return 変換したオイラー角
		*/
		Vector3 EulerAngle() const;

		/**
		* クォータニオンの逆数を取得
		* 
		* @param クォータニオンの逆数
		*/
		Quaternion Inverse() const;

		/**
		* axisの周りをangle(度数法)回転するクォータニオンを返す
		* 
		* @param angle	回転する角度(度数法)
		* @param axis	回転する軸
		* 
		* @return 回転したクォータニオン
		*/
		static Quaternion AngleAxis(float angle, const Vector3& axis);

		/**
		* 2つのクォータニオンの内積を計算する
		* 
		* @param a	クォータニオン1
		* @param b	クォータニオン2
		* 
		* @return aとbの内積
		*/
		static float Dot(const Quaternion& a, const Quaternion& b);

		/**
		* 前方ベクトルと上方ベクトルの方向に回転する
		*
		* @param foward	前方ベクトル
		* @param upward 上方べベクトル
		*
		* @return 作成したクォータニオン
		*/
		static Quaternion LookRotation(const Vector3& foward, const Vector3& upward);

		/**
		* 前方ベクトルと上方ベクトルの方向に回転する
		*
		* @param foward	前方ベクトル
		*
		* @return 作成したクォータニオン
		*/
		static Quaternion LookRotation(const Vector3& foward);

		/**
		* クォータニオン a と クォータニオン b の間を球状補間する
		*
		* @param a 補間の開始クォータニオン
		* @param b 補間の終了クォータニオン
		* @param t 補間パラメータ (0.0 ~ 1.0 の範囲)
		*
		* @return 補間されたクォータニオン
		*/
		static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);

		/**
		* オイラー角からクォータニオンに変換
		* 
		* @param euler	オイラー角
		* 
		* @return 変換したクォータニオン
		*/
		static Quaternion EulerToQuaternion(const Vector3& euler);

		/**
		* オイラー角からクォータニオンに変換
		* 
		* @param x	Xの角度(度数法)
		* @param y	Yの角度(度数法)
		* @param z	Zの角度(度数法)
		* 
		* @return 変換したクォータニオン
		*/
		static Quaternion EulerToQuaternion(float x, float y, float z);

		/**
		* クォータニオンからオイラー角に変換
		* 
		* @param qua クォータニオン
		* 
		* @return 変換したオイラー角
		*/
		static Vector3 QuaternionToEuler(const Quaternion& qua);

		/**
		* 回転行列(Matrix3x3)からクォータニオンに変換
		*
		* @param rotationMatrix 回転行列(Matrix3x3)
		*
		* @return 変換したクォータニオン
		*/
		static Quaternion RotationMatrixToQuaternion(const Matrix3x3& rotationMatrix);

		/**
		* 回転行列(Matrix4x4)からクォータニオンに変換
		* 
		* @param rotationMatrix 回転行列(Matrix4x4)
		* 
		* @return 変換したクォータニオン
		*/
		static Quaternion RotationMatrixToQuaternion(const Matrix4x4& rotationMatrix);

		/**
		* クォータニオンから回転行列(Matrix3x3)に変換
		* 
		* @param qua クォータニオン
		* 
		* @return 変換した回転行列(Matrix3x3)
		*/
		static Matrix3x3 QuaternionToRotationMatrix3x3(const Quaternion& qua);

		/**
		* クォータニオンから回転行列(Matrix4x4)に変換
		*
		* @param qua クォータニオン
		*
		* @return 変換した回転行列(Matrix4x4)
		*/
		static Matrix4x4 QuaternionToRotationMatrix4x4(const Quaternion& qua);

	public:

		// クォータニオンのX成分
		float x;

		// クォータニオンのY成分
		float y;

		// クォータニオンのZ成分
		float z;

		// クォータニオンのW成分
		float w;

		const static Quaternion identity;

		float operator[](size_t i) const
		{
			return *(&x + i);
		}
		float& operator[](size_t i) 
		{
			return *(&x + i);
		}

	};

	// クォータニオン同士の乗算
	Quaternion operator*(const Quaternion& a, const Quaternion& b);

	// クォータニオンとベクトルの乗算
	Vector3 operator*(const Quaternion& qua, const Vector3& v);

	// クォータニオンの比較演算
	bool operator==(const Quaternion& a, const Quaternion& b);

}
#endif // !QUATERNION_H_INCLUDED
